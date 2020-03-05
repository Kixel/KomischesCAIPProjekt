#include "KPImageSelector.h"

KPImageSelector::KPImageSelector(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	this->setFixedSize(100, 100);
}

KPImageSelector::KPImageSelector(KPImage* image, QWidget* parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	this->setFixedSize(100, 100);
	this->setIcon(QPixmap::fromImage(image->getQ()));
	this->setIconSize(QSize(100, 100));
}

KPImageSelector::~KPImageSelector()
{
}
