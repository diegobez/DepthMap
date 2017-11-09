#include "stdafx.h"



/*#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>*/


#include <assert.h> 

#include <stdio.h>
#include <iostream>
#include <BaseStereoBM.h>
#include <BaseStereoSGBM.h>

#include "StereoManager.h"

StereoManager::StereoManager()
{
}


bool StereoManager::generateDepthMap(std::string imgL, std::string imgR, std::string newImage, int alg, std::string path, int disparity, int blockSize)
{

	if (alg == BaseStereo::STEREO_BM) {
		 baseStereo = new BaseStereoBM();
	}
	else {
		baseStereo = new BaseStereoSGBM();
	}
	baseStereo->rectifyImagesCameraNoCalibrated(path + imgL, path + imgR);

	baseStereo->compute(path+imgL, path+imgR, path+newImage, alg, disparity, blockSize);

	return true;
}


StereoManager::~StereoManager()
{
}
