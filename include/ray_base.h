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

typedef enum ErrorCode {
	ERR_NO = 0,
	ERR_ERROR,
	ERR_UNSUPPORT,
	ERR_INVALID_CONTEXT,
	ERR_NEED_INIT,
	ERR_TIMEOUT,
	ERR_ALLOCATE_FAILED,

	//ERR_CO_
	ERR_CO_INITED_FAILED,
	ERR_CO_CREATE_FAILED,
	ERR_CO_GETENDPOINT_FAILED,
	ERR_CO_ACTIVE_DEVICE_FAILED,
	ERR_CO_GET_FORMAT_FAILED,
	ERR_CO_AUDIOCLIENT_INIT_FAILED,
	ERR_CO_GET_CAPTURE_FAILED,
	ERR_CO_CREATE_EVENT_FAILED,
	ERR_CO_SET_EVENT_FAILED,
	ERR_CO_START_FAILED,
	ERR_CO_ENUMENDPOINT_FAILED,
	ERR_CO_GET_ENDPOINT_COUNT_FAILED,
	ERR_CO_GET_ENDPOINT_ID_FAILED,
	ERR_CO_OPEN_PROPERTY_FAILED,
	ERR_CO_GET_VALUE_FAILED,
	ERR_CO_GET_BUFFER_FAILED,
	ERR_CO_RELEASE_BUFFER_FAILED,
	ERR_CO_GET_PACKET_FAILED,
	ERR_CO_PADDING_UNEXPECTED,

	//ERR_FFMPEG_
	ERR_FFMPEG_OPEN_INPUT_FAILED,
	ERR_FFMPEG_FIND_STREAM_FAILED,
	ERR_FFMPEG_FIND_DECODER_FAILED,
	ERR_FFMPEG_OPEN_CODEC_FAILED,
	ERR_FFMPEG_READ_FRAME_FAILED,
	ERR_FFMPEG_READ_PACKET_FAILED,
	ERR_FFMPEG_DECODE_FRAME_FAILED,
	ERR_FFMPEG_NEW_SWSCALE_FAILED,
	ERR_FFMPEG_FIND_ENCODER_FAILED,
	ERR_FFMPEG_ALLOC_CONTEXT_FAILED,
	ERR_FFMPEG_ENCODE_FRAME_FAILED,
	ERR_FFMPEG_ALLOC_FRAME_FAILED,
	ERR_FFMPEG_OPEN_IO_FAILED,
	ERR_FFMPEG_CREATE_STREAM_FAILED,
	ERR_FFMPEG_COPY_PARAMS_FAILED,
	ERR_RESAMPLE_INIT_FAILED,
	ERR_FFMPEG_NEW_STREAM_FAILED,
	ERR_FFMPEG_FIND_INPUT_FMT_FAILED,
	ERR_FFMPEG_WRITE_HEADER_FAILED,
	ERR_FFMPEG_WRITE_TRAILER_FAILED,
	ERR_FFMPEG_WRITE_FRAME_FAILED,

	//ERR_FILTER_
	ERR_FILTER_ALLOC_GRAPH_FAILED,
	ERR_FILTER_CREATE_FILTER_FAILED,
	ERR_FILTER_PARSE_PTR_FAILED,
	ERR_FILTER_CONFIG_FAILED,
	ERR_FILTER_INVALID_CTX_INDEX,
	ERR_FILTER_ADD_FRAME_FAILED,

	//ERR_GDI_
	ERR_GDI_GET_DC_FAILED,
	ERR_GDI_CREATE_DC_FAILED,
	ERR_GDI_CREATE_BMP_FAILED,
	ERR_GDI_BITBLT_FAILED,
	ERR_GDI_GET_DIBITS_FAILED,

	//ERR_D3D_
	ERR_D3D_LOAD_FAILED,
	ERR_D3D_GET_PROC_FAILED,
	ERR_D3D_CREATE_DEVICE_FAILED,
	ERR_D3D_QUERYINTERFACE_FAILED,
	ERR_D3D_CREATE_VERTEX_SHADER_FAILED,
	ERR_D3D_CREATE_INLAYOUT_FAILED,
	ERR_D3D_CREATE_PIXEL_SHADER_FAILED,
	ERR_D3D_CREATE_SAMPLERSTATE_FAILED,

	//ERR_DXGI_
	ERR_DXGI_GET_PROC_FAILED,
	ERR_DXGI_GET_ADAPTER_FAILED,
	ERR_DXGI_GET_FACTORY_FAILED,
	ERR_DXGI_FOUND_ADAPTER_FAILED,

	//ERR_DUP_
	ERR_DUP_ATTATCH_FAILED,
	ERR_DUP_QI_FAILED,
	ERR_DUP_GET_PARENT_FAILED,
	ERR_DUP_ENUM_OUTPUT_FAILED,
	ERR_DUP_DUPLICATE_MAX_FAILED,
	ERR_DUP_DUPLICATE_FAILED,
	ERR_DUP_RELEASE_FRAME_FAILED,
	ERR_DUP_ACQUIRE_FRAME_FAILED,
	ERR_DUP_QI_FRAME_FAILED,
	ERR_DUP_CREATE_TEXTURE_FAILED,
	ERR_DUP_QI_DXGI_FAILED,
	ERR_DUP_MAP_FAILED,
	ERR_DUP_GET_CURSORSHAPE_FAILED,

	//ERR_REMUX_
	ERR_REMUX_RUNNING,
	ERR_REMUX_NOT_EXIST,
	ERR_REMUX_INVALID_INOUT,

	ERR_MAX
}ErrorCode;

