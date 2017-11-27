#pragma once
#include "BaseStereo.h"
class BaseStereoSGBM :
	public BaseStereo
{
private:
	Ptr<StereoSGBM> sgbm;


public:

	virtual void compute(const Mat& imgL, const Mat& imgR, Mat& newImage, const int alg, const bool is360, const int disparity, const int blockSize) override;

	BaseStereoSGBM();
	~BaseStereoSGBM();
};

