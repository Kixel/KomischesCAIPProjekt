#pragma once

#include <QWidget>
#include "ui_KPImageView.h"
#include "KPImage.h"
#include "KPGraphicsScene.h"
#include <iostream>

class KPImageView : public QWidget
{
	Q_OBJECT

public:
	KPImageView(QWidget *parent = Q_NULLPTR);
	~KPImageView();

	void setImage(KPImage* img, const int& ID);
	void fit(KPImage* img, const bool current); 
	void fitToCurrent();
	const int getID();

	//Events
	void resizeEvent(QResizeEvent* event);

signals:
	void windowactivated(int id);
	void closethis(int id);

private:
	Ui::KPImageView ui;

	//Fields
	KPGraphicsScene kpgs;
	KPImage* currentImage;
	int currentImageID;
	
	//private methods
	void updateStats();

	
	

	//overrides
	bool event(QEvent* e);

private slots:
	void mouseHoverUpdater(int x, int y);
	void on_actionDismiss_clicked();
	void on_actionHide_clicked();

};
