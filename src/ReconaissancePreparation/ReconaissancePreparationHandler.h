#ifndef DEF_RECONNAISSANCEPREPARATIONHANDLER
#define DEF_RECONNAISSANCEPREPARATIONHANDLER

#include "opencv2/opencv.hpp"

#include "ImageHandler.h"
#include "Utilities/databaseHandler.hpp"

using namespace cv;

class ReconnaissancePreparationHandler
{
public:

	// Depuis l'image donn�e, extrait son vecteur caract�ristique
	static void buildCaracteristicVector(Mat image, vector<float>& caracteristicVector);

	// Effectue l'apprentissage des classes depuis la base de donn�es d'image
	static void learning(DatabaseHandler& database, vector<vector<float>>& classes);
};

#endif 