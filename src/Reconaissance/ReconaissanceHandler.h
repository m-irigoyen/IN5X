#ifndef DEF_RECONNAISSANCEHANDLER
#define DEF_RECONNAISSANCEHANDLER

#include <string>
#include <vector>
//#include "Utilities/Helper.h"
//#include "ReconaissancePreparation/ReconaissancePreparationHandler.h"
#include "../Utilities/Helper.h"
#include "../ReconaissancePreparation/ReconaissancePreparationHandler.h"

#include "opencv2/opencv.hpp"
using namespace cv;

using namespace std;

class ReconnaissanceHandler
{
private:
	//TODO: stocker les classes ici pour éviter les calculs inutiles

public:
	
	PIECE_TYPE completeReconaissance(string imageName, vector<vector<float>>& classes);

	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce (méthode sans PCA)
	vector<float> recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes);
	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce (méthode PCA)
	vector<float> recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB);

	PIECE_TYPE getTypeFromProbabilities(vector<float> probabilities);
};

#endif 