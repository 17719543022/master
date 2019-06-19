cmake_minimum_required(VERSION 2.8)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

ADD_DEFINITIONS(-DLINUX)

#project name
PROJECT(FaceSDKTest_Project)

#head file path
INCLUDE_DIRECTORIES(
	Source/include
	Source/include/base
	Source/include/singleton
	Export/face/Linux/include
	Export/googletest-release-1.6.0/include
)

#source directory
AUX_SOURCE_DIRECTORY(Source/src DIR_SRCS)

#set environment variable
SET(TEST_PATH
	${DIR_SRCS}
)

ADD_SUBDIRECTORY(Source/src/base)
ADD_SUBDIRECTORY(Source/src/singleton)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
set(OpenCV_DIR /usr/local/opencv4/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)

#set link libraries
LINK_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/Export/googletest-release-1.6.0/build
	${CMAKE_CURRENT_SOURCE_DIR}/Export/face/Linux/lib
)

#add executable file
ADD_EXECUTABLE(FaceSDKTest ${TEST_PATH})

SET_TARGET_PROPERTIES(
	FaceSDKTest
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Target"
)

#add link library
TARGET_LINK_LIBRARIES(FaceSDKTest singleton base gtest gtest_main pthread ${OpenCV_LIBS} ISFaceSDK)

