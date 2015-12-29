#ifndef DEF_IMAGEHANDLER
#define DEF_IMAGEHANDLER

#include "opencv2/opencv.hpp"

#include "cannyOperatorHandler.hpp"
#include "ThresholdingHandler.h"
#include "gaussianBlurHandler.hpp"

class ImageHandler
{
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

	// Prepares the image for recognition : gaussianBlur -> cannyOperator -> thresholding
	/*static void prepareImage_canny(Mat src,
		Mat& output,
		int gaussianKernelSize = GaussianBlurHandler::GB_KERNEL_SIZE::GBK_OPTIMAL,
		int cannyKernelSize = CannyOperatorHandler::KERNEL_SIZE::CK_OPTIMAL,
		int cannyThreshold = CannyOperatorHandler::THRESHOLD_SIZE::CT_OPTIMAL,
		int threshold = TresholdingHandler::THRESHOLD::T_OPTIMAL);*/
};

#endif