# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

######## OpenCV #######

# External library
set( OpenCV_DIR /home/user/OpenCV-android-sdk/sdk/native/jni )
find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})

######## end OpenCV #######

include_directories(src/main/cpp/)

# My own class
add_library( # Sets the name of the library.
        yolo

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/Yolo.cpp
        src/main/cpp/YoloJNI.cpp )

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

target_link_libraries( # Specifies the target library.
        yolo

        # Links the target library to the log library
        # included in the NDK.
        ${OpenCV_LIBS}
        ${log-lib} )