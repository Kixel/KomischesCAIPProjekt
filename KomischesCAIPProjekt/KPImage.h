#pragma once
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Tools.h"

using namespace std;
using namespace cv;


class KPImage : public cv::Mat {
	
private:

public:
	const QImage getQ();
	KPImage(string name);

};

