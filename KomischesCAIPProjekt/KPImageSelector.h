#pragma once

#include <QPushButton>
#include "ui_KPImageSelector.h"

class KPImageSelector : public QPushButton
{
	Q_OBJECT

public:
	KPImageSelector(QWidget *parent = Q_NULLPTR);
	~KPImageSelector();

private:
	Ui::KPImageSelector ui;
};
