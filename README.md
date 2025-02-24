# Build a libopus release wrapped in a Tunity JNI bridge

This allows for a fully automated future upgrade of libopus, requiring only copying the _jni_ folder into the new Opus source tree and running from inside it:
```
build.sh
```

Then, you nedd to manually copy all newly built libtunityopus.so into the Tunity tree.

All scripts will inform whether a required environment variable is missing (not exported).  Here's the current list:
```
# build
$ANDROID_NDK_ROOT
```

To change the minimum Android API version, change the value of _MIN_ANDROID_API_VERSION_.

Target architectures are defined as:
```
architectures=("arm64-v8a" "armeabi-v7a" "x86_64" "x86")
```

For more information, refer to https://github.com/xiph/opus/blob/main/cmake/README.md.
