#include "ImageManager.h"

ImageManager::ImageManager() : images()
{

}

void ImageManager::addImage(cv::Mat im, string info)
{
}

void ImageManager::loadImage(string filename)
{
}

cv::Mat ImageManager::getImage(int n)
{
	return cv::Mat();
}

cv::Mat ImageManager::getImage(string name)
{
	return cv::Mat();
}

bool ImageManager::deleteImage(int n)
{
	return false;
}

bool ImageManager::deleteImage(string name)
{
	return false;
}
