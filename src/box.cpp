#include "box.hpp"

Box::Box(Mat img)
{
	vector<pair<int, int>> white;
	imshow("Image1", img);
	waitKey(0);
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == 255) {
				white.push_back(pair<int, int>(i, j));
			}
		}
	}
	xmin = 40000;
	ymin = 40000;
	xmax = -1;
	ymax = -1;
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

	rectangle(img, Point(ymin, xmin), Point(ymax, xmax), Scalar(255, 255, 255), +1, 4);
	imshow("Image1", img);
	waitKey(0);
	angle = 0;
	pair<int, int> center((xmin + xmax) / 2, (ymin + ymax) / 2);
	float aire = sqrt(pow(points_box.at(0).first - points_box.at(1).first, 2) + pow(points_box.at(0).second - points_box.at(1).second, 2)) * sqrt(pow(points_box.at(1).first - points_box.at(2).first, 2) + pow(points_box.at(1).second - points_box.at(2).second, 2));
	vector<pair<int, int>> new_white = white;
	for (int i = 1; i < 360; ++i) {
		for (int j = 0; j < white.size(); ++j) {
			new_white.at(j).first = ((white.at(j).first - center.first) * cos(i) - (white.at(j).second - center.second) * sin(i)) + center.first;
			new_white.at(j).second = ((white.at(j).first - center.first)* sin(i) + (white.at(j).second - center.second)* cos(i)) + center.second;
		}
		for (int k = 0; k < new_white.size(); ++k) {
			pair<int, int> p = new_white.at(k);
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
		float new_aire = sqrt(pow(xmin - xmin, 2) + pow(ymin - ymax, 2)) * sqrt(pow(xmin - xmax, 2) + pow(ymax - ymax, 2));
		if (new_aire < aire) {
			points_box.at(0) = (pair<int, int>(xmin, ymin));
			points_box.at(1) = (pair<int, int>(xmin, ymax));
			points_box.at(2) = (pair<int, int>(xmax, ymax));
			points_box.at(3) = (pair<int, int>(xmax, ymin));
			aire = new_aire;
			angle = i;
		}
	}

	if (points_box.at(2).first - points_box.at(0).first<points_box.at(1).second - points_box.at(0).second) {
		angle = 90; 
	}
}
