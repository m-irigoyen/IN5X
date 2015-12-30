#include "ThresholdingHandler.h"

void TresholdingHandler::basic(Mat src, Mat & output, int threshold)
{
	cv::threshold(src, output, threshold, 255, THRESH_BINARY);
}

//void TresholdingHandler::basic(Mat src, Mat & output, THRESHOLD threshold)
//{
//	cv::threshold(src, output, int(threshold));
//}
