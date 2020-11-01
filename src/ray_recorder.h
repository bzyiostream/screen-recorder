#include "include\ray_base.h"

#include "base\ray_singleton.h"

namespace ray {
namespace recorder {

class Recorder :
	public IRecorder,
	public base::Singleton<Recorder>
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

	void setEventHandler(IRecorderEventHandler *handler) override;

	rt_error queryInterface(const RECORDER_INTERFACE_IID& iid, void **pp) override;

private:

	IRecorderEventHandler *_event_handler;
};
}
}