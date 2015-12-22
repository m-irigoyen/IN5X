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
	Polynome* product(Polynome);
	int getDegree();
	std::vector<float> getCoefficients();
	void setCoefficients(std::vector<float>);
	Polynome* Polynome::pol_lagrange(std::vector<std::pair<float,float>>, int);


private:
	int degree;
	std::vector<float> coefficients;
};

#endif // !DEF_POLYNOME