#include "stdafx.h"


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
	//baseStereo->rectifyImagesCameraNoCalibrated(path + imgL, path + imgR);

	baseStereo->compute(path+imgL, path+imgR, path+newImage, alg, disparity, blockSize);

	return true;
}


StereoManager::~StereoManager()
{
}
