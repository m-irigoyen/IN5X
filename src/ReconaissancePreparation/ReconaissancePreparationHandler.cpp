#include "ReconaissancePreparationHandler.h"

void ReconnaissancePreparationHandler::buildCaracteristicVector(Mat image, vector<float>& caracteristicVector)
{
	Mat edges;
	ImageHandler::prepareImage_canny(image, edges);

	//TODO: impl�menter la construction du vecteur caract�ristique
	//caracteristicVector = 
}

void ReconnaissancePreparationHandler::learning(DatabaseHandler & database, vector<vector<float>>& classes)
{
	//TODO: impl�menter l'apprentissage des classes

	//classes = 
}
