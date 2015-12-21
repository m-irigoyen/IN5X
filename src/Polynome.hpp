#ifndef DEF_POLYNOME
#define DEF_POLYNOME

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <assert.h>

class Polynome {
public:
	Polynome(int, std::list<float>);
	Polynome* derivative();


private:
	int degree;
	std::list<float> coefficients;
};

#endif // !DEF_POLYNOME