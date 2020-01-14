#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KomischesCAIPProjekt.h"

class KomischesCAIPProjekt : public QMainWindow
{
	Q_OBJECT

public:
	KomischesCAIPProjekt(QWidget *parent = Q_NULLPTR);

private:
	Ui::KomischesCAIPProjektClass ui;
};
