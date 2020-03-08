#pragma once

#include <QPushButton>
#include "ui_KPImageSelector.h"
#include "KPImage.h"
#include "QMouseEvent"

class KPImageSelector : public QPushButton
{
	Q_OBJECT

public:
	KPImageSelector(QWidget *parent = Q_NULLPTR);
	KPImageSelector(int ID, KPImage* image, QWidget* parent = Q_NULLPTR);
	~KPImageSelector();

	int getID();
	void setImage(KPImage* image);

	void setActive(bool act);

	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);

private:
	Ui::KPImageSelector ui;
	int ID;

signals:
	void leftclick(int i);
	void middleclick(int i);
	void rightclick(int i);
	void mouseHovering();
};
