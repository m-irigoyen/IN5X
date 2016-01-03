#ifndef DEF_RECONNAISSANCEHANDLER
#define DEF_RECONNAISSANCEHANDLER

#include <string>
#include <vector>
//#include "Utilities/Helper.h"
//#include "ReconaissancePreparation/ReconaissancePreparationHandler.h"
#include "../Utilities/Helper.h"
#include "../ReconaissancePreparation/ReconaissancePreparationHandler.h"
#include <fstream>

#include "opencv2/opencv.hpp"
using namespace cv;

using namespace std;

class ReconnaissanceHandler
{
private:
	vector<vector<float>> classes;
	PCA pca;

	
public:

	void analyseResults(vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& results, int n = 350, int x = 1);

	int getNumberOf(PIECE_TYPE type, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& db);
	int getNumberOfRecognised(PIECE_TYPE type, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& db);
	// Set les classes
	void setClasses(vector<vector<float>>& classes);
	
	// Construit les classes à partir des images fournies
	void buildClasses(DatabaseHandler& db, int n = 350, int x = 1);

	void buildClassesPCA(DatabaseHandler& db, int n = 350, int x = 1);
	

		// FONCTIONS DE RECONNAISSANCE
	// Effectue une reconnaissance sur la base d'images donnée
	void completeReconnaissance_db(DatabaseHandler& testImages, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& result, int n = 350, int x = 1);
	void completeReconnaissance_dbPCA(DatabaseHandler& testImages, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& result, int n = 350, int x = 1);
	// Effectue une reconnaissance sur l'image donnée
	PIECE_TYPE completeReconaissance_one(string imageName);
	// Effectue une reconnaissance sur l'image donnée
	PIECE_TYPE completeReconaissance_one(Mat image, int n = 350, int x = 1);
	PIECE_TYPE completeReconaissance_onePCA(Mat image, int n = 350, int x = 1);
	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce (méthode sans PCA)
	vector<float> recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes);
	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce (méthode PCA)
	vector<float> recognisePCA(vector<float>& caracteristicVector, PCA pca, vector<vector<float>>& classes);

	PIECE_TYPE getTypeFromProbabilities(vector<float> probabilities);
};

#endif 