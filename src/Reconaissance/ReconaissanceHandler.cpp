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

void ReconnaissanceHandler::analyseResults(vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& results)
{
	int correct = 0;
	for (pair<DatabaseImageDescriptor, PIECE_TYPE> p : results)
	{
		cout << "Type :  " << convert_pieceTypeToName(p.first.type) << " | Result : " << convert_pieceTypeToName(p.second) << endl;
		if (p.first.type == p.second)
			++correct;
	}
	cout << endl;
	cout << "RESULTAT FINAL : " << correct << "/" << results.size() << endl;
	cout << "_______ Reconnus | Total" << endl;
	cout << "Cavaliers : " << this->getNumberOfRecognised(PIECE_TYPE::CAVALIER, results) << " / " << this->getNumberOf(PIECE_TYPE::CAVALIER, results) << endl;
	cout << "Fous	   : " << this->getNumberOfRecognised(PIECE_TYPE::FOU, results) << " / " << this->getNumberOf(PIECE_TYPE::FOU, results) << endl;
	cout << "Pions	   : " << this->getNumberOfRecognised(PIECE_TYPE::PION, results) << " / " << this->getNumberOf(PIECE_TYPE::PION, results) << endl;
	cout << "Reine	   : " << this->getNumberOfRecognised(PIECE_TYPE::REINE, results) << " / " << this->getNumberOf(PIECE_TYPE::REINE, results) << endl;
	cout << "Rois	   : " << this->getNumberOfRecognised(PIECE_TYPE::ROI, results) << " / " << this->getNumberOf(PIECE_TYPE::ROI, results) << endl;
	cout << "Tours	   : " << this->getNumberOfRecognised(PIECE_TYPE::TOUR, results) << " / " << this->getNumberOf(PIECE_TYPE::TOUR, results) << endl;
}

int ReconnaissanceHandler::getNumberOf(PIECE_TYPE type, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& db)
{
	int nb = 0;
	for (pair<DatabaseImageDescriptor, PIECE_TYPE> p : db)
	{
		if (p.first.type == type)
			++nb;
	}
	return nb;
}

int ReconnaissanceHandler::getNumberOfRecognised(PIECE_TYPE type, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& db)
{
	int nb = 0;
	for (pair<DatabaseImageDescriptor, PIECE_TYPE> p : db)
	{
		if (p.second == type)
			++nb;
	}
	return nb;
}

void ReconnaissanceHandler::setClasses(vector<vector<float>>& classes)
{
	this->classes = classes;
}

void ReconnaissanceHandler::buildClasses(DatabaseHandler & db)
{
	ReconnaissancePreparationHandler::learning(db, this->classes);
}

void ReconnaissanceHandler::completeReconnaissance_db(DatabaseHandler & testImages, vector<pair<DatabaseImageDescriptor, PIECE_TYPE>>& result)
{
	for (DatabaseImage i : testImages.getImages())
		result.push_back(pair<DatabaseImageDescriptor, PIECE_TYPE>(i.descriptor, this->completeReconaissance_one(i.mat)));
}

PIECE_TYPE ReconnaissanceHandler::completeReconaissance_one(string imageName)
{
	// Pré traitement de l'image
	Mat src;
	ImageHandler::loadImage(imageName, src);

	return this->completeReconaissance_one(src);
}

PIECE_TYPE ReconnaissanceHandler::completeReconaissance_one(Mat image)
{
	// Construction du vecteur caractéristique
	vector<float> caracteristicVector;
	ReconnaissancePreparationHandler::buildCaracteristicVector(image, caracteristicVector);

	// Calcul des probabilités d'appartenance
	vector<float> probabilities = this->recognise(caracteristicVector, this->classes);

	// Déduction du type de pièce
	return this->getTypeFromProbabilities(probabilities);
}

vector<float> ReconnaissanceHandler::recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes)
{
	vector<float> dist;
	for (int i = 0; i < classes.size(); ++i)
	{
		dist.push_back(distanceVector(caracteristicVector, classes.at(i)));
	}
	return dist;
}