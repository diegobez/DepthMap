#include "stdafx.h"

#include "./frei0r/frei0r.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include <fstream>
#include <stdio.h>


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

		pixelizerInfo->name = "Filter"; //todo : name
		pixelizerInfo->author = "Enrique-Diego";  //todo : author
		pixelizerInfo->plugin_type = F0R_PLUGIN_TYPE_FILTER;
		pixelizerInfo->color_model = F0R_COLOR_MODEL_BGRA8888;
		pixelizerInfo->frei0r_version = FREI0R_MAJOR_VERSION;
		pixelizerInfo->major_version = 1;
		pixelizerInfo->minor_version = 0;
		pixelizerInfo->num_params = 8;
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
		memcpy(outframe, inframe, width * height * 32);
		//todo : fill outframe with image data.
		//Mat cvSrc(height, width, CV_8UC4, inframe);
		//Mat cvDst(height, width, CV_8UC4, outframe);
		return;
	}

}

