#pragma once
/*#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"*/

#include <stdio.h>
#include <BaseStereo.h>

//using namespace cv;


class StereoManager
{
private:

	BaseStereo*		baseStereo;

	//Functions

	bool createBM();
	bool createSGBM();
	void display();
	void rectifyImagesCameraNoCalibrated();

public:
	//static enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_3WAY = 3 };
	StereoManager();
	//StereoManager(std::string n_img1, std::string n_img2, std::string n_outputName, std::string n_path, int n_numOfDisparities,int n_SADWindowSize,int n_alg);
	bool generateDepthMap(std::string imgL, std::string imgR, std::string newImage, int alg = BaseStereo::STEREO_SGBM,  std::string path="", int disparity=16*4, int blockSize=21);


	~StereoManager();
};

