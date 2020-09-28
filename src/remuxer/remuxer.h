#ifndef REMUXER_FFMPEG
#define REMUXER_FFMPEG

#include <map>
#include <atomic>
#include <functional>
#include <thread>

#include "export.h"
#include "utils\singleton.h"

namespace ray {
namespace remux {

typedef std::function<void(const char *srcFilePath, int progress, int total)> IREMUXER_PROGRESS_CB;
typedef std::function<void(const char *srcFilePath, bool succeed, rt_error error)> IREMUEXER_STATE_CB;

class Remuxer :
	public recorder::IRemuxer,
	public utils::Singleton<Remuxer>
{
private:
	Remuxer() {}

	~Remuxer() { release(); }

	SINGLETON_FRIEND(Remuxer);

public:
	typedef struct _REMUXER_PARAM {
		char src[RECORDER_MAX_PATH_LEN];
		char dst[RECORDER_MAX_PATH_LEN];
		int64_t src_size;

		IREMUXER_PROGRESS_CB cb_progress;
		IREMUEXER_STATE_CB cb_state;
		std::atomic_bool running;
	}REMUXER_PARAM;

	typedef struct _REMUXER_HANDLE {
		REMUXER_PARAM param;
		std::thread fn;
	}REMUXER_HANDLE;

	void setEventHandler(const IREMUXER_PROGRESS_CB progressCB, const IREMUEXER_STATE_CB stateCB);

	rt_error remux(
		const char srcFilePath[RECORDER_MAX_PATH_LEN],
		const char dstFilePath[RECORDER_MAX_PATH_LEN]
	) override;

	void stop(const char srcFilePath[RECORDER_MAX_PATH_LEN]) override;

	void stopAll() override;

	virtual void release() override;

private:
	std::mutex _g_mutex;
	std::map<std::string, REMUXER_HANDLE*> _handlers;

	IREMUXER_PROGRESS_CB _cb_progress;
	IREMUEXER_STATE_CB _cb_state;
};

}

}



#endif // !REMUXER_FFMPEG