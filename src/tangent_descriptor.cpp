#include "Polynome.hpp"
#include "tangent_descriptor.hpp"
#include <stdio.h>
#include <stdlib.h>

tangent_descriptor::tangent_descriptor(vector<pair<float, float>> points, int x) {
	assert(x*2 < points.size());
	vector<pair<float, float>> list_points_interp = *new vector<pair<float, float>>(int(x*2+1),*new pair<float,float> (0,0));
	interp = *new vector<Polynome>(points.size(),*new Polynome());
	tangent = *new vector<Polynome>(points.size(), *new Polynome());
	angle = *new vector<float>(points.size(), 0);
	for (int i = 0; i < points.size(); ++i) {
		for (int j = i - x; j <= i + x; ++j) {
			if (j < 0) {
				list_points_interp.at(j - i + x) = points.at(j + points.size());
			}
			else if (j >= points.size()) {
				list_points_interp.at(j - i + x) = points.at(j - points.size());
			}
			else {
				list_points_interp.at(j - i + x) = points.at(j);
			}
		}

		interp.at(i).interp_lagrange(list_points_interp);
		tangent.at(i) = interp.at(i).find_tangente(points.at(i).first);
		if (i > 0) {
			angle.at(i - 1) = interp.at(i).angle(interp.at(i - 1));
		}
		if (i == points.size() - 1) {
			angle.at(i) = interp.at(0).angle(interp.at(points.size()-1));
		}
		
	}
}