#include "ImProc.h"

KPImage ImProc::invert(KPImage& O) {
	return KPImage();
}

KPImage ImProc::crop(KPImage& O, int startx, int starty, int endx, int endy) {
	return KPImage();
}

KPImage ImProc::gamma(KPImage& O, double gammavalue) {
	/*double max = 255;
	KPImage work = KPImage(O.getM().clone());
	for (int i1 = 0; i1 < work.getM().rows; i1++) {
		for (int i2 = 0; i2 < work.getM().cols; i2++) {
			switch (work.getM().type()) {
			case CV_8UC1:
			{
				unsigned char& c = work.getM().at<uchar>(i1, i2);
				c = (uchar)((pow(((double)c / max), gammavalue)) * max);
				break;
			}
			case CV_8UC3:
			{
				Vec3b& a = work.getM().at<Vec3b>(i1, i2);
				for (int i3 = 0; i3 < 3; i3++) {
					uchar& b = a.val[i3];
					b = (uchar)(pow(((double)b / 255.0), gammavalue));
				}
				break;
			}
			case CV_8UC4:

				break;
			}
		}
	}
	return work;*/
	return KPImage();
}

KPImage ImProc::contrast(KPImage& O, int startg, int endg) {
	return KPImage();
}

KPImage ImProc::binarise(KPImage& O, int thresh) {
	return KPImage();
}

KPImage ImProc::binarise2(KPImage& O, int threshlower, int threshhigher) {
	return KPImage();
}

KPImage ImProc::adaptthresh(KPImage& O, int range, double correctionvalue) {
	return KPImage();
}

KPImage ImProc::filter(KPImage& O, Mat mask, int maskcenterx, int maskcentery, int outofbounds) {
	return KPImage();
}

vector<int> ImProc::grayhisto(KPImage& O) {
	return vector<int>();
}

KPImage ImProc::convert2Gray(KPImage& O) {
	return KPImage();
}

KPImage ImProc::rotate(KPImage& O, double angle) {
	return KPImage();
}

KPImage ImProc::resize(KPImage& O, int w, int h, cv::InterpolationFlags) {
	return KPImage();
}

KPImage ImProc::erode(KPImage& O, Mat structure) {
	return KPImage();
}

KPImage ImProc::dilate(KPImage& O, Mat structure) {
	return KPImage();
}

KPImage ImProc::open(KPImage& O, Mat structure) {
	return KPImage();
}

KPImage ImProc::close(KPImage& O, Mat structure) {
	return KPImage();
}

KPImage ImProc::create_Gradientfast(int w, int h, bool toptodown) {
	return KPImage();
}

KPImage ImProc::create_Gradientslow(int w, int h, bool toptodown) {
	return KPImage();
}

KPImage ImProc::create_Colornoise(int w, int h) {
	return KPImage();
}

KPImage ImProc::create_Graynoise(int w, int h) {
	return KPImage();
}

KPImage ImProc::create_Colorperlin(int w, int h, int seed) {
	return KPImage();
}

KPImage ImProc::create_Grayperlin(int w, int h, int seed) {
	return KPImage();
}
