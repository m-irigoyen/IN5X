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

	void analyseResults(vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& results);
	int getNumberOf(PIECE_TYPE type, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& db);
	int getNumberOfRecognised(PIECE_TYPE type, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& db);
	// Set les classes
	void setClasses(vector<vector<float>>& classes);
	
	// Construit les classes � partir des images fournies
	void buildClasses(DatabaseHandler& db);
	

		// FONCTIONS DE RECONNAISSANCE
	// Effectue une reconnaissance sur la base d'images donn�e
	void completeReconnaissance_db(DatabaseHandler& testImages, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& result);
	// Effectue une reconnaissance sur l'image donn�e
	PIECE_TYPE completeReconaissance_one(string imageName);
	// Effectue une reconnaissance sur l'image donn�e
	PIECE_TYPE completeReconaissance_one(Mat image);

	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce (m�thode sans PCA)
	vector<float> recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes);
	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce (m�thode PCA)
	vector<float> recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB);

	PIECE_TYPE getTypeFromProbabilities(vector<float> probabilities);
};

#endif 