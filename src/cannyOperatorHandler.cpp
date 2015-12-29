#include "cannyOperatorHandler.hpp"

const float CannyOperatorHandler::ratio = 3;

// Applique un opérateur de canny sur l'image passée en paramètre. 
void CannyOperatorHandler::basic(Mat src, Mat& output, int kernelSize, int threshold)
{
	if (kernelSize < 3 || kernelSize % 2 != 1 || kernelSize >= 7)
	{
		std::cout << "CannyOperatorHandler : ERROR : kernel size must be odd (impaire)" << std::endl;
		return;
	}

	output.copySize(src);
	Canny(src, output, threshold, threshold * CannyOperatorHandler::ratio, static_cast<int>(kernelSize));
}

//void CannyOperatorHandler::basic(Mat src, Mat & output, KERNEL_SIZE kernelSize, THRESHOLD_SIZE thresholdSize)
//{
//	CannyOperatorHandler::basic(src, output, (int)kernelSize, (int)thresholdSize);
//}