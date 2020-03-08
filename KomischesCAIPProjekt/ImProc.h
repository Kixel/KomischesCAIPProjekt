#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include "KPImage.h"
#include "PerlinNoise.h"
#include <iostream>
#include "KPProcessingWindow.h"

class ImProc
{
public:
	//enums
	enum OOBHandling {replicate = -1, allblack = -2, allwhite = -3, mean = -4, median = -5, circular = -6, symmetric = -7};

	//Image Processing custom
	static KPImage* invert(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* crop(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* crop(KPImage* O, int x, int y, int wi, int hi);
	static KPImage* gamma(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* contrast(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* binarise(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* binarise2(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* adaptthresh(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* filter(KPImage* O, Mat mask, int maskcenterx, int maskcentery, int outofbounds = replicate);
	static vector<int>* grayhisto(KPImage* O);
	static vector<vector<int>>* colorhisto(KPImage* O);

	//Filtering
	static KPImage* filter_mean(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* filter_meanS(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* filter_meanCV(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* filter_median(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* filter_gauss(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* filter_edge(KPImage* O, KPProcessingWindow* kpp);

	//Image Processing via lib
	static KPImage* convert2Gray(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* rotate  (KPImage* O, KPProcessingWindow* kpp);
	static KPImage* resize	(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* erode   (KPImage* O, KPProcessingWindow* kpp);
	static KPImage* dilate	(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* open	(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* close	(KPImage* O, KPProcessingWindow* kpp);
	static KPImage* morphgradient(KPImage* O, KPProcessingWindow* kpp);

	//Image creation
	static KPImage* create_Gradientfast(int w, int h, bool toptodown, bool invert);
	static KPImage* create_Gradientslow(int w, int h, bool toptodown, bool invert);
	static KPImage* create_Colornoise(int w, int h);
	static KPImage* create_Graynoise(int w, int h);
	static KPImage* create_Colorperlin(int w, int h, unsigned int seed, double zoomfactor);
	static KPImage* create_Grayperlin(int w, int h, unsigned int seed , double zoomfactor);

	static int otsu(KPImage* im);
};

