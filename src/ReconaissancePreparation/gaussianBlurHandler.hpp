#ifndef DEF_GAUSSIANBLURHANDLER
#define DEF_GAUSSIANBLURHANDLER

/*
Fonctions d'aide qui simplifient l'utilisation du flou gaussien
*/

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

class GaussianBlurHandler
{
public:
	// La taille du kernel utilisé pour le flou gaussien
	enum GB_KERNEL_SIZE
	{
		GBK_OPTIMAL = 9,
		GBK_OPTIMAL2 = 11
	};

	// Applique un flou gaussien sur l'image passée en paramètre. 
	void static basic(Mat src, Mat& output, int size = (int)GB_KERNEL_SIZE::GBK_OPTIMAL);
	//void static basic(Mat src, Mat& output, GB_KERNEL_SIZE size = GB_KERNEL_SIZE::GBK_OPTIMAL);
};


#endif // !DEF_GAUSSIANBLURHANDLER
