CC = g++
CFLAGS	:= -Wall -O3  

OPENCV_INC_ROOT = /usr/local/include
OPENCV_LIB_ROOT = /usr/local/lib
MY_ROOT = ./include

OPENCV_INC= -I $(OPENCV_INC_ROOT)
MY_INC = -I $(MY_ROOT)

EXT_INC = $(OPENCV_INC) $(MY_INC)

OPENCV_LIB_PATH = -L $(OPENCV_LIB_ROOT)
MY_LIB_PATH = -L ./lib

EXT_LIB = $(OPENCV_LIB_PATH) $(MY_LIB_PATH) 

MY_LIB_NAME = -lfacewarp -lfacelanddet -lfeat -lFaceDetector -lFaceTracker -lISFaceSDK
OPENCV_LIB_NAME =  -lopencv_objdetect -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_video 

all:test

test:demo.cpp
	$(CC) $(CFLAGS) demo.cpp $(EXT_INC) $(EXT_LIB) $(MY_LIB_PATH) $(MY_LIB_NAME) $(OPENCV_LIB_PATH) $(OPENCV_LIB_NAME) -o test


