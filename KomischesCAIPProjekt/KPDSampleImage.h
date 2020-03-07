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
	KPDSampleImage(string genname = "Generic", bool needsdirection = false, bool needsinvert = false, bool needsspinner = false, bool needsslider=false, QWidget *parent = Q_NULLPTR);
	~KPDSampleImage();

	const int getHeight();
	const int getWidth();
	const int getSeed();
	const bool getDirection();
	const bool getInvert();
	const double getZoom();
	void setGenType(const string a);

private:
	Ui::KPDSampleImage ui;
};



/*
Image Size
options    options
for gray   for perlin


*/