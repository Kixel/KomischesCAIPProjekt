#pragma once

#include <QDialog>
#include "ui_KPFilterPreDialog.h"

class KPFilterPreDialog : public QDialog
{
	Q_OBJECT

public:
	KPFilterPreDialog(QWidget *parent = Q_NULLPTR);
	~KPFilterPreDialog();

	int getW();
	int getH();
		

private:
	Ui::KPFilterPreDialog ui;
};
