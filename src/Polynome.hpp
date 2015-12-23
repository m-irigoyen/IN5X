#ifndef DEF_POLYNOME
#define DEF_POLYNOME

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>

class Polynome {
public:
	Polynome(int, std::vector<float>);
	Polynome* derivative();
	Polynome* product(Polynome*);
	int getDegree();
	std::vector<float> getCoefficients();
	void setCoefficients(std::vector<float>);
	Polynome* pol_lagrange(std::vector<std::pair<float,float>>, int);
	Polynome interp_lagrange(std::vector<std::pair<float,float>>);
	void operator+=(Polynome);
	Polynome find_tangente(int);
	float value_y(float x);
	float angle(Polynome p);

private:
	int degree;
	std::vector<float> coefficients;
};

#endif // !DEF_POLYNOME