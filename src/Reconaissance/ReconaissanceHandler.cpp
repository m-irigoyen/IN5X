#include "ReconaissanceHandler.h"

vector<float> ReconnaissanceHandler::recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB)
{
	Mat reduceVector = pca.project(caracteristicVector);

	// TODO KNN avec reduceVector ReducedLearnDB et surement une troisieme variable qui sait pour chaque vecteur de reduceLearnDB a quelle classe il appartient
	//TODO: implémenter les probabilités d'appartenance P(v|c) = nbVecteur appatenant a c / nbVecteur dans KNN
	return vector<float>();
}

vector<float> ReconnaissanceHandler::completeReconaissance(string imageName)
{
	//TODO: prepareimage
	//TODO: build classes (or use premade ones)
	//TODO: 
	return vector<float>();
}

vector<float> ReconnaissanceHandler::recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes)
{
	vector<float> dist;
	for (int i = 0; i < classes.size(); ++i)
	{
		/*vector<float> vector_Piece = classes.at(i);
		dist.push_back(distanceVector(caracteristicVector, vector_Piece));*/
		dist.push_back(distanceVector(caracteristicVector, classes.at(i)));	// Petite optimisation par rapport au code ci-dessus
	}
	return dist;
}