#pragma once
#include "BaseStereo.h"
class BaseStereoSGBM :
	public BaseStereo
{
private:
	Ptr<StereoSGBM> sgbm;


public:

	virtual void compute(std::string imgL, std::string imgR, std::string newImage, int alg, int disparity, int blockSize) override;

	BaseStereoSGBM();
	~BaseStereoSGBM();
};

