#include "Helper.h"

Mat convertCaracteristicVector(vector<float> caracteristicVector)
{
	//TODO: à implémenter
	return Mat(); 
}

vector<float> convertCaracteristicVector(Mat caracteristicVector)
{
	//TODO: à implémenter
	return vector<float>();
}

float distanceVector(vector<float>& v1, vector<float>& v2) {
	float dist = 0;
	if (v1.size() != v2.size()) {
		cout << "Helper::distance : Erreur! v1 et v2 de taille différentes" << std::endl;
	}
	else{
		for (int i = 0; i < v1.size(); ++i) {
			dist += pow(v1.at(i) - v2.at(i), 2);
		}
		dist = sqrt(dist);
	}
	return dist;
}

string convert_pieceTypeToName(PIECE_TYPE t)
{
	string name;
	switch (t)
	{
	case PIECE_TYPE::CAVALIER:
		name += "cavalier";
		break;
	case PIECE_TYPE::FOU:
		name += "fou";
		break;
	case PIECE_TYPE::PION:
		name += "pion";
		break;
	case PIECE_TYPE::REINE:
		name += "reine";
		break;
	case PIECE_TYPE::ROI:
		name += "roi";
		break;
	case PIECE_TYPE::TOUR:
		name += "tour";
		break;
	}
	return name;
}
