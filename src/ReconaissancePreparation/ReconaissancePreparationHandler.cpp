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
	vector<DatabaseImage>& images = database.getImages();
	for (DatabaseImage d : images)
	{
		//TODO: implémenter l'apprentissage des classes
		//classes = 
	}
}
