#include "recorder.h"

#include "constants\version.h"

#include "remuxer\remuxer.h"

#include "utils\strings.h"
#include "utils\log.h"

namespace ray {
namespace recorder {

rt_error Recorder::initialize(const char logPath[RECORDER_MAX_PATH_LEN]) {

	utils::InitLogImpl(utils::strings::utf8_unicode(logPath).c_str());

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

void Recorder::queryInterface(const RECORDER_INTERFACE_IID& iid, void **pp) {
	if (!pp) return;

	*pp = nullptr;

	switch (iid)
	{
	case RECORDER_IID_REMUXER:
		*pp = static_cast<void*>(remux::Remuxer::getInstance());
		break;
	default:
		break;
	}
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
