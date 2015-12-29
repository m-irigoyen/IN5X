#ifndef DEF_THRESHOLDINGHANDLER
#define DEF_THRESHOLDINGHANDLER

#include "opencv2/opencv.hpp"

using namespace cv;

class TresholdingHandler
{
public : 
	enum THRESHOLD
	{
		T_OPTIMAL = 127
	};

	static void basic(Mat src, Mat& output, int threshold = (int)THRESHOLD::T_OPTIMAL);
	//static void basic(Mat src, Mat& output, THRESHOLD threshold = THRESHOLD::T_OPTIMAL);
};

#endif