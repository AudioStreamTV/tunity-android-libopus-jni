/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_tunityapp_tunityapp_OpusDecoder */

#ifndef _Included_com_tunityapp_tunityapp_OpusDecoder
#define _Included_com_tunityapp_tunityapp_OpusDecoder
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_tunityapp_tunityapp_OpusDecoder
 * Method:    decoderCreate
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_com_tunityapp_tunityapp_OpusDecoder_decoderCreate
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_tunityapp_tunityapp_OpusDecoder
 * Method:    decode
 * Signature: (J[B[SII)I
 */
JNIEXPORT jint JNICALL Java_com_tunityapp_tunityapp_OpusDecoder_decode
  (JNIEnv *, jobject, jlong, jbyteArray, jshortArray, jint, jint);

/*
 * Class:     com_tunityapp_tunityapp_OpusDecoder
 * Method:    decoderDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_tunityapp_tunityapp_OpusDecoder_decoderDestroy
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
