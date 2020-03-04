#pragma once
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Tools.h"

using namespace std;
using namespace cv;


class KPImage {
	
private:
	string internalname;
	Mat im;

public:
	KPImage();
	KPImage(Mat m);
	KPImage(QImage& data);
	KPImage(const string name);
	KPImage(int w, int h);

	QImage& getQ();
	KPI& getM();
	void setName(const string& n);
	
	bool saveToDisk(const string name);
};

