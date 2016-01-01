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
	

	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce
	vector<float> recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB);
};

#endif 