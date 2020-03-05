#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "KPImage.h"

class ImProc
{
public:
	//enums
	enum OOBHandling {replicate = -1, allblack = -2, allwhite = -3, mean = -4, median = -5, circular = -6, symmetric = -7};

	//Image Processing custom
	static KPImage* invert(KPImage* O);
	static KPImage* crop(KPImage* O, int startx, int starty, int endx, int endy);
	static KPImage* gamma(KPImage* O, double gammavalue);
	static KPImage* contrast(KPImage* O, int startg = 0, int endg = 255);
	static KPImage* binarise(KPImage* O, int thresh);
	static KPImage* binarise2(KPImage* O, int threshlower, int threshhigher);
	static KPImage* adaptthresh(KPImage* O, int range, double correctionvalue);
	static KPImage* filter(KPImage* O, Mat mask, int maskcenterx, int maskcentery, int outofbounds = replicate);
	static vector<int> grayhisto(KPImage* O);

	//Image Processing via openCV
	static KPImage* convert2Gray(KPImage* O);
	static KPImage* rotate  (KPImage* O, double angle);
	static KPImage* resize	(KPImage* O, int w, int h, cv::InterpolationFlags);
	static KPImage* erode	(KPImage* O, Mat structure);
	static KPImage* dilate	(KPImage* O, Mat structure);
	static KPImage* open	(KPImage* O, Mat structure);
	static KPImage* close	(KPImage* O, Mat structure);

	//Image creation
	static KPImage* create_Gradientfast(int w, int h, bool toptodown);
	static KPImage* create_Gradientslow(int w, int h, bool toptodown);
	static KPImage* create_Colornoise(int w, int h);
	static KPImage* create_Graynoise(int w, int h);
	static KPImage* create_Colorperlin(int w, int h, int seed);
	static KPImage* create_Grayperlin(int w, int h, int seed);
};

