#include "Polynome.hpp"

int degree;
std::list<float> coefficients;

Polynome::Polynome(int degr, std::list<float> coeffs)
{
	degree = degr;
	coefficients = coeffs;
	// We verify if the list actually matches the degree of the polynomial
	assert(coefficients.size == degree + 1);
}

Polynome* Polynome::derivative()
{
	if(degree > 0){
		int newDegree = degree - 1;
		std::list<float>* newCoeffs = new std::list<float>();

		
		std::list<float>::iterator il = coefficients.begin();
		for (int currentDegree = degree; currentDegree > 0; --currentDegree) {
			//We fill each coefficient for the new polynome by iterating on the previous one
			newCoeffs->push_back(*il * currentDegree);
			il++;
		}
		return new Polynome(newDegree, *newCoeffs);
	}
	
	return new Polynome(0,*(new std::list<float>(0)));
}



