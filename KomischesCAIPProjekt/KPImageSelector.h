#pragma once

#include <QPushButton>
#include "ui_KPImageSelector.h"
#include "KPImage.h"

class KPImageSelector : public QPushButton
{
	Q_OBJECT

public:
	KPImageSelector(QWidget *parent = Q_NULLPTR);
	KPImageSelector(KPImage* image, QWidget* parent = Q_NULLPTR);
	~KPImageSelector();

private:
	Ui::KPImageSelector ui;
};
