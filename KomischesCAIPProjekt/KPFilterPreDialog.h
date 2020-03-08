#pragma once

#include <QDialog>
#include "ui_KPFilterPreDialog.h"

class KPFilterPreDialog : public QDialog
{
	Q_OBJECT

public:
	KPFilterPreDialog(QWidget *parent = Q_NULLPTR);
	~KPFilterPreDialog();

private:
	Ui::KPFilterPreDialog ui;
};
