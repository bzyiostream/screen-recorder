#ifndef RECORDER_EXPORT
#define RECORDER_EXPORT

#include <stdint.h>


#ifdef AMRECORDER_IMPORT
#define AMRECORDER_API extern "C"  __declspec(dllimport)
#else
#define AMRECORDER_API extern "C"  __declspec(dllexport)
#endif


/**
* AMRECORDER_DEVICE
*/
#pragma pack(push,1)
typedef struct {
	/**
	* Device id in utf8
	*/
	char id[260];

	/**
	* Device name in utf8
	*/
	char name[260];

	/**
	* Is default device
	*/
	uint8_t is_default;
}AMRECORDER_DEVICE;
#pragma pack(pop)

/**
* AMRECORDER_SETTING
*/
#pragma pack(push,1)
typedef struct {

	/**
	* Left of desktop area
	*/
	int v_left;

	/**
	* Top of desktop area
	*/
	int v_top;

	/**
	* Width of desktop area
	*/
	int v_width;

	/**
	* Height of desktop area
	*/
	int v_height;

	/**
	* Output video quality, value must be between 0 and 100, 0 is least, 100 is best
	*/
	int v_qb;

	/**
	* Output video bitrate, the larger value you set,
	* the better video quality you get, but the file size is also larger.
	* Suggestion: 960|1280|2500 *1000
	*/
	int v_bit_rate;

	/**
	* FPS(frame per second)
	*/
	int v_frame_rate;

	/**
	* Video encoder id
	* Must get by recorder_get_vencoders
	*/
	int v_enc_id;

	/**
	* Output file path,the output file format is depended on the ext name.
	* Support .mp4|.mkv for now.
	*/
	char output[260];

	/**
	* Desktop device
	* Unused
	*/
	AMRECORDER_DEVICE v_device;

	/**
	* Microphone device info
	*/
	AMRECORDER_DEVICE a_mic;

	/**
	* Speaker device info
	*/
	AMRECORDER_DEVICE a_speaker;
}AMRECORDER_SETTING;
#pragma pack(pop)

/**
* AMRECORDER_ENCODERS
*/
#pragma pack(push,1)
typedef struct {

	/**
	* Encoder id
	*/
	int id;

	/**
	* Encoder name
	*/
	char name[260];
}AMRECORDER_ENCODERS;
#pragma pack(pop)

/**
* Recording duration callback function
* @param[in] duration time in millisecond
*/
typedef void(*AMRECORDER_FUNC_DURATION)(uint64_t duration);

/**
* Recording error callback function
* Should call recorder_err2str to get stringify error info
* @param[in] error
*/
typedef void(*AMRECORDER_FUNC_ERROR)(int error);

/**
* Device changed callback function
* Should refresh devices
* @param[in] type 0 for video, 1 for speaker, 2 for microphone
*/
typedef void(*AMRECORDER_FUNC_DEVICE_CHANGE)(int type);

/**
* YUV data callback function
* Should refresh devices
* @param[in] data   yuv buffer
* @param[in] size   yuv buffer size
* @param[in] width  picture with
* @param[in] height picture height
* @param[in] type   yuv type, 0 for 420, 1 fro 444
*/
typedef void(*AMRECORDER_FUNC_PREVIEW_YUV)(
	const unsigned char *data,
	unsigned int size,
	int width,
	int height,
	int type
	);

/**
* Unused callback function
*/
typedef void(*AMRECORDER_FUNC_PREVIEW_AUDIO)();

/**
* Remux progress callback function
* @param[in] path       source file path
* @param[in] progress   remuxing progress in total
* @param[in] total      always will be 100
*/
typedef void(*AMRECORDER_FUNC_REMUX_PROGRESS)(const char *path, int progress, int total);

/**
* Remux state callback function
* @param[in] path    source file path
* @param[in] state   0 for unremuxing,1 for remuxing
* @param[in] error   0 for succed,otherwhise error code
*/
typedef void(*AMRECORDER_FUNC_REMUX_STATE)(const char *path, int state, int error);

/**
* Callback functions structure
*/
#pragma pack(push,1)
typedef struct {
	AMRECORDER_FUNC_DURATION func_duration;
	AMRECORDER_FUNC_ERROR func_error;
	AMRECORDER_FUNC_DEVICE_CHANGE func_device_change;
	AMRECORDER_FUNC_PREVIEW_YUV func_preview_yuv;
	AMRECORDER_FUNC_PREVIEW_AUDIO func_preview_audio;
}AMRECORDER_CALLBACK;
#pragma pack(pop)

