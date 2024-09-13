# Build a libopus release wrapped in a Tunity JNI bridge

This allows for a fully automated future upgrade of libopus, requiring only copying the _jni_ folder into the new Opus source tree and running from inside it:
```
build.sh
```

Then, you can either manually copy all newly built libtunityopus.so into the Tunity tree, or simply run:
```
deploy.sh
```

All scripts will inform whether a required environment variable is missing (not exported).  Here's the current list:
```
# build
$ANDROID_NDK_ROOT
$NDK_VERSION

# deploy
$TUNITY_ROOT
```

To change the minimum Android API version, change the value of _ANDROID_PLATFORM_ in `build_opus_for_arch()`.

Target architectures are defined as:
```
architectures=("arm64-v8a" "armeabi-v7a" "x86_64" "x86")
```
