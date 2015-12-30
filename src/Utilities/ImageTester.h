#ifndef DEF_IMAGETESTER
#define DEF_IMAGETESTER

#include <string>

#include "opencv2/opencv.hpp"
#include "Utilities/filePaths.hpp"
#include "ReconaissancePreparation/ImageHandler.h"

using namespace std;
using namespace cv;

class ImageTester
{
public :
	ImageTester();

	// Ouvre une fenêtre de test sur l'image donnée pour tester la méthode de canny
	void testImage_cannyMethod(string imageName);
	static void testImageCallback_cannyMethod(int, void*);


	// ouaaais, je sais, en public c'est dégueu
	Mat src, src_gray, output;
	int gaussianSize;
	int cannySize;
	int cannyThreshold;
	int threshold;
private:
	
};





#endif
