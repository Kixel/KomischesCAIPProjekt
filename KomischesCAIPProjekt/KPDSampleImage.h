#pragma once

#include <QDialog>
#include "ui_KPDSampleImage.h"
#include <string>
#include "Tools.h"

using namespace std;

class KPDSampleImage : public QDialog
{
	Q_OBJECT

public:
	KPDSampleImage(bool needsdirection, bool needsinvert, bool needsspinner, string genname = "Generic", QWidget *parent = Q_NULLPTR);
	~KPDSampleImage();

	const int getHeight();
	const int getWidth();
	const int getSeed();
	const bool getDirection();
	const bool getInvert();
	void setGenType(const string a);

private:
	Ui::KPDSampleImage ui;
};



/*
Image Size
options    options
for gray   for perlin


*/