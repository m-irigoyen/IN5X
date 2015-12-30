#ifndef DEF_HELPER
#define DEF_HELPER

#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

// Convertit un vecteur caractéristique sous format matriciel
Mat convertCaracteristicVector(vector<float> caracteristicVector);
// Convertit un vecteur caractéristique sous format vectoriel
vector<float> convertCaracteristicVector(Mat caracteristicVector);

#endif