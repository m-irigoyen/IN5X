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
	//TODO: stocker les classes ici pour �viter les calculs inutiles

public:
	
	PIECE_TYPE completeReconaissance(string imageName, vector<vector<float>>& classes);

	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce (m�thode sans PCA)
	vector<float> recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes);
	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce (m�thode PCA)
	vector<float> recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB);

	PIECE_TYPE getTypeFromProbabilities(vector<float> probabilities);
};

#endif 