#pragma once

#include <QWidget>
#include "ui_KPProcessingWindow.h"

class KPProcessingWindow : public QWidget
{
	Q_OBJECT

public:
	KPProcessingWindow(QWidget *parent = Q_NULLPTR);
	~KPProcessingWindow();

private:
	Ui::KPProcessingWindow ui;
};
