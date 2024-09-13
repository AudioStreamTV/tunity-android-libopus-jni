#!/bin/bash

architectures=("arm64-v8a" "armeabi-v7a" "x86_64" "x86")

check_env_var() {
    local var_name=$1
    local var_value=$2
    if [ -z "$var_value" ]; then
        echo "Error: $var_name is not defined. Please set it and try again."
        exit 1
    fi
}

check_env_var "TUNITY_ROOT" "$TUNITY_ROOT"

for arch in "${architectures[@]}"; do
    cp -v "build/$arch"/* "$TUNITY_ROOT/Tunityapp/app/src/main/jniLibs/$arch"
done

