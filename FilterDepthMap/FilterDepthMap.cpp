// FilterDepthMap.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include "./frei0r/frei0r.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include <fstream>
#include <stdio.h>

#include <StereoManager.h>

int idx = 0;
int zeromultiplier = 4;

extern "C"
{

	typedef struct pixelizer_instance
	{
		unsigned int width;
		unsigned int height;
	} pixelizer_instance_t;

	__declspec(dllexport) int f0r_init()
	{
		return 1;
	}

	__declspec(dllexport) void f0r_deinit()
	{ /* no initialization required */
	}

	__declspec(dllexport) void f0r_get_plugin_info(f0r_plugin_info_t* pixelizerInfo)
	{

		pixelizerInfo->name = "FilterDepthMap"; //todo : name
		pixelizerInfo->author = "Enrique-Diego";  //todo : author
		pixelizerInfo->plugin_type = F0R_PLUGIN_TYPE_FILTER;
		pixelizerInfo->color_model = F0R_COLOR_MODEL_BGRA8888;
		pixelizerInfo->frei0r_version = FREI0R_MAJOR_VERSION;
		pixelizerInfo->major_version = 1;
		pixelizerInfo->minor_version = 0;
		pixelizerInfo->num_params = 0;
		pixelizerInfo->explanation = "Depthmap from stereo"; //todo : stereo
	}

	__declspec(dllexport) void f0r_get_param_info(f0r_param_info_t* info, int param_index)
	{

	}

	__declspec(dllexport) f0r_instance_t f0r_construct(unsigned int width, unsigned int height)
	{
		pixelizer_instance_t* inst = (pixelizer_instance_t*)calloc(1, sizeof(*inst));
		inst->width = width; inst->height = height;
		return (f0r_instance_t)inst;
	}

	__declspec(dllexport) void f0r_destruct(f0r_instance_t instance)
	{
		free(instance);
	}

	__declspec(dllexport) void f0r_set_param_value(f0r_instance_t instance,
		f0r_param_t param, int param_index)
	{
		assert(instance);
		pixelizer_instance_t* inst = (pixelizer_instance_t*)instance;
	}



	__declspec(dllexport) void f0r_get_param_value(f0r_instance_t instance,
		f0r_param_t param, int param_index)
	{
		assert(instance);
		pixelizer_instance_t* inst = (pixelizer_instance_t*)instance;

	}

	__declspec(dllexport) void f0r_update(f0r_instance_t instance, double time,
		uint32_t* inframe, uint32_t* outframe)
	{
		assert(instance);
		pixelizer_instance_t* inst = (pixelizer_instance_t*)instance;
		int width = inst->width;
		int height = inst->height;
		uint32_t* inframe1 = inframe;
		uint32_t* inframe2 = &(inframe[width*height/2]);

		//1- Reading left and right image from frame of video

		Mat imgL, imgR;
		Mat gcvSrc, gcvSrc1, gcvSrc2;
		Mat gNewImg, NewImg;

		Mat cvSrc(height, width, CV_8UC4, inframe);
		Mat cvSrc1(height / 2, width, CV_8UC4, inframe1);
		Mat cvSrc2(height / 2, width, CV_8UC4, inframe2);
		//2- Turning them from bgr to gray

		cvtColor(cvSrc, gcvSrc, CV_BGR2GRAY);
		cvtColor(cvSrc1, gcvSrc1, CV_BGR2GRAY);
		cvtColor(cvSrc2, gcvSrc2, CV_BGR2GRAY);

		//3- Generating depthmap img

		StereoManager* sm = new StereoManager();
		sm->generateDepthMap(gcvSrc1, gcvSrc2, gNewImg, BaseStereo::STEREO_3WAY, true);

		//NO VERY GOOD- writes every frame in a folder to generate video after

		/*
		std::string zero = "";

		for (int i = 0; i < zeromultiplier; i++) {

			int m=10;
			for (int j = 0; j < i; j++)
				m = m * 10;

			if (idx / m < 1)
				zero = zero + "0";
		}
		


		std::string idx_c = std::to_string(idx);
		std::string idx_s = "videoFrames/Frame"+zero+idx_c+".png";
		imwrite(idx_s.c_str(), gNewImg);
		idx++;
		*/
		
		gNewImg.convertTo(NewImg, CV_8UC4);

		cvtColor(gNewImg, NewImg, CV_GRAY2BGRA);

		//imwrite("FrameIMG.png", NewImg);

		//printf("Mat input Left data: COL %d, ROW %d, CHA %d \n", cvSrc1.cols, cvSrc1.rows, cvSrc1.channels());
		//printf("Mat output data: COL %d, ROW %d, CHA %d \n", NewImg.cols, NewImg.rows, NewImg.channels());
		memcpy(outframe, NewImg.data, (width * height*2 ));
		//memcpy(outframe, NewImg.data, (width * height * 4)/2);
		return;
	}


}
