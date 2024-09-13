#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <opus.h>
#include <stdio.h>
#include "opusjni.h"
#include <android/log.h>

#define LOG_TAG "Opus JNI"
#ifdef NDEBUG
#define LOGD(...)
#define LOGV(...)
#pragma message ( "This is a release version!")
#else
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#pragma message ( "This is a debug version!")
#endif
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL
Java_com_tunityapp_tunityapp_OpusDecoder_decoderCreate(JNIEnv * env, jobject obj, jint sampleRate, jint channels)
{
    int error = 0;
    LOGV("creating decoder sample rate: %d channels %d", sampleRate, channels);
    OpusDecoder *st = opus_decoder_create(sampleRate, channels, &error);
    if(error != OPUS_OK)
    {
	LOGE("decoder_create failed: %s", opus_strerror(error));
        return 0;
    }
    LOGV("decoder_create success");
    return (jlong)(intptr_t) st;
}

JNIEXPORT jint JNICALL
Java_com_tunityapp_tunityapp_OpusDecoder_decode(JNIEnv * env, jobject obj, jlong opusDecoder, jbyteArray inData, jshortArray pcm, jint frameSize, jint decodeFec)
{
    LOGV("Opus decode. opus decoder: %lld. framesize: %d decodefec: %d", opusDecoder, frameSize, decodeFec);
    OpusDecoder *st = (OpusDecoder *)(intptr_t)(jlong)opusDecoder;
    if(st == NULL)
    {
		LOGE("decoder failed: opusDecoder is null!");
		return OPUS_BAD_ARG;
    }

	if(pcm == NULL)
    {
		LOGE("decoder failed: pcm is null!");
		return OPUS_BAD_ARG;
    }

	jbyte* bufferPtr = NULL;
    jsize bufferLen = 0;
    if(inData == NULL)
    {
		LOGD("decoder received null packet. is this to compensate for packet loss?");
    }
    else
    {
		bufferPtr = (*env)->GetByteArrayElements(env, inData, NULL);
		if(bufferPtr == NULL)
			bufferLen = 0;
		else
			bufferLen = (*env)->GetArrayLength(env, inData);
    }
    jshort* outPtr = (*env)->GetShortArrayElements(env, pcm, NULL);
    jsize outLen = (*env)->GetArrayLength(env, pcm);
    LOGD("Opus decode. bufferPtr=%p, outPtr=%p, length=%d outLen=%d", bufferPtr, outPtr, bufferLen, outLen);
    int frame_size = opus_decode(st, (const unsigned char *)bufferPtr, bufferLen, outPtr, frameSize, decodeFec);
    if (frame_size<0)
    {
		LOGE("decoder failed: %s", opus_strerror(frame_size));
    }
    LOGV("decoder success. decoded length=%d", frame_size);
	if(bufferPtr != NULL)
		(*env)->ReleaseByteArrayElements(env, inData, bufferPtr, JNI_ABORT); /*this is an [in] array. no need to copy back*/
    (*env)->ReleaseShortArrayElements(env, pcm, outPtr, 0); //this is an [out] array
    return frame_size;
}

JNIEXPORT void JNICALL
Java_com_tunityapp_tunityapp_OpusDecoder_decoderDestroy(JNIEnv * env, jobject obj, jlong opusDecoder)
{
    OpusDecoder *st = (OpusDecoder *)(intptr_t)(jlong)opusDecoder;
    LOGV("decoder destroy. st = %p", st);
    opus_decoder_destroy(st);
}

#ifdef __cplusplus
} //extern "C"
#endif