/**
* Get error string by specified error code
* @return error string
*/
AMRECORDER_API const char * recorder_err2str(int error);

/**
* Initialize recorder with specified seetings¡¢speaker¡¢mic¡¢encoder...
* @return 0 if succeed,error code otherwise
*/
AMRECORDER_API int recorder_init(const AMRECORDER_SETTING &setting, const AMRECORDER_CALLBACK &callbacks);

/**
* Release all recorder resources
*/
AMRECORDER_API void recorder_release();

/**
* Start recording
* @return 0 if succeed,error code otherwise
*/
AMRECORDER_API int recorder_start();

/**
* Stop recording
*/
AMRECORDER_API void recorder_stop();

/**
* Pause recording
* @return 0 if succeed,error code otherwise
*/
AMRECORDER_API int recorder_pause();

/**
* Resume recording
* @return 0 if succeed,error code otherwise
*/
AMRECORDER_API int recorder_resume();

/**
* Get valid speaker devices
* @param[in] devices a pointer to a device array,should call recorder_free_array to free memory
* @return count of speakers
*/
AMRECORDER_API int recorder_get_speakers(AMRECORDER_DEVICE **devices);

/**
* Get valid mic devices
* @param[in] devices a pointer to a device array,should call recorder_free_array to free memory
* @return count of mics
*/
AMRECORDER_API int recorder_get_mics(AMRECORDER_DEVICE **devices);

/**
* Get valid camera devices
* @param[in] devices a pointer to a device array,should call recorder_free_array to free memory
* @return count of cameras
*/
AMRECORDER_API int recorder_get_cameras(AMRECORDER_DEVICE **devices);

/**
* Get valid encoders
* @param[in] encoders a pointer to a encoder array,should call recorder_free_array to free memory
* @return count of encoders
*/
AMRECORDER_API int recorder_get_vencoders(AMRECORDER_ENCODERS **encoders);

/**
* Free memory allocate by recorder
* @param[in] array_address the pointer of array buffer
*/
AMRECORDER_API void recorder_free_array(void *array_address);

/**
* Recorder create a remux job
* @param[in] src    source file path
* @param[in] dst   0 for unremuxing,1 for remuxing
* @param[in] func_progress   0 for succed,otherwhise error code
* @param[in] func_state   0 for succed,otherwhise error code
*/
AMRECORDER_API int recorder_remux(
	const char *src, const char *dst,
	AMRECORDER_FUNC_REMUX_PROGRESS func_progress,
	AMRECORDER_FUNC_REMUX_STATE func_state);

/**
* Enable or disable preview include video and audio
* @param[in] enable 1 for enable,0 for disable
*/
AMRECORDER_API void recorder_set_preview_enabled(int enable);

#endif //RECORDER_EXPORT


#ifndef RAY_RECORDER_H
#define RAY_RECORDER_H

#include "base.h"

namespace ray {
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

class IRemuxer {
protected:
	virtual ~IRemuxer() {};
public:
	virtual rt_error remux(
		const char srcFilePath[RECORDER_MAX_PATH_LEN],
		const char dstFilePath[RECORDER_MAX_PATH_LEN]
	) = 0;

	virtual void stop(const char srcFilePath[RECORDER_MAX_PATH_LEN]) = 0;

	virtual void stopAll() = 0;
};

/**
*
*/
class IRecorderEventHandler {
public:
	virtual ~IRecorderEventHandler() {};

	/**
	*
	*/
	virtual void onDuration(uint64_t duration) {}

	virtual void onError(ERROR_CODE code) {}

	virtual void onDeviceChanged(bool isAudio) {}

	virtual void onRawVideoData(IVideoFrame &frame) {}

	virtual void onRawAudioData(IAudioFrame &frame) {}

	virtual void onAudioVolume(const rt_uid uid, int volume) {}

	virtual void onRemuxProgress(const char *src, uint8_t progress, uint8_t total) {}

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
	virtual rt_error initialize(const char logPath[RECORDER_MAX_PATH_LEN]) = 0;

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
	* @param[in] iid              Interface IID
	* @param[out] interface   A pointer pointed to interface's pointer,
							  nullptr will be set when get error, otherwise none-nullptr value will be set
	*/
	virtual void queryInterface(const RECORDER_INTERFACE_IID& iid, void **interface) = 0;
};
}
}


RAY_API ray::recorder::IRecorder* RAY_CALL createRecorder();

#endif // !RAY_RECORDER_H