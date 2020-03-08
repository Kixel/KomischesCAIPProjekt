#include "HistWidget.h"

HistWidget::HistWidget(vector<vector<int>> source, QWidget *parent)
	: QWidget(parent)
{
	hist = source;
	this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

HistWidget::~HistWidget()
{
}

void HistWidget::paintEvent(QPaintEvent* e) {
	int width = this->width();
	int height = this->height();
	int dims = hist.size();
	int origX = std::max(10, width / 100);
	int origY = std::max(10, height / 100);

	float usableW = width - 2 * origX;
	float usableH = height - 2 * origY;

	float perX = usableW / 256;

	QPainter painter;
	painter.begin(this);
	painter.setPen(QPen(Qt::black, 3));
	QFont f;
	f.setPixelSize(50);
	painter.setFont(f);

	painter.drawLine(origX, origY + usableH, origX, origY);
	painter.drawLine(origX, origY + usableH, origX + usableW, origY + usableH);

	

	int maxv = 0;
	for (int i = 0; i < hist[0].size(); i++) {
		for (int j = 0; j < dims; j++) {
			if (hist[j][i] > maxv) maxv = hist[j][i];
		}
	}
	QPointF points[3][256];
	for (int i = 0; i < hist[0].size(); i++) {
		for (int j = 0; j < dims; j++) {
			float x = (float)origX + (float)i / 256.0 * usableW;
			float y = (float)origY + (float)usableH - ((float)(hist[j][i] / (float)maxv) * (float)usableH);
			//std::cout << x << " " << y << std::endl;
			points[j][i] = QPointF(x, y);
		}
	}
	if (dims == 3) {
		painter.setPen(QPen(Qt::red, 2));
		painter.drawPolyline(points[0], 256);

		painter.setPen(QPen(Qt::green, 2));
		painter.drawPolyline(points[1], 256);

		painter.setPen(QPen(Qt::blue, 2));
		painter.drawPolyline(points[2], 256);

	} else {
		painter.setPen(QPen(Qt::black, 2));
		painter.drawPolyline(points[0], 256);
	}


}
