#pragma once
class DetTrackImp
{
public:
	DetTrackImp(void);
	~DetTrackImp(void);

	static DetTrackImp* GetInstance();

	int CreateChannel();

	int DestoryChannel();

	int FaceDetect(char* img, int imgLen, int& faceNum);

	int FaceDetectByPath(const char* path, int& faceNum);

private:

	int _detTrackChannel;
};

