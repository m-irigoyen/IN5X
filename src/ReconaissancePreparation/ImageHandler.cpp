#include "ImageHandler.h"

void ImageHandler::convert_colorToGray(Mat src, Mat & output)
{
	cv::cvtColor(src, output, CV_BGR2GRAY);
}

void ImageHandler::prepareImage_canny(Mat src, Mat & output, int gaussianKernelSize, int cannyKernelSize, int cannyThreshold, int threshold)
{
	// La kernelSize doit être impaire et plus grande que 0. Sinon, ça plante.
	if (gaussianKernelSize % 2 != 1 || cannyKernelSize < 3 || cannyKernelSize % 2 != 1 || cannyKernelSize >= 7)
		return;
	//resize(src, src, Size(), 0.4, 0.4);
	Mat src_gray;
	ImageHandler::convert_colorToGray(src, src_gray);
	GaussianBlurHandler::basic(src_gray, output, gaussianKernelSize);
	CannyOperatorHandler::basic(output, output, cannyKernelSize, cannyThreshold);
	TresholdingHandler::basic(output, output, threshold);
}

bool ImageHandler::loadImage_path(std::string path, Mat & output)
{
	Mat image = imread(path, CV_LOAD_IMAGE_COLOR);
	if (!image.data)                              // Check for invalid input
	{
		cout << "ImageHandler::loadImage : Erreur! L'image " << path << " n'a pas pu etre chargee" << std::endl;
		return false;
	}
	else
	{
		output = image;
		return true;
	}
	
}

string ImageHandler::getImageExtension()
{
	return string(".jpg");
}

bool ImageHandler::loadImage(std::string name, Mat & output)
{
	return ImageHandler::loadImage_path(PATHS::DATABASE2 + name + ImageHandler::getImageExtension(), output);
}

void ImageHandler::findContour(Mat& contour, vector<pair<int, int>>& result) {
	TransformPiece piece(contour);
	piece.findDirection();

	piece.findPathcontour(result);
}