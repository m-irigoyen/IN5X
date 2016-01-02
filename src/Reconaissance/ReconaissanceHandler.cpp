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
	float norme;
	float dist_dim;
	for (int i = 0; i < classes.size(); ++i)
	{
		/*vector<float> vector_Piece = classes.at(i);
		dist.push_back(distanceVector(caracteristicVector, vector_Piece));*/
		dist_dim = distanceVector(caracteristicVector, classes.at(i));
		norme += pow(dist_dim, 2);
		dist.push_back(dist_dim);
	}
	norme = sqrt(norme);

	for (int i = 0; i < classes.size(); ++i) {
		dist.at(i) = dist.at(i) / norme;
	}
	return dist;
}