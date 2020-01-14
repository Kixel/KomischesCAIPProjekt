#include "KPImage.h"

QImage KPImage::getQ() {
	QImage imgIn = QImage((uchar*)this->data, this->cols, this->rows, this->step, QImage::Format_RGB888);
	return imgIn;
}