typedef enum {
	REASON_NONE = 0
}ErrorReason;

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

typedef enum RECORDER_INTERFACE_IID {
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

namespace recorder {

typedef struct {
	char name[DEVICE_MAX_NAME_LEN];
	char id[DEVICE_MAX_ID_LEN];
}VideoDevice;

typedef struct {
	char name[DEVICE_MAX_NAME_LEN];
	char id[DEVICE_MAX_ID_LEN];
}AudioDevice;

typedef struct {

}VideoEncoderParameter;

typedef struct {

}AudioEncoderParameter;

typedef struct RecorderConfiguration {
	const char *logPath = nullptr;
}RecorderConfiguration;

/**
*
*/
class IVideoDeviceCollection {
protected:
	virtual ~IVideoDeviceCollection() {};

	virtual void release() = 0;

	virtual void getCount() = 0;
};

class IVideoDeviceManager {
protected:
	virtual ~IVideoDeviceManager() {};
};

class IVideoFrame {
protected:
	virtual ~IVideoFrame() {};

public:

	enum VIDEO_FRAME_TYPE {
		VIDEO_FRAME_BGRA,
		VIDEO_FRAME_YUV420,
		VIDEO_FRAME_YUV444
	};

	virtual rt_uid getUID() const = 0;

	virtual const uint8_t *getData() const = 0;

	virtual uint32_t getDataSize() const = 0;

	virtual const base::CRect& getSize() const = 0;
};

class IVideoCapturer {
protected:
	virtual ~IVideoCapturer() {};
};

class IVideoCapturerManager {
protected:
	virtual ~IVideoCapturerManager() {};

public:
	virtual rt_error createVideoCapturer(VIDEO_CAPTURER_TYPE type, IVideoCapturer **capturer, rt_uid *uid) = 0;

	virtual void deleteVideoCapturer(IVideoCapturer *capturer) = 0;
};

class IVideoEncoderCollection {
protected:
	virtual ~IVideoEncoderCollection() {};
};

class IVideoEncoderManager {
protected:
	virtual ~IVideoEncoderManager() {};
};

class IAudioDeviceCollection {
protected:
	virtual ~IAudioDeviceCollection() {};
};

class IAudioDeviceManager {
protected:
	virtual ~IAudioDeviceManager() {};
};

class IAudioFrame {
protected:
	virtual ~IAudioFrame() {};

public:

	virtual rt_uid getUID() const = 0;

	virtual const uint8_t *getData() const = 0;

	virtual uint32_t getDataSize() const = 0;
};

class IAudioCapturer {
protected:
	virtual ~IAudioCapturer() {};

public:
	virtual void release() = 0;

	virtual IAudioDeviceManager *getManager() = 0;
};

class IAudioCapturerManager {
protected:
	virtual ~IAudioCapturerManager() {};

public:
	virtual rt_error createAudioCapturer(AUDIO_CAPTURER_TYPE type, IAudioCapturer **capturer, rt_uid *uid) = 0;

	virtual void deleteAudioCapturer(IAudioCapturer *capturer) = 0;
};

class IAudioEncoderCollection {
protected:
	virtual ~IAudioEncoderCollection() {};
};

class IAudioEncoderManager {
protected:
	virtual ~IAudioEncoderManager() {};
};

class IMuxer {
protected:
	virtual ~IMuxer() {};

public:
	virtual bool isMuxing() = 0;

	virtual rt_error start(const char outputFileName[RECORDER_MAX_PATH_LEN]) = 0;

	virtual void stop() = 0;

	virtual rt_error pause() = 0;

	virtual rt_error resume() = 0;

	virtual rt_error setVideoEncoderParameters(VideoEncoderParameter *param) = 0;

	virtual rt_error setAudioEncoderParameters(AudioEncoderParameter *param) = 0;
};

/**
* Remuxer
*/
class IRemuxer {
protected:
	virtual ~IRemuxer() {};
public:

	/**
	* Start to remux file to specified format
	* @param srcFilePath source file path
	* @param dstFilePath dst file path specified format by extension
	* @return 0 for succeed, others for error code
	*/
	virtual rt_error remux(
		const char srcFilePath[RECORDER_MAX_PATH_LEN],
		const char dstFilePath[RECORDER_MAX_PATH_LEN]
	) = 0;

	/**
	* Stop to remux specified file
	* @param srcFilePath
	*/

	virtual void stop(const char srcFilePath[RECORDER_MAX_PATH_LEN]) = 0;

	/**
	* Stop all remuxing thread
	*/
	virtual void stopAll() = 0;

	/**
	* Release remuxer
	* This will stop all remuxing tasks and release remuxer
	*/
	virtual void release() = 0;
};

/**
* Recorder event handler
*/
class IRecorderEventHandler {
public:
	virtual ~IRecorderEventHandler() {};

	/**
	* Muxe duration callback function
	* @param duration
	*/
	virtual void onDuration(uint64_t duration) {}

	/*
	* Error code callback function
	* @param code error code
	* @param reason error reason
	*/
	virtual void onError(ErrorCode code, ErrorReason reason) {}

	/**
	* Device change callback function
	* @param isAudio audio or video device
	*/
	virtual void onDeviceChanged(bool isAudio) {}

	/**
	* Raw video data callback function
	* @param frame video frame
	*/
	virtual void onRawVideoData(IVideoFrame &frame) {}

	/**
	* Raw audio data callback function
	* @param frame audio frame
	*/
	virtual void onRawAudioData(IAudioFrame &frame) {}

	/**
	* Audio volume callback function
	* @param uid    specified audio capture
	* @param volume
	*/
	virtual void onAudioVolume(const rt_uid uid, int volume) {}

	/**
	* Remux progress callback function
	* @param src source file path
	* @param progress current progress (0-100)
	* @param total total progress value ,will be always 100
	*/
	virtual void onRemuxProgress(const char *src, uint8_t progress, uint8_t total) {}

	/**
	* Remux state
	* @param src     source file path
	* @param succeed true or false
	* @param error   error code
	*/
	virtual void onRemuxState(const char *src, bool succeed, rt_error error) {}
};

/**
* Define all interfaces of Recorder
*/
class IRecorder {
protected:
	virtual ~IRecorder() {};

public:

	/**
	* Initialize recorder with specified log file path
	* @param logPath   Specified log file path in utf8
	* @return          0 for success, other for error code
	*/
	virtual rt_error initialize(const RecorderConfiguration& config) = 0;

	/**
	* Release recorder
	* This will stop all tasks include capturing, encoding, muxing and remuxing
	*/
	virtual void release() = 0;

	/**
	* Get recorder version
	* @param major
	* @param minor
	* @param patch
	* @param build
	*/
	virtual void getVersion(uint32_t *major, uint32_t *minor, uint32_t *patch, uint32_t *build) = 0;

	/**
	* Set recorder event handler
	* @param handler
	*/
	virtual void setEventHandler(IRecorderEventHandler *handler) = 0;

	/**
	* Query interface by iid
	* @param iid         Interface IID
	* @param interface   A pointer pointed to interface's pointer,
	*					 nullptr will be set when get error, otherwise none-nullptr value will be set
	* @return            0 for success, other for error code
	*/
	virtual rt_error queryInterface(const RECORDER_INTERFACE_IID& iid, void **pp) = 0;
};
} // namespace recorder

} // namespace ray

RAY_API ray::recorder::IRecorder* RAY_CALL createRecorder();

#endif
