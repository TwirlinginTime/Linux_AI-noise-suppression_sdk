#ifndef __AUDIO_CAPTURE_API__
#define __AUDIO_CAPTURE_API__

#ifdef __cplusplus
extern "C"
{
#endif
	void captureAuthInit(const char *app_id, const char *passwd);

	void captureAuthRelease();

	void *dnnoiseInit();
	void dnnoiseSet(void *obj);
	void dnnoiseProcess(void *obj, float *pcm);
	void dnnoiseRelease(void *obj);


#ifdef __cplusplus
};
#endif

#endif /*__AUDIO_CAPTURE_API__*/
