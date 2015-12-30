#ifndef DEF_POLYNOME
#define DEF_POLYNOME

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>

using namespace std;

class Polynome {
public:
	Polynome();
	Polynome(int, vector<float>);
	Polynome* derivative();
	Polynome* product(Polynome*);
	int getDegree();
	vector<float> getCoefficients();
	void setCoefficients(vector<float>);
	Polynome* pol_lagrange(vector<pair<float,float>>, int);
	void interp_lagrange(vector<pair<float,float>>);
	void operator+=(Polynome);
	Polynome find_tangente(int);
	float value_y(float x);
	float angle(Polynome p);

private:
	int degree;
	vector<float> coefficients;
};

#endif // !DEF_POLYNOME