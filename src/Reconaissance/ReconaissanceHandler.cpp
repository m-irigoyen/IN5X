#include "ReconaissanceHandler.h"

vector<float> ReconnaissanceHandler::recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB)
{
	Mat reduceVector = pca.project(caracteristicVector);

	// TODO KNN avec reduceVector ReducedLearnDB et surement une troisieme variable qui sait pour chaque vecteur de reduceLearnDB a quelle classe il appartient
	//TODO: implémenter les probabilités d'appartenance P(v|c) = nbVecteur appatenant a c / nbVecteur dans KNN
	return vector<float>();
}

PIECE_TYPE ReconnaissanceHandler::getTypeFromProbabilities(vector<float> probabilities)
{
	//TODO : trouver le type en fonction des probas

	int smallest = 0;
	for (int i = 1; i < probabilities.size(); ++i)
	{
		if (probabilities.at(i) < probabilities.at(smallest))
			smallest = i;
	}

	return (PIECE_TYPE)smallest;
}

PIECE_TYPE ReconnaissanceHandler::completeReconaissance(string imageName, vector<vector<float>>& classes)
{
	// Pré traitement de l'image
	Mat src;
	ReconnaissancePreparationHandler::prepareImage_method1(imageName,src);

	// Construction du vecteur caractéristique
	vector<float> caracteristicVector;
	ReconnaissancePreparationHandler::buildCaracteristicVector(src, caracteristicVector);

	// Calcul des probabilités d'appartenance
	vector<float> probabilities = this->recognise(caracteristicVector, classes);

	// Déduction du type de pièce
	return this->getTypeFromProbabilities(probabilities);
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