#pragma once

#include <QDialog>
#include "ui_KPDSampleImage.h"

class KPDSampleImage : public QDialog
{
	Q_OBJECT

public:
	KPDSampleImage(bool needscheckbox, bool needsspinner, QWidget *parent = Q_NULLPTR);
	~KPDSampleImage();

private:
	Ui::KPDSampleImage ui;
};



/*
Image Size
options    options
for gray   for perlin


*/