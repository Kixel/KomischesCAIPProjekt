#pragma once

#include <QWidget>
#include "ui_KPImageView.h"
#include "KPImage.h"
#include "KPGraphicsScene.h"

class KPImageView : public QWidget
{
	Q_OBJECT

public:
	KPImageView(QWidget *parent = Q_NULLPTR);
	~KPImageView();

	void setImage(KPImage& img, const int& ID);
	void fit(KPImage& img, const bool current); 
	void fitToCurrent();
	const int getID();

	//Events
	void resizeEvent(QResizeEvent* event);
private:
	Ui::KPImageView ui;

	//Fields
	KPGraphicsScene kpgs;
	QImage currentImage;
	int currentImageID;
	
	//private methods
	void updateStats();

};
