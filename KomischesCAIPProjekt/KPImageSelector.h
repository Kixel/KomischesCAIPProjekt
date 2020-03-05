#pragma once

#include <QPushButton>
#include "ui_KPImageSelector.h"
#include "KPImage.h"

class KPImageSelector : public QPushButton
{
	Q_OBJECT

public:
	KPImageSelector(QWidget *parent = Q_NULLPTR);
	KPImageSelector(int ID, KPImage* image, QWidget* parent = Q_NULLPTR);
	~KPImageSelector();

	int getID();
	void setImage(KPImage* image);

private:
	Ui::KPImageSelector ui;
	int ID;
};
