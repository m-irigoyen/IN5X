#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"
#include <vector>


#include "filePaths.hpp"
#include "exampleCodes.h"
#include "tangent_descriptor.hpp"

#include "ImageTester.h"

using namespace cv;


// Le main
int main(int argc, char* argv[])
{
	// DESCRIPTEUR
	/*vector<pair<float, float>> points = *new vector<pair<float, float>>(5, *new pair<float, float>(0, 0));
	points.at(0) = (*new pair<float, float>(0, 0));
	points.at(1) = (*new pair<float, float>(3, 4));
	points.at(2) = (*new pair<float, float>(5, 20));
	points.at(3) = (*new pair<float, float>(35, 40));
	points.at(4) = (*new pair<float, float>(-5, 0));

	tangent_descriptor descript = *new tangent_descriptor(points, 1);*/

	// fix des fuites de mémoire par rapport au code ci-dessus
	vector<pair<float, float>> points;
	points.push_back(pair<float, float>(0, 0));
	points.push_back(pair<float, float>(3, 4));
	points.push_back(pair<float, float>(5, 20));
	points.push_back(pair<float, float>(35, 40));
	points.push_back(pair<float, float>(-5, 0));

	tangent_descriptor descript(points, 1);

	
	// TEST TRAITEMENT IMAGE
	ImageTester tester;
	tester.testImage_cannyMethod("n_roi_face (1).jpg");

	waitKey(0);
	return EXIT_SUCCESS;

	//videoTest();	// Lance la caméra avec une détection de contours 
}