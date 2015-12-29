#include "box.hpp"

Box::Box(Mat img)
{
	vector<pair<int, int>> white;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<int>(i, j) == 255) {
				white.push_back(pair<int, int>(i, j));
			}
		}
	}

	for (int i = 0; i < white.size(); ++i) {
		pair<int,int> p = white.at(i);
		if (p.first < xmin) {
			xmin = p.first;
		}
		if (p.first > xmax) {
			xmax = p.first;
		}
		if (p.second < ymin) {
			ymin = p.second;
		}
		if (p.second > ymax) {
			ymax = p.second;
		}
	}
	points_box.push_back(pair<int, int>(xmin, ymin));
	points_box.push_back(pair<int, int>(xmin, ymax));
	points_box.push_back(pair<int, int>(xmax, ymax));
	points_box.push_back(pair<int, int>(xmax, ymin));
	pair<int, int> center((xmin + xmax) / 2, (ymin + ymax) / 2);
	float aire = sqrt(pow(points_box.at(0).first - points_box.at(1).first, 2) + pow(points_box.at(0).second - points_box.at(1).second, 2)) * sqrt(pow(points_box.at(2).first - points_box.at(3).first, 2) + pow(points_box.at(2).second - points_box.at(3).second, 2));
	vector<pair<int, int>> new_white = white;
	for (int i = 1; i < 360; ++i) {
		for (int j = 0; j < white.size(); ++j) {
			new_white.at(j).first = ((white.at(j).first - center.first) * cos(i) - (white.at(j).second - center.second) * sin(i)) + center.first;
			new_white.at(j).second = ((white.at(j).first - center.first)* sin(i) + (white.at(j).second - center.second)* cos(i)) + center.second;
		}
		for (int i = 0; i < new_white.size(); ++i) {
			pair<int, int> p = new_white.at(i);
			if (p.first < xmin) {
				xmin = p.first;
			}
			if (p.first > xmax) {
				xmax = p.first;
			}
			if (p.second < ymin) {
				ymin = p.second;
			}
			if (p.second > ymax) {
				ymax = p.second;
			}
		}
		float new_aire = sqrt(pow(points_box.at(0).first - points_box.at(1).first, 2) + pow(points_box.at(0).second - points_box.at(1).second, 2)) * sqrt(pow(points_box.at(2).first - points_box.at(3).first, 2) + pow(points_box.at(2).second - points_box.at(3).second, 2));
		if (new_aire < aire) {
			points_box.at(0) = (pair<int, int>(xmin, ymin));
			points_box.at(1) = (pair<int, int>(xmin, ymax));
			points_box.at(2) = (pair<int, int>(xmax, ymax));
			points_box.at(3) = (pair<int, int>(xmax, ymin));
			aire = new_aire;
			angle = i;
		}
	}
}
