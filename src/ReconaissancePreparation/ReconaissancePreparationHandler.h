#ifndef DEF_RECONNAISSANCEPREPARATIONHANDLER
#define DEF_RECONNAISSANCEPREPARATIONHANDLER

#include "opencv2/opencv.hpp"
#include "ImageHandler.h"
//#include "Utilities/databaseHandler.hpp"
#include "../Utilities/databaseHandler.hpp"
#include "tangent_descriptor.hpp"

using namespace cv;

class ReconnaissancePreparationHandler
{
public:

	// Depuis l'image donn�e, extrait son vecteur caract�ristique
	static void buildCaracteristicVector(Mat image, vector<float>& caracteristicVector, int n = 350, int x = 1);

	// Effectue l'apprentissage des classes depuis la base de donn�es d'image (PCA)
	static void learningPCA(DatabaseHandler & database, PCA& pca, vector<vector<float>>& classes, int n, int x);

	// Effectue l'apprentissage des classes depuis la base de donn�es d'image
	static void learning(DatabaseHandler& database, vector<vector<float>>& classes, int n = 350, int x = 1);

	static vector<float> meanVectorClass(vector<vector<float>> vectorsClass);
};

#endif 