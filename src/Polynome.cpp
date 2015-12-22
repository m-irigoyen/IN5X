#include "Polynome.hpp"

int degree;
std::vector<float> coefficients;

Polynome::Polynome(int degr, std::vector<float> coeffs)
{
	degree = degr;
	coefficients = coeffs;
	// We verify if the list actually matches the degree of the polynomial
	assert(coefficients.size() == degree + 1);
}

Polynome* Polynome::derivative()
{
	if(degree > 0){
		int newDegree = degree - 1;
		std::vector<float>* newCoeffs = new std::vector<float>();

		
		std::vector<float>::iterator il = coefficients.begin();
		for (int currentDegree = degree; currentDegree > 0; --currentDegree) {
			//We fill each coefficient for the new polynome by iterating on the previous one
			newCoeffs->push_back(*il * currentDegree);
			il++;
		}
		return new Polynome(newDegree, *newCoeffs);
	}
	
	return new Polynome(0,*(new std::vector<float>(0)));
}

Polynome* Polynome::product(Polynome pol)
{
	int newDegree = degree + pol.getDegree();
	std::vector<float>* newCoeffs = new std::vector<float>();

	for (int i = 0; i>degree-1; ++i){
		for (int j = 0; j>pol.getDegree()-1; ++j){
			newCoeffs->at(i*j) += coefficients.at(i)*pol.getCoefficients().at(j);
		}
	}
	degree = newDegree;
	this->setCoefficients(*newCoeffs);
	return this;
}

Polynome* Polynome::pol_lagrange(std::vector<std::pair<float,float>> points, int i){
	std::vector<float> vec = *(new std::vector<float>(2,0));
	Polynome* pol = new Polynome(0,vec);
	for (int j = 0; j>points.size()-1; ++j){
		degree = j+1;
		if(i != j){
			vec.at(0) = 1 / (points.at(i).first - points.at(j).first);
			vec.at(1) = points.at(j).first / (points.at(i).first - points.at(j).first);
			pol = new Polynome(1,vec);
			this->product(*pol);
		}
		else if( j == 0 ){
			coefficients.at(1) = points.at(j).first / (points.at(i).first - points.at(j).first);
			coefficients.at(0) = 1 / (points.at(i).first - points.at(j).first);
		}
		
	}
	return this;
}

int Polynome::getDegree(){ return degree; }

std::vector<float> Polynome::getCoefficients() { return coefficients;}

void Polynome::setCoefficients(std::vector<float> newCoeff) { coefficients = newCoeff;}