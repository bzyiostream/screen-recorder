#include "recorder.h"

#include "constants\version.h"

#include "remuxer\remuxer.h"

#include "utils\strings.h"
#include "utils\log.h"

namespace ray {
namespace recorder {

using namespace base;

rt_error Recorder::initialize(const RecorderConfiguration& config) {

	utils::InitLogImpl(config.logPath ? utils::strings::utf8_unicode(config.logPath).c_str() : nullptr);

	remux::Remuxer::getInstance()->setEventHandler(
		std::bind(&Recorder::onRemuxProgress, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
		std::bind(&Recorder::onRemuxState, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
	);

	return ERR_NONE;
}

void Recorder::release() {

}

void Recorder::getVersion(uint32_t *major, uint32_t *minor, uint32_t *patch, uint32_t *build) {

	if (major) *major = VER_MAJOR;

	if (minor) *minor = VER_MINOR;

	if (patch) *patch = VER_PATCH;

	if (build) *build = VER_BUILD;
}

void Recorder::setEventHandler(IRecorderEventHandler *handler) {
	_event_handler = handler;
}

rt_error Recorder::queryInterface(const RECORDER_INTERFACE_IID& iid, void **pp) {
	rt_error ret = ERR_NONE;

	do {
		if (!pp) {
			ret = ERR_INVALID_POINTER;
			break;
		}

		*pp = nullptr;

		switch (iid)
		{
		case RECORDER_IID_REMUXER:
			*pp = static_cast<void*>(remux::Remuxer::getInstance());
			break;
		default:
			ret = ERR_UNSUPPORT;
			break;
		}

	} while (0);

	return ret;
}

void Recorder::onRemuxProgress(const char * srcFilePath, int progress, int total)
{
	if (_event_handler)
		_event_handler->onRemuxProgress(srcFilePath, progress, total);
}

void Recorder::onRemuxState(const char * srcFilePath, bool succeed, rt_error error)
{
	if (_event_handler)
		_event_handler->onRemuxState(srcFilePath, succeed, error);
}

}
}



RAY_API ray::recorder::IRecorder *createRecorder()
{
	return ray::recorder::Recorder::getInstance();
}