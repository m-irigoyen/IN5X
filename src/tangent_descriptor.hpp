#ifndef DEF_TANGENT_DESCRIPTOR
#define DEF_TANGENT_DESCRIPTOR

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Polynome.hpp"

using namespace std;

class tangent_descriptor {
public:
	tangent_descriptor(vector<pair<float, float>> points, int x);

private:
	vector<pair<float,float>> points;
	vector<float> angle;
	vector<Polynome> interp;
	vector<Polynome> tangent;
};

#endif // !DEF_TANGENT_DESCRIPTOR#pragma once
