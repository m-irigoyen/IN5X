#include "ReconaissancePreparationHandler.h"

void ReconnaissancePreparationHandler::buildCaracteristicVector(Mat image, vector<float>& caracteristicVector)
{
	Mat edges;
	ImageHandler::prepareImage_canny(image, edges);

	//TODO: implémenter la construction du vecteur caractéristique
	//caracteristicVector = 
}

void ReconnaissancePreparationHandler::learning(DatabaseHandler & database, vector<vector<float>>& classes)
{
	//TODO: implémenter l'apprentissage des classes

	//classes = 
}
