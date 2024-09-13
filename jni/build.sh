#!/bin/bash

original_dir=$(pwd)
architectures=("arm64-v8a" "armeabi-v7a" "x86_64" "x86")

clean_build_dir() {
  rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
}

check_env_var() {
    local var_name=$1
    local var_value=$2
    if [ -z "$var_value" ]; then
        echo "Error: $var_name is not defined. Please set it and try again."
        exit 1
    fi
}

build_opus_for_arch() {
  local build_arch=$1
  clean_build_dir
  cmake -DANDROID_ABI=$build_arch -DANDROID_PLATFORM=android-29 -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/$NDK_VERSION/build/cmake/android.toolchain.cmake ..
  make -j
  mkdir $build_arch
  mv libtunityopus.so $build_arch
}

# Check required environment variables
check_env_var "ANDROID_SDK_ROOT" "$ANDROID_SDK_ROOT"
check_env_var "ANDROID_NDK_ROOT" "$ANDROID_NDK_ROOT"
check_env_var "NDK_VERSION" "$NDK_VERSION"

# Prepare build directory if it doesn't exist yet and enter it
rm -rf build
mkdir build
cd build

# Build all targets
for arch in "${architectures[@]}"; do
  build_opus_for_arch $arch
done

# Clean up and show targets
clean_build_dir
tree
for arch in "${architectures[@]}"; do
  file $arch/*
done

cd $original_dir
