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
	int smallest = 0;
	for (int i = 1; i < probabilities.size(); ++i)
	{
		if (probabilities.at(i) < probabilities.at(smallest))
			smallest = i;
	}

	return (PIECE_TYPE)smallest;
}

void ReconnaissanceHandler::setClasses(vector<vector<float>>& classes)
{
	this->classes = classes;
}

void ReconnaissanceHandler::buildClasses(DatabaseHandler & db)
{
	ReconnaissancePreparationHandler::learning(db, this->classes);
}

PIECE_TYPE ReconnaissanceHandler::completeReconaissance(string imageName)
{
	// Pré traitement de l'image
	Mat src;
	ImageHandler::loadImage(imageName, src);

	// Construction du vecteur caractéristique
	vector<float> caracteristicVector;
	ReconnaissancePreparationHandler::buildCaracteristicVector(src, caracteristicVector);

	// Calcul des probabilités d'appartenance
	vector<float> probabilities = this->recognise(caracteristicVector, this->classes);

	// Déduction du type de pièce
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