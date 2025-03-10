#!/bin/bash
cmake .. -G "Unix Makefiles" -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_ARCHITECTURES=arm64
make -j$(sysctl -n hw.logicalcpu)
strip libopus.a

# This uses XCode for building
# cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS
# xcodebuild -project Opus.xcodeproj -scheme ALL_BUILD -configuration Release -sdk iphoneos
# strip Release-iphoneos/libopus.a
