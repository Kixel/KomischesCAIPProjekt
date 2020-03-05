#include "ImageManager.h"

ImageManager::ImageManager() : images(), keywalker(0) {

}

void ImageManager::addImage(KPImage* im, string info) {
	images[keywalker] = im;
	images[keywalker]->setName(info);


	keywalker++;
	return;
}

int ImageManager::loadImage(string filename) {
	KPImage* n = new KPImage(filename);
	this->addImage(n, filename);
	return this->keywalker - 1;
}

KPImage* ImageManager::getImage(int n) {
	if (!iDExists(n))
		throw out_of_range("This does not exist!");
	return images[n];
}

//cv::Mat ImageManager::getImage(string name) {
//	return cv::Mat();
//}

bool ImageManager::deleteImage(int n) {
	if (this->iDExists(n)) {
		this->images.erase(n);
		return true;
	}
	return false;
}

bool ImageManager::iDExists(int n) {
	return images.count(n) == 1;
}

bool ImageManager::isEmpty() {
	return this->size() == 0;
}

int ImageManager::size() {
	return images.size();
}

//bool ImageManager::deleteImage(string name) {
//	return false;
//}
