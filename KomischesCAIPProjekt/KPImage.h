#pragma once
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Tools.h"

using namespace std;
using namespace cv;


class KPImage : public cv::Mat {
	
private:
	string internalname;

public:
	const QImage getQ();
	void setName(const string& n);
	KPImage();
	KPImage(Mat m);
	KPImage(QImage& data);
	KPImage(const string name);
	KPImage(int w, int h);
	bool saveToDisk(const string name);
};

