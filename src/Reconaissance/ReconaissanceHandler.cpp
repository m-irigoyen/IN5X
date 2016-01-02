#include "ReconaissanceHandler.h"

vector<float> ReconnaissanceHandler::recognise(vector<float>& caracteristicVector, PCA pca, Mat reducedLearnDB)
{
	Mat reduceVector = pca.project(caracteristicVector);

	// TODO KNN avec reduceVector ReducedLearnDB et surement une troisieme variable qui sait pour chaque vecteur de reduceLearnDB a quelle classe il appartient
	//TODO: impl�menter les probabilit�s d'appartenance P(v|c) = nbVecteur appatenant a c / nbVecteur dans KNN
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
	// Pr� traitement de l'image
	Mat src;
	ReconnaissancePreparationHandler::prepareImage_method1(imageName,src);

	// Construction du vecteur caract�ristique
	vector<float> caracteristicVector;
	ReconnaissancePreparationHandler::buildCaracteristicVector(src, caracteristicVector);

	// Calcul des probabilit�s d'appartenance
	vector<float> probabilities = this->recognise(caracteristicVector, classes);

	// D�duction du type de pi�ce
	return this->getTypeFromProbabilities(probabilities);
}

vector<float> ReconnaissanceHandler::recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes)
{
	vector<float> dist;
	float norme;
	float dist_dim;
	for (int i = 0; i < classes.size(); ++i)
	{
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