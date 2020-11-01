#include "ray_recorder.h"

#include "utils\strings.h"
#include "utils\log.h"

namespace ray {
namespace recorder {

using namespace base;

rt_error Recorder::initialize(const RecorderConfiguration& config) {

	utils::InitLogImpl(config.logPath ? utils::strings::utf8_unicode(config.logPath).c_str() : nullptr);

	return ERR_NO;
}

void Recorder::release() {

}

void Recorder::setEventHandler(IRecorderEventHandler *handler) {
	_event_handler = handler;
}

rt_error Recorder::queryInterface(const RECORDER_INTERFACE_IID& iid, void **pp) {
	rt_error ret = ERR_NO;

	do {
		if (!pp) {
			ret = ERROR_INVALID_PARAMETER;
			break;
		}

		*pp = nullptr;

		switch (iid)
		{
			//case RECORDER_IID_REMUXER:
				//*pp = static_cast<void*>(remux::Remuxer::getInstance());
			break;
		default:
			ret = ERR_UNSUPPORT;
			break;
		}

	} while (0);

	return ret;
}

}
}