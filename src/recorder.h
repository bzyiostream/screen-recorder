
#define RAY_EXPORT
#include "export.h"

#include "utils\singleton.h"

namespace ray {
namespace recorder {

class Recorder :
	public IRecorder,
	public utils::Singleton<Recorder>
{

private:
	Recorder() :_event_handler(nullptr) {}
	~Recorder() { release(); }

	Recorder(const Singleton&) = delete;
	Recorder& operator=(const Recorder&) = delete;

	SINGLETON_FRIEND(Recorder);

public:
	rt_error initialize(const RecorderConfiguration& config) override;

	void release() override;

	void getVersion(
		uint32_t *major,
		uint32_t *minor,
		uint32_t *patch,
		uint32_t *build) override;

	void setEventHandler(IRecorderEventHandler *handler) override;

	rt_error queryInterface(const RECORDER_INTERFACE_IID& iid, void **pp) override;

private:
	void onRemuxProgress(const char *srcFilePath, int progress, int total);
	void onRemuxState(const char *srcFilePath, bool succeed, rt_error error);

private:

	IRecorderEventHandler *_event_handler;
};
}
}