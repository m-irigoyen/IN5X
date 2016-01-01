#ifndef DEF_RECONNAISSANCEHANDLER
#define DEF_RECONNAISSANCEHANDLER

#include <string>
#include <vector>

#include "opencv2/opencv.hpp"
using namespace cv;

using namespace std;

class ReconnaissanceHandler
{

public:
	

	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce
	vector<float> recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB);
};

#endif 