
#include "./frei0r/frei0r.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>



#include <stdio.h>

#define PI 3.14159265358979323846

using namespace cv;
using namespace std;

//Mat cvSrc, cvDst;
Mat map_x, map_y;// , map_x2, map_y2, map_x3, map_y3;        // Preguntar a Diego: variables globales?????
//float f;
//float k0, k1, k2, k3, k4;
//int ix, jx, iy, jy;
//bool mapMade;


extern "C"
{

	//void WriteMap(string fileName, Mat& map);
	//void ReadMap(string fileName, Mat& map);
	//void MirrorMap(Mat& map_x, Mat& map_y, int width, int height);
	//void fishEyeCorrecMap(Mat& map_x, Mat& map_y, int& ix, int& jy, float f, float k0, float k1, float k2, float k3, float k4);
	//void CutImage(Mat& map_x, Mat& map_y, Mat& map_x2, Mat& map_y2, int ix, int jy);
	//void cutImage2(Mat& map_x, Mat& map_y, float fx, int fy);

	typedef struct pixelizer_instance
	{
		unsigned int width;
		unsigned int height;
		unsigned int block_size_x;
		unsigned int block_size_y;




	} pixelizer_instance_t;

	__declspec(dllexport) int f0r_init()
	{

		cv::FileStorage storagerx("mapx.yml", cv::FileStorage::READ);
		cv::FileStorage storagery("mapy.yml", cv::FileStorage::READ);
		storagerx["img"] >> map_x;
		storagerx.release();
		storagery["img"] >> map_y;
		storagery.release();
		printf("\nholaaa. hollaaaaa");
		return 1;
	}

	__declspec(dllexport) void f0r_deinit()
	{ /* no initialization required */
	}

	__declspec(dllexport) void f0r_get_plugin_info(f0r_plugin_info_t* pixelizerInfo)
	{
		pixelizerInfo->name = "Remap_smooth";
		pixelizerInfo->author = "Jorge Diego";
		pixelizerInfo->plugin_type = F0R_PLUGIN_TYPE_FILTER;
		pixelizerInfo->color_model = F0R_COLOR_MODEL_BGRA8888;
		pixelizerInfo->frei0r_version = FREI0R_MAJOR_VERSION;
		pixelizerInfo->major_version = 1;
		pixelizerInfo->minor_version = 0;
		pixelizerInfo->num_params = 8;
		pixelizerInfo->explanation = "Remap_smooth filter";

	}

	__declspec(dllexport) void f0r_get_param_info(f0r_param_info_t* info, int param_index)
	{
		/*switch (param_index)
		{
		case 0:
			info->name = "Block width";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Horizontal size of one \"pixel\"";
			break;
		case 1:
			info->name = "Block height";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Vertical size of one \"pixel\"";
			break;
		case 2:
			info->name = "Folcal";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Focal lenght";
			break;
		case 3:
			info->name = "k0";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Distorsion parameter 0";
			break;
		case 4:
			info->name = "k1";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Distorsion parameter 1";
			break;
		case 5:
			info->name = "k2";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Distorsion parameter 2";
			break;
		case 6:
			info->name = "k3";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Distorsion parameter 3";
			break;
		case 7:
			info->name = "k4";
			info->type = F0R_PARAM_DOUBLE;
			info->explanation = "Distorsion parameter 4";
			break;

		}*/
	}

	__declspec(dllexport) f0r_instance_t f0r_construct(unsigned int width, unsigned int height)
	{
		pixelizer_instance_t* inst = (pixelizer_instance_t*)calloc(1, sizeof(*inst));
		inst->width = width; inst->height = height;
		printf("\nconstruct");


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

		//switch (param_index)
		//{
		//case 0:
		//	// scale to [1..width]
		//	inst->block_size_x = 1;
		//	break;
		//case 1:
		//	// scale to [1..height]
		//	inst->block_size_y = 1;
		//	break;
		//case 2:

		//	f = *((double*)param);
		//	break;
		//case 3:

		//	k0 = *((double*)param);
		//	break;
		//case 4:

		//	k1 = *((double*)param);
		//	break;
		//case 5:

		//	k2 = *((double*)param);
		//	break;
		//case 6:

		//	k3 = *((double*)param);
		//	break;
		//case 7:

		//	k4 = *((double*)param);
		//	break;
		//}

	}






	__declspec(dllexport) void f0r_get_param_value(f0r_instance_t instance,
		f0r_param_t param, int param_index)
	{
		assert(instance);
		pixelizer_instance_t* inst = (pixelizer_instance_t*)instance;

		//switch (param_index)
		//{
		//case 0:
		//	// scale back to [0..1]
		//	*((double*)param) = 1;
		//	break;
		//case 1:
		//	// scale back to [0..1]
		//	*((double*)param) = 1;
		//	break;
		//case 2:

		//	*((double*)param) = f;
		//	break;
		//case 3:

		//	*((double*)param) = k0;
		//	break;
		//case 4:

		//	*((double*)param) = k1;
		//	break;
		//case 5:

		//	*((double*)param) = k2;
		//	break;
		//case 6:

		//	*((double*)param) = k3;
		//	break;
		//case 7:

		//	*((double*)param) = k4;
		//	break;
		//}
	}

	__declspec(dllexport) void f0r_update(f0r_instance_t instance, double time,
		uint32_t* inframe, uint32_t* outframe)
	{
		assert(instance);
		pixelizer_instance_t* inst = (pixelizer_instance_t*)instance;
		int width = inst->width;
		int height = inst->height;
		/*int w = 0;
		int h = 0;
		float a, b;*/
		Mat cvSrc(height, width, CV_8UC4, inframe);
		Mat cvDst(height, width, CV_8UC4, outframe);

		//printf("\nupdate");

		remap(cvSrc, cvDst, map_x, map_y, INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
		//memcpy(outframe, cvDst.data, height * width * sizeof(uint32_t));


	//	if (mapMade == false)
	//	{

	//		map_x.create(cvSrc.size(), CV_32FC1);
	//		map_y.create(cvSrc.size(), CV_32FC1);


	//		fishEyeCorrecMap(map_x, map_y, ix, jy, f, k0, k1, k2, k3, k4);
	//

	//		 h = (int)((height ) - (2 * jy));
	//		 w = (int)((width ) - (2 * ix));
	//	

	//		// cvDst.create(cvSrc.size(), cvSrc.type());


	//		Mat cvDst(h, w, CV_8UC4);

	//		map_x2.create(cvDst.size(), CV_32FC1);
	//		map_y2.create(cvDst.size(), CV_32FC1);


	//		CutImage(map_x, map_y, map_x2, map_y2, ix, jy);



	//		mapMade = true;
	//	}
	//	else
	//	{
	//		ReadMap("map_x_Fish", map_x);
	//		ReadMap("map_y_Fish", map_y);
	//		ReadMap("map_x_Fish2", map_x2);
	//		ReadMap("map_y_Fish2", map_y2);
	//		cvDst.create(cvSrc.size(), cvSrc.type());
	//	}


	//	Mat cvDst2( height * (PI/2), width, CV_8UC4);
	//	Mat cvDst3(height, width, CV_8UC4);
	//	map_x3.create(cvDst3.size(), CV_32FC1);
	//	map_y3.create(cvDst3.size(), CV_32FC1);
	//	
	//	/*remap(cvSrc, cvDst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	//	memcpy(outframe, cvDst.data, width * height * sizeof(uint32_t));*/
	//	
	//	//memcpy(outframe, cvDst.data, map_x2.cols * map_x2.rows * sizeof(uint32_t));

	//	

	//	remap(cvSrc, cvDst, map_x2, map_y2, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//	resize(cvDst, cvDst2, cvDst2.size(), 0, 0, INTER_LINEAR);

	//	float y0, y1;

	//	for (int j = 0; j < height; ++j) 
	//	{

	//		for (int i = 0; i < width; ++i) 
	//		{

	//			
	//			y0 = -((-(height / 2.0f) + (j + 0.5f)));
	//			y1 = asin(y0/(height/2.0f)) * ((PI * height )/ 4.0f);

	//			map_x3.at<float>(j, i) = i;
	//			map_y3.at<float>(j, i) = ((-y1 ) + ((PI * height) /4.0f));
	//			
	//		}
	//	}
	//	WriteMap("map_x_Fish3", map_x3);
	//	WriteMap("map_y_Fish3", map_y3);

	//	remap(cvDst2, cvDst3, map_x3, map_y3, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));


	//	memcpy(outframe, cvDst3.data, height * width * sizeof(uint32_t));

	//}




	//void WriteMap(string fileName, Mat& map)
	//{
	//	fstream myfile(fileName, std::ios_base::out);

	//	if (myfile.fail())
	//	{
	//		cerr << "Error writing map";
	//		exit(1);
	//	}

	//	for (int j = 0; j < map.rows; ++j)
	//	{

	//		for (int i = 0; i < map.cols; ++i)
	//		{
	//			myfile << map.at<float>(j, i) << endl;
	//		}
	//		
	//	}
	//	return;
	//}




	//void ReadMap(string fileName, Mat& map) {

	//	fstream myfile(fileName, std::ios_base::in);
	//	int x, y;


	//	if (myfile.fail())
	//	{
	//		cerr << "Error reading map";
	//		exit(1);
	//	}


	//	for (int j = 0; j < map.rows; ++j)
	//	{
	//		for (int i = 0; i < map.cols; ++i)
	//		{
	//			myfile >> map.at<float>(j, i);
	//		}
	//	}

	//	return;
	//}




	//void fishEyeCorrecMap(Mat& map_x, Mat& map_y, int& ix, int& jy, float f, float k0, float k1, float k2, float k3, float k4)
	//{
	//	float bx, ax, by, ay, newNormW, newNormH, factX, factY;
	//	float xd, yd, xu, yu, theta, thetaD, rd, ru, mod, rNorm;
	//	int width = map_x.cols;
	//	int height = map_y.rows;
	//	float x, y;
	//	float normFactor = width;
	//	int  jx, iy;

	//	ix = 0;
	//	jx = 0;

	//	
	//	ax = 0;
	//	bx = 0;
	//	iy = 0;
	//	jy = 0;

	//
	//	ay = 0;
	//	by = 0;

	//	if (height > width) {

	//		normFactor = height;
	//	}



	//	bx = 5;
	//	ax = (-width/2) - 1;

	//	ay = 5;
	//	by = (height / 2) + 3;

	//	for (int j = 0; j < height; ++j)
	//	{
	//		for (int i = 0; i < width; ++i)
	//		{
	//			// Cambio de origen de coordenadas
	//			
	//			xd = ((-(width / 2.0f) + (i + 0.5f)) / normFactor);
	//			yd = -((-(height / 2.0f) + (j + 0.5f)) / normFactor);

	//			rd = sqrt(pow(xd, 2.0f) + pow(yd, 2.0f));                           //Funciones en float o double?????


	//			theta = f * (atan(rd / f) / rd);


	//			if (theta != 0)
	//			{


	//				thetaD = theta * (1.0f + k0 * pow(theta, 20.0f) + k1 * pow(theta, 2.0f) + k2 * pow(theta, 4.0f) + k3 * pow(theta, 6.0f) + k4 * pow(theta, 8.0f));
	//				//thetaD = theta * (1.0f  + k1 * pow(theta, 2.0f) + k2 * pow(theta, 4.0f) + k3 * pow(theta, 6.0f) + k4 * pow(theta, 8.0f));

	//				xu = (xd * thetaD / 0.8f);
	//				yu = (yd * thetaD / 0.8f); 


	//				x = xu * normFactor;
	//				y = yu * normFactor;

	//				if ((x < -(width / 2)) && (x > ax)  && (pow(y, 2) < pow(bx, 2)))
	//				{
	//					ix = i;
	//					jx = j;

	//					
	//					ax = x;
	//					bx = y;
	//				}


	//				if (y > (height / 2) && (y < by) && (pow(x, 2) < pow(ay, 2)))
	//				{
	//					iy = i;
	//					jy = j;

	//				
	//					ay = x;
	//					by = y;
	//				}					

	//				map_x.at<float>(j, i) = ( x + (width / 2.0f) - 0.5f);
	//				map_y.at<float>(j, i) = ((-y) + (height / 2.0f) - 0.5f);


	//			}
	//			else
	//			{

	//				map_x.at<float>(j, i) = i;
	//				map_y.at<float>(j, i) = j;
	//			}

	//		}
	//	}

		
		return;
	}

/*
	void MirrorMap(Mat& map_x, Mat& map_y, int width, int height)
	{
		for (int j = 0; j < height; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				map_x.at<float>(j, i) = width - i;
				map_y.at<float>(j, i) = j;

			}
		}

		WriteMap("map_x_Mirror", map_x);
		WriteMap("map_y_Mirror", map_y);

		return;
	}



	void CutImage(Mat& map_x, Mat& map_y, Mat& map_x2, Mat& map_y2, int ix, int jy)
	{

		int height = map_x.rows;
		int width = map_y.cols;


		int m, n;

		m = 0;
		for (int j = jy; j < height - jy; ++j)
		{
			n = 0;
			for (int i = ix; i < width - ix; ++i)
			{

				map_x2.at<float>(m, n) =  map_x.at<float>(j, i);
				map_y2.at<float>(m, n) =  map_y.at<float>(j, i);

				n++;
			}
			m++;
		}

		WriteMap("map_x_Fish2", map_x2);
		WriteMap("map_y_Fish2", map_y2);
		
		return;
	}

	void cutImage2(Mat& map_x, Mat& map_y, float fx, int fy) {

		float x, y, xc, yc, ixc, jyc;
	
		int width = map_x.cols;
		int height = map_x.rows;


		for (int j = 0; j < height; ++j)
		{
			
			for (int i = 0; i < width; ++i)
			{
				
				x= map_x.at<float>(j, i);
				y= map_y.at<float>(j, i);
				
				
				xc = ((-(width / 2) + (x)));
				yc = -((-(height / 2) + (y)));

				ixc= ((-(width / 2) + (ix + 0.5)));
				jyc= -((-(height / 2) + (jy + 0.5)));

				xc = xc / (width / ixc);
				yc = yc / (height / 5 * jyc);

				map_x.at<float>(j, i) = (xc + (width / 2));
				map_y.at<float>(j, i)= (-yc + (height / 2));
					
			}
		}

		WriteMap("map_x_Fish", map_x);
		WriteMap("map_y_Fish", map_y);

		return;
	}*/
}



//------------------------------------------------------------------------------------------------------------

// OTROS MODELOS PARA LA CORRECCIÓN DE LA DISTORSCIÓN DEL FISH EYE:

//Odd Polynomial Model
/*
rd = sqrt(pow(xd, 2) + pow(yd, 2));

ru = rd - (rd * ( (k1 * pow(rd, 2) + k2 * pow(rd, 4) + (pow(k1, 2) * pow(rd, 4)) + (pow(k2, 2) * pow(rd, 8)) + 2 * k1 * k2 * pow(rd, 6)) / ( 1 + 4 * k1 * pow(rd, 2) + 6 * k2 * pow(rd, 4))));

if (ru != 0) {

xu = (xd * ru) / rd;
yu = (yd * ru) / rd;

}*/

//The Division Model
//ru= rd / ( 1 + k1 * pow(rd, 2) + k2 * pow(rd, 4) + k3 * pow(rd, 6) + k4 * pow(rd, 8)); 

//The Fish Eye Transform
//ru= (exp(rd / s) - 1) / lambda; 

//FOV
//ru = tan(rd * w) / (2 * tan(w / 2));

// Perspective Model
//ru= f * tan(rd / f);



//------------------------------------------------------------------------------------------------------------


