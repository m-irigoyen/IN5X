#include "Helper.h"

Mat convertCaracteristicVector(vector<float> caracteristicVector)
{
	//TODO: � impl�menter
	return Mat(); 
}

vector<float> convertCaracteristicVector(Mat caracteristicVector)
{
	//TODO: � impl�menter
	return vector<float>();
}

float distanceVector(vector<float>& v1, vector<float>& v2) {
	float dist = 0;
	if (v1.size() != v2.size()) {
		cout << "Helper::distance : Erreur! v1 et v2 de taille diff�rentes" << std::endl;
	}
	else{
		for (int i = 0; i < v1.size(); ++i) {
			dist += pow(v1.at(i) - v2.at(i), 2);
		}
		dist = sqrt(dist);
	}
	return dist;
}
