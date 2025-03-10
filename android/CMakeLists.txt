cmake_minimum_required(VERSION 3.22.0)

project(tunityopus VERSION 2.0.0 LANGUAGES C CXX)

# This is important to keep, as source file removal (REMOVE_ITEM) below will fail if defined in some other way
set(ROOT_DIR "${CMAKE_SOURCE_DIR}/..")

# Include the required source files (from silk_sources.mk, celt_sources.mk, opus_sources.mk)
file(GLOB SILK_SOURCES ${ROOT_DIR}/silk/*.c ${ROOT_DIR}/silk/fixed/*.c)
file(GLOB CELT_SOURCES ${ROOT_DIR}/celt/*.c)
file(GLOB OPUS_SOURCES ${ROOT_DIR}/src/*.c)

# Exclude unneeded demo files that contain main() functions and sabotage the build
list(REMOVE_ITEM CELT_SOURCES ${ROOT_DIR}/celt/opus_custom_demo.c)
list(REMOVE_ITEM OPUS_SOURCES ${ROOT_DIR}/src/opus_compare.c ${ROOT_DIR}/src/opus_demo.c)

# Include the header files (from silk_headers.mk, celt_headers.mk, opus_headers.mk)
include_directories(${ROOT_DIR}/include)
include_directories(${ROOT_DIR}/celt)
include_directories(${ROOT_DIR}/silk)
include_directories(${ROOT_DIR}/silk/fixed)

# Create the shared library from JNI and Opus sources
add_library(tunityopus SHARED opusjni.c ${SILK_SOURCES} ${CELT_SOURCES} ${OPUS_SOURCES})

# Define the target libraries to link with (libm and Android log library)
target_link_libraries(tunityopus log)

# Define compile flags
target_compile_options(tunityopus PRIVATE
    -DNULL=0
    -DSOCKLEN_T=socklen_t
    -DLOCALE_NOT_USED
    -D_LARGEFILE_SOURCE=1
    -D_FILE_OFFSET_BITS=64
    -D__EMX__
    -DOPUS_BUILD
    -DFIXED_POINT
    -DDISABLE_FLOAT_API
    -DUSE_ALLOCA
    -DHAVE_LRINT
    -DHAVE_LRINTF
    -O3
    -fno-math-errno
    -fPIE
    -ffast-math
    -funroll-loops
    -fPIC
)

# Strip the shared object after it's built
add_custom_command(TARGET tunityopus
    POST_BUILD
    COMMAND ${CMAKE_STRIP} --strip-unneeded $<TARGET_FILE:tunityopus>
    COMMENT "Stripping the final Android shared object (libtunityopus.so)"
)
