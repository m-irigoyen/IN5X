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

	static void prepareImage_method1(string imageName, Mat& output);

	// Depuis l'image donnée, extrait son vecteur caractéristique
	static void buildCaracteristicVector(Mat image, vector<float>& caracteristicVector, int n = 500, int x = 6);

	// Effectue l'apprentissage des classes depuis la base de données d'image
	static void learning(DatabaseHandler& database, PCA& pca,Mat& reducedLearnDB);

	static vector<float> meanVectorClass(vector<vector<float>> vectorsClass);
};

#endif 