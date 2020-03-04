#include "KPImage.h"

const QImage KPImage::getQ() {

	QImage* imgIn = new QImage((uchar*)this->data, this->cols, this->rows, this->step, QImage::Format(Tools::Type_CV2Q(this->type)));
	return *imgIn;
}

void KPImage::setName(const string& n) {
	this->internalname = n;
}

KPImage::KPImage() : Mat(1,1, CV_8UC3) {
}

KPImage::KPImage(Mat m) : Mat(m) {
}

KPImage::KPImage(QImage& data) : Mat(data.height(), data.width(), Tools::Type_Q2CV(data.format()), data.bits(), data.bytesPerLine()) {
	
}

KPImage::KPImage(const string name) : Mat(imread(name)), internalname(name) {
	
	
}

KPImage::KPImage(int w, int h) : Mat(w, h, CV_8UC3) {

}

bool KPImage::saveToDisk(const string name) {
	return false;
}

