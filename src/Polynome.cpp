#include "Polynome.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ostream>
#include <algorithm>
#include <math.h>

using namespace std;

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

Polynome* Polynome::product(Polynome* pol)
{
	int newDegree = degree + pol->getDegree();
	std::vector<float>* newCoeffs = new std::vector<float>(newDegree+1,0);
	for (int i = 0; i<=degree; ++i){
		for (int j = 0; j<=pol->getDegree(); ++j){
			newCoeffs->at(i+j) += coefficients.at(i)*pol->getCoefficients().at(j);
		}
	}
	degree = newDegree;
	this->setCoefficients(*newCoeffs);
	return this;
}

Polynome* Polynome::pol_lagrange(std::vector<std::pair<float,float>> points, int i){
	std::vector<float> vec = *(new std::vector<float>(2,0));
	Polynome* pol = new Polynome(1,vec);
	std::vector<float>* newCoeffs = new std::vector<float>(2, 0);
	this->setCoefficients(*newCoeffs);
	degree = 1;
	for (int j = 0; j<points.size(); ++j){
		if ((j == 0 && i!=0) || (j==1 && i==0)){
			coefficients.at(1) = -points.at(j).first / (points.at(i).first - points.at(j).first);
			coefficients.at(0) = 1 / (points.at(i).first - points.at(j).first);
		}
		else {
			if (i != j) {
				vec.at(0) = 1 / (points.at(i).first - points.at(j).first);
				vec.at(1) = - points.at(j).first / (points.at(i).first - points.at(j).first);
				pol = new Polynome(1, vec);
				this->product(pol);
			}
		}
		
	}
	return this;
}

Polynome Polynome::interp_lagrange(std::vector<pair<float, float>> points) {
	Polynome pol_interp = *new Polynome(1, *new std::vector<float>(2, 0));
	Polynome pol_l = *new Polynome(1, *new std::vector<float>(2, 0));
	for (int i = 0; i < points.size(); ++i) {
		pol_interp += *(*pol_l.pol_lagrange(points, i)).product(new Polynome(0, *new std::vector<float>(1, points.at(i).second)));
	}

	return pol_interp;
}

void Polynome::operator+=(Polynome p) {
	std::vector<float> vec = *new std::vector<float>(std::max(degree, p.getDegree()) + 1, 0);
	if (p.getDegree() > degree) {
		vec = p.getCoefficients();
	}
	else {
		vec = coefficients;
	}
	for (int i = std::max(degree, p.getDegree())- std::min(degree, p.getDegree()); i < std::max(degree, p.getDegree()); ++i) {
		if (p.getDegree() > degree) {
			vec.at(i)+= coefficients.at(i- std::min(degree, p.getDegree()));
		}
		else if (p.getDegree() < degree) {
			vec.at(i) += p.getCoefficients().at(i - std::min(degree, p.getDegree()));
		}
		else {
			vec.at(i) += p.getCoefficients().at(i);
		}
	}
	degree = std::max(degree, p.getDegree());
	this->setCoefficients(vec);
}

Polynome Polynome::find_tangente(int x) {
	Polynome tangente = *new Polynome(1, *new std::vector<float>(2, 0));
	Polynome deriv = *this->derivative();
	std::vector<float> coeff_tan = *new std::vector<float>();
	float dfx = deriv.value_y(x);
	float fx = this->value_y(x);
	coeff_tan.push_back(dfx);
	coeff_tan.push_back(fx-dfx*x);
	tangente.setCoefficients(coeff_tan);

	return tangente;
}

float Polynome::value_y(float x) {
	float y = 0;
	for (int i = coefficients.size() - 1; i >= 0; --i) {
		y += pow(x, coefficients.size() - i - 1) * coefficients.at(i);
	}

	return y;
}

float Polynome::angle(Polynome p) {
	float angle = atan((p.getCoefficients().at(0) - coefficients.at(0) / (1 + p.getCoefficients().at(0) * coefficients.at(0))));
	if (p.getCoefficients().at(0) != p.getCoefficients().at(0)) {
		angle = atan(coefficients.at(0)) - atan(1)*2;
	}
	if (coefficients.at(0) != coefficients.at(0)) {
		angle = atan(p.getCoefficients().at(0)) - atan(1)*2;
	}
	return angle;
}
int Polynome::getDegree(){ return degree; }

std::vector<float> Polynome::getCoefficients() { return coefficients;}

void Polynome::setCoefficients(std::vector<float> newCoeff) { coefficients = newCoeff;}
