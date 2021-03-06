#ifndef DEF_IMAGEHANDLER
#define DEF_IMAGEHANDLER

#include "opencv2/opencv.hpp"
#include <string>

#include "cannyOperatorHandler.hpp"
#include "ThresholdingHandler.h"
#include "gaussianBlurHandler.hpp"
#include "transformPiece.hpp"
//#include "Utilities/filePaths.hpp"
#include "../Utilities/filePaths.hpp"

using namespace std;

class ImageHandler
{
private:
	static bool loadImage_path(std::string path, Mat& output);
	static string getImageExtension();

public: 
	// Converts the input image into grayscale
	static void convert_colorToGray(Mat src, Mat& output);

	// Prepares the image for recognition : gaussianBlur -> cannyOperator -> thresholding
	static void prepareImage_canny(Mat src, 
		Mat& output, 
		int gaussianKernelSize = GaussianBlurHandler::GB_KERNEL_SIZE::GBK_OPTIMAL, 
		int cannyKernelSize = CannyOperatorHandler::KERNEL_SIZE::CK_OPTIMAL, 
		int cannyThreshold = CannyOperatorHandler::THRESHOLD_SIZE::CT_OPTIMAL, 
		int threshold = TresholdingHandler::THRESHOLD::T_OPTIMAL);

	
	static bool loadImage(std::string name, Mat& output);

	static void findContour(Mat& contour, vector<pair<int, int>>& result);

	// Prepares the image for recognition : gaussianBlur -> cannyOperator -> thresholding
	/*static void prepareImage_canny(Mat src,
		Mat& output,
		int gaussianKernelSize = GaussianBlurHandler::GB_KERNEL_SIZE::GBK_OPTIMAL,
		int cannyKernelSize = CannyOperatorHandler::KERNEL_SIZE::CK_OPTIMAL,
		/*int cannyThreshold = CannyOperatorHandler::THRESHOLD_SIZE::CT_OPTIMAL,
		/*int threshold = TresholdingHandler::THRESHOLD::T_OPTIMAL);*/
};

#endif