#ifndef RAY_BASE_H
#define RAY_BASE_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define RAY_CALL __cdecl
#if defined(RAY_EXPORT)
#define RAY_API extern "C" __declspec(dllexport)
#else
#define RAY_API extern "C" __declspec(dllimport)
#endif
#elif defined(__APPLE__)
#include <TargetConditionals.h>
#define RAY_API __attribute__((visibility("default"))) extern "C"
#define RAY_CALL
#elif defined(__ANDROID__) || defined(__linux__)
#define RAY_API extern "C" __attribute__((visibility("default")))
#define RAY_CALL
#else
#define RAY_API extern "C"
#define RAY_CALL
#endif

#include "ray_autoptr.h"
#include "ray_refptr.h"

#define DEVICE_MAX_NAME_LEN 260
#define DEVICE_MAX_ID_LEN 260

#define ENCODER_MAX_NAME_LEN 260
#define ENCODER_MAX_ID_LEN 260

#define RECORDER_MAX_PATH_LEN 260

namespace ray {

typedef uint32_t	rt_error;
typedef uint64_t	rt_uid;

typedef enum {
	ERR_NONE = 0,
	ERR_UNKNOWN,
	ERR_UNSUPPORT,
	ERR_INVALID_PARAM,
	ERR_INVALID_POINTER,
}ERROR_CODE;

typedef enum {
	REASON_NONE = 0
}ERROR_REASON;

typedef enum {
	VIDEO_CAPTURER_UNKNOWN = 0,

	/**
	* whole monitor video capturer
	*/
	VIDEO_CAPTURER_MONITOR,

	/**
	* rect video capturer
	*/
	VIDEO_CAPTURER_RECT,

	/**
	* window video capturer
	*/
	VIDEO_CAPTURER_WINDOW,

	/**
	* game video capturer, means dx or gl hook capture
	*/
	VIDEO_CAPTURER_GAME,

	/**
	* camera video capturer
	*/
	VIDEO_CAPTURER_CAMERA,

	/**
	* source video capturer, like text what you want to draw topmost or picture and video files
	*/
	VIDEO_CAPTURER_SOURCE,
}VIDEO_CAPTURER_TYPE;

typedef enum {
	AUDIO_CAPTURER_UNKNOWN = 0,

	/**
	* speaker audio capturer
	*/
	AUDIO_CAPTURER_SPEAKER,

	/**
	* microphone audio capturer
	*/
	AUDIO_CAPTURER_MICROPHONE,

	/**
	* app audio capturer
	*/
	AUDIO_CAPTURER_APP
}AUDIO_CAPTURER_TYPE;

typedef enum {
	RECORDER_IID_UNKNOWN = 0,

	RECORDER_IID_VIDEO_DEVICE_MGR,
	RECORDER_IID_VIDEO_CAPTURER_MGR,
	RECORDER_IID_VIDEO_ENCODER_MGR,

	RECORDER_IID_AUDIO_DEVICE_MGR,
	RECORDER_IID_AUDIO_CAPTURER_MGR,
	RECORDER_IID_AUDIO_ENCODER_MGR,

	RECORDER_IID_MUXER,
	RECORDER_IID_REMUXER
}RECORDER_INTERFACE_IID;

namespace base {

class CRect {
public:
	CRect() {}
	~CRect() {}

	uint32_t width() { return right - left; }
	uint32_t height() { return bottom - top; }

	uint32_t left;
	uint32_t top;
	uint32_t right;
	uint32_t bottom;
};


class RayRefInterface {
protected:
	virtual ~RayRefInterface() = default;

public:
	virtual void AddRef() const = 0;

	virtual void Release() const = 0;

	virtual bool HasOneRef() const = 0;
};

} // namespace base
} // namespace ray

#endif
