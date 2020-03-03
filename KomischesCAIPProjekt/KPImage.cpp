#include "KPImage.h"

const QImage KPImage::getQ() {

	QImage* imgIn = new QImage((uchar*)this->data, this->cols, this->rows, this->step, QImage::Format(Tools::Type_CV2Q(this->type)));
	return *imgIn;
}

KPImage::KPImage(string name) : Mat(imread(name))
{
	
	
}
