#pragma once

#include <QWindow>
#include "ui_KPImageViewer.h"

class KPImageViewer : public QWindow
{
	Q_OBJECT

public:
	KPImageViewer(QWidget *parent = Q_NULLPTR);
	~KPImageViewer();

private:
	Ui::KPImageViewer ui;
};


/* UI layout
viewer
internal name									
dimensions			dataformat, layers				close button
mouse position		data under mouse
*/