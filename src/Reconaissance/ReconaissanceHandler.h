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
	vector<vector<float>> classes;

public:
	// Set les classes
	void setClasses(vector<vector<float>>& classes);
	
	// Construit les classes � partir des images fournies
	void buildClasses(DatabaseHandler& db);
	
	PIECE_TYPE completeReconaissance(string imageName);

	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce (m�thode sans PCA)
	vector<float> recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes);
	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce (m�thode PCA)
	vector<float> recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB);

	PIECE_TYPE getTypeFromProbabilities(vector<float> probabilities);
};

#endif 