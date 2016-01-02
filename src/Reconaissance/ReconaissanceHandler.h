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
	

	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce (méthode sans PCA)
	vector<float> recognise(vector<float>& caracteristicVector);
	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce (méthode PCA)
	vector<float> recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB);
};

#endif 