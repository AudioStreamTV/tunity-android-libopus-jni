# Build libopus for Android and iOS

## Build a libopus release for iOS

Copy the *ios* folder into the official libopus root directory.
Then, from inside it, simply run (requires CMake):
```
./build.sh
```
To install, manually copy the *libopus.a* output file to the following folder in the *tunity-mobile* tree:
```
core/opus/src/iosMain/cinterop/lib/
```

## Build a libopus release for Android (JNI-bridged)
Copy the *android* folder into the official *libopus* root directory.
Then, from inside it, simply run (requires CMake):
```
./build.sh
```
It will inform whether a required environment variable is missing (not exported).  Here's the current list:
```
$ANDROID_NDK_ROOT
```
To change the minimum Android API version, change the value of *MIN_ANDROID_API_VERSION*.
Target architectures are defined as:
```
architectures=("arm64-v8a" "armeabi-v7a" "x86_64" "x86")
```
To install, manually copy the output *libtunityopus.so* targets to the following folder in the *tunity-mobile* tree:
```
core/opus/src/androidMain/jniLibs/
```
Make sure to copy the correct output to each architecture folder.

For more information, refer to https://github.com/xiph/opus/blob/main/cmake/README.md.
