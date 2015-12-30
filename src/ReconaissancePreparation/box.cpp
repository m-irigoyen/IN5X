#include "box.hpp"

#define PI 3.14159265

Box::Box() {
	aire = 0;
	points_box = vector<pair<int, int>>();
}
Box::Box(vector<pair<int, int>> piece)
{
	int xmin, xmax, ymin, ymax;
	xmin = 40000;
	ymin = 40000;
	xmax = -1;
	ymax = -1;
	for (int i = 0; i < piece.size(); ++i) {
		pair<int, int> p = piece.at(i);
		if (p.second < xmin) {
			xmin = p.second;
		}
		if (p.second > xmax) {
			xmax = p.second;
		}
		if (p.first < ymin) {
			ymin = p.first;
		}
		if (p.first > ymax) {
			ymax = p.first;
		}
	}
	points_box.push_back(pair<int, int>(xmin, ymin));
	points_box.push_back(pair<int, int>(xmin, ymax));
	points_box.push_back(pair<int, int>(xmax, ymax));
	points_box.push_back(pair<int, int>(xmax, ymin));
	aire = sqrt(pow(points_box.at(0).second - points_box.at(1).second, 2)) * sqrt(pow(points_box.at(1).first - points_box.at(2).first, 2));

}
