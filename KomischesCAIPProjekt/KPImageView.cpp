#include "KPImageView.h"

KPImageView::KPImageView(QWidget* parent)
	: QWidget(parent), currentImage(), kpgs(), currentImageID(-1) {
	ui.setupUi(this);
	ui.graphicsView->setScene(&kpgs);
	
	connect(&kpgs, SIGNAL(mouseMoved(int, int)), this, SLOT(mouseHoverUpdater(int, int)));
}

KPImageView::~KPImageView() {
}

void KPImageView::setImage(KPImage* img, const int& ID) {
	this->currentImageID = ID;
	this->currentImage = img;
	kpgs.clear();
	kpgs.setSceneRect(currentImage->getQ().rect());
	kpgs.addPixmap(QPixmap::fromImage(currentImage->getQ()));
	this->updateStats();
}

void KPImageView::fit(KPImage* img, const bool current = true) {
	if (current) {
		ui.graphicsView->fitInView(0, 0, currentImage->getQ().width(), currentImage->getQ().height(), Qt::KeepAspectRatio);
	} else {
		ui.graphicsView->fitInView(0, 0, img->getQ().width(), img->getQ().height(), Qt::KeepAspectRatio);
	}
}

void KPImageView::fitToCurrent() {
	ui.graphicsView->fitInView(0, 0, currentImage->getQ().width(), currentImage->getQ().height(), Qt::KeepAspectRatio);
}

const int KPImageView::getID() {
	return this->currentImageID;
}

void KPImageView::mouseHoverUpdater(int x, int y) {
	string pos;
	string col;
	x--;
	y--;
	if (x < 0 || y < 0 || x > currentImage->getWidth() || y > currentImage->getHeight()) {
		pos += string("X: ") + to_string(x) + string(" Y: ") + to_string(y);
		pos += string("(out of bounds) ");
		col += "-";
	} else {
		pos += string("X: ") + to_string(x) + string(" Y: ") + to_string(y);
		QColor color = currentImage->getQ().pixelColor(x, y);
		col += string("R:") + to_string(color.red());
		col += string(" G:") + to_string(color.green());
		col += string(" B:") + to_string(color.blue());
		col += string(" A:") + to_string(color.alpha());
	}
	this->ui.mousePositionLineEdit->setText(QString(pos.c_str()));
	this->ui.hoverDataLineEdit->setText(QString(col.c_str()));
}



void KPImageView::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	this->fitToCurrent();
}

void KPImageView::updateStats() {
	// TODO update fields in viewer
	this->ui.imageNameLineEdit->setText(QString(currentImage->getName().c_str()));
	string b = string("Width: ") + to_string(currentImage->getWidth()) + string("px   Height: ") + to_string(currentImage->getHeight()) + string("px");
	this->ui.dimensionsLineEdit->setText(QString(b.c_str()));
	string c = string("Channels: ") + to_string(currentImage->getNumChannels()) + string("   Bitdepth: ") + to_string(currentImage->getBitDepth()) + string(" raw: ") + to_string(currentImage->getQ().format());
	this->ui.imageFormatLineEdit->setText(QString(c.c_str()));
}

void KPImageView::on_actionHide_clicked() {
	cout << "Viewer hidden" << endl;
	this->hide();
	
}

void KPImageView::on_actionDismiss_clicked() {
	cout << "Window will be gone!" << endl;
	emit closethis(this->currentImageID);
}



bool KPImageView::event(QEvent* e) {
	if (e->type() == QEvent::WindowActivate) {
		emit windowactivated(this->currentImageID);
	}
	return QWidget::event(e);
}