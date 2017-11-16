#pragma once
#include <iostream>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
//#include "opencv2/core/utility.hpp"
using namespace cv;


class BaseStereo
{
protected:
	
	void display(Mat &img);
	void cropImage(Mat &img, Mat &cropImg);

public:
	static enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_3WAY = 3 };
	BaseStereo();
	~BaseStereo();
	virtual void compute(std::string imgL, std::string imgR, std::string newImage, int alg, int disparity, int blockSize) = 0;
	void rectifyImagesCameraNoCalibrated(std::string imgL, std::string imgR);

};

