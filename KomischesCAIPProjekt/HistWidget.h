#pragma once

#include <QWidget>
#include <vector>
#include <QPainter>
//#include <iostream>

using std::vector;

class HistWidget : public QWidget
{
	Q_OBJECT

public:
	HistWidget(vector<vector<int>> source, QWidget *parent = Q_NULLPTR);
	~HistWidget();

	void paintEvent(QPaintEvent* e);

private:
	vector<vector<int>> hist;
};
