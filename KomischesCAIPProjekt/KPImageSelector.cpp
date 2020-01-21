#include "KPImageSelector.h"

KPImageSelector::KPImageSelector(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	this->setFixedSize(100, 100);
}

KPImageSelector::~KPImageSelector()
{
}
