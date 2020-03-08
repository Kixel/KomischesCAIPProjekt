#include "KPImageSelector.h"
#include <iostream>

KPImageSelector::KPImageSelector(QWidget *parent)
	: QPushButton(parent)
{
	ui.setupUi(this);
	this->setFixedSize(100, 100);
}

KPImageSelector::KPImageSelector(int ID, KPImage* image, QWidget* parent)
	: QPushButton(parent), ID(ID)
{
	ui.setupUi(this);
	this->setFixedSize(100, 100);
	this->setImage(image);
	this->setIconSize(QSize(90, 90));
}

KPImageSelector::~KPImageSelector()
{
}

int KPImageSelector::getID() {
	return this->ID;
}

void KPImageSelector::setImage(KPImage* image) {
	this->setIcon(QPixmap::fromImage(image->getQ()));
}

void KPImageSelector::setActive(bool act) {
	if (act) {
		setStyleSheet("border-style: outset; border-width:5px; border-color:red;");
	} else {
		setStyleSheet("");
	}
}

void KPImageSelector::mouseReleaseEvent(QMouseEvent* e) {
	if(e->button() == Qt::LeftButton) {
		emit leftclick(ID);
	}
	if (e->button() == Qt::RightButton) {
		emit rightclick(ID);
	}
	if (e->button() == Qt::MiddleButton) {
		cout << "middleclicked" << endl;
		emit middleclick(ID);
	}


	QPushButton::mouseReleaseEvent(e);
}

void KPImageSelector::mouseMoveEvent(QMouseEvent* e) {
	emit mouseHovering();
	QPushButton::mouseMoveEvent(e);
}
