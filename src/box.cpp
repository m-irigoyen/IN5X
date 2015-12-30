#include "box.hpp"

#define PI 3.14159265

Box::Box(Mat img)
{

	imshow("Imagedepart", img);
	waitKey(0);
	int xmin, ymin, xmax, ymax;
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
	pair<int, int> center((xmin + xmax) / 2, (ymin + ymax) / 2);
	float aire = sqrt(pow(points_box.at(0).first - points_box.at(1).first, 2) + pow(points_box.at(0).second - points_box.at(1).second, 2)) * sqrt(pow(points_box.at(1).first - points_box.at(2).first, 2) + pow(points_box.at(1).second - points_box.at(2).second, 2));
	vector<pair<int, int>> new_white = white;
	vector<pair<int, int>> fin_white = white;
	for (int i = 1; i < 360; ++i) {
		for (int j = 0; j < white.size(); ++j) {
			new_white.at(j).first = ((white.at(j).first - center.first) * cos(i * PI / 180.0) - (white.at(j).second - center.second) * sin(i * PI / 180.0)) + center.first;
			new_white.at(j).second = ((white.at(j).first - center.first)* sin(i * PI / 180.0) + (white.at(j).second - center.second)* cos(i * PI / 180.0)) + center.second;
		}
		int xmin_tmp = 40000;
		int ymin_tmp = 40000;
		int xmax_tmp = -1;
		int ymax_tmp = -1;
		for (int k = 0; k < new_white.size(); ++k) {
			pair<int, int> p = new_white.at(k);
			if (p.first < xmin_tmp) {
				xmin_tmp = p.first;
			}
			if (p.first > xmax_tmp) {
				xmax_tmp = p.first;
			}
			if (p.second < ymin_tmp) {
				ymin_tmp = p.second;
			}
			if (p.second > ymax_tmp) {
				ymax_tmp = p.second;
			}
		}
		float new_aire = sqrt(pow(xmin_tmp - xmin_tmp, 2) + pow(ymin_tmp - ymax_tmp, 2)) * sqrt(pow(xmin_tmp - xmax_tmp, 2) + pow(ymax_tmp - ymax_tmp, 2));
		if (new_aire < aire) {
			aire = new_aire;
			fin_white = new_white;
			xmax = xmax_tmp;
			ymax = ymax_tmp;
			xmin = xmin_tmp;
			ymin = ymin_tmp;
			points_box.at(0) = (pair<int, int>(xmin, ymin));
			points_box.at(1) = (pair<int, int>(xmin, ymax));
			points_box.at(2) = (pair<int, int>(xmax, ymax));
			points_box.at(3) = (pair<int, int>(xmax, ymin));
		}
	}
	if (points_box.at(2).first - points_box.at(0).first<points_box.at(1).second - points_box.at(0).second) { 
		for (int j = 0; j < white.size(); ++j) {
			fin_white.at(j).first = ((white.at(j).first - center.first) * cos(90 * PI / 180.0) - (white.at(j).second - center.second) * sin(90 * PI / 180.0)) + center.first;
			fin_white.at(j).second = ((white.at(j).first - center.first)* sin(90 * PI / 180.0) + (white.at(j).second - center.second)* cos(90 * PI / 180.0)) + center.second;
		}
		int xmin = 40000;
		int ymin = 40000;
		int xmax = -1;
		int ymax = -1;
		for (int k = 0; k < fin_white.size(); ++k) {
			pair<int, int> p = fin_white.at(k);
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

			points_box.at(0) = (pair<int, int>(xmin, ymin));
			points_box.at(1) = (pair<int, int>(xmin, ymax));
			points_box.at(2) = (pair<int, int>(xmax, ymax));
			points_box.at(3) = (pair<int, int>(xmax, ymin));
		}
	}
	img = img * 0;
	for (int i = 0; i < fin_white.size(); ++i) {
		img.at<uchar>(fin_white.at(i).first, fin_white.at(i).second) = 255;
	}
	int count_up = 0, count_down = 0;
	for (int i = points_box.at(0).second; i <= points_box.at(2).second; ++i) {
		if (img.at<uchar>(ymin, i) == 255) {
			count_up++;
		}
		if (img.at<uchar>(ymax, i) == 255) {
			count_down++;
		}
	}

	if (count_up > count_down) {
		for (int j = 0; j < white.size(); ++j) {
			fin_white.at(j).first = ((white.at(j).first - center.first) * cos(PI)) - (white.at(j).second - center.second) * sin(PI) + center.first;
			fin_white.at(j).second = ((white.at(j).first - center.first)* sin(PI)) + (white.at(j).second - center.second)* cos(PI) + center.second;
		}
	}
	img = img * 0;
	for (int i = 0; i < fin_white.size(); ++i) {
		img.at<uchar>(fin_white.at(i).first, fin_white.at(i).second) = 255;
	}
	//imshow("Image1", img);
	//waitKey(0);
	white = vector<pair<int, int>>();

	bool test = true;
	int i = img.rows-1;
	while (test) {
		if (img.at<uchar>(i, points_box.at(0).second) == 255) {
			white.push_back(pair<float, float>(i, points_box.at(0).second));
			test = false;
		}
		--i;
	}
	imshow("Image1", img);
	waitKey(0);
	int j = 0;
	bool testclose = true;
	while(testclose){
		pair<int, int> p = white.at(j);
		bool test_neighboor = true;
		if (j > 469) {
			i = 0;
		}
		int z = 1;
		while (test_neighboor) {
			vector<pair<int, int>> neighboors = vector<pair<int, int>>();
			for (int x = p.second - z; x <= p.second + z; ++x) {
				for (int y = p.first - z; y <= p.first + z; ++y) {
					if (x != p.second || y != p.first) {
						if (img.at<uchar>(y, x) == 255) {
							neighboors.push_back(pair<int, int>(y, x));
						}
					}
				}
			}
			if (j == 1) {
				for (int x = 0; x < neighboors.size(); ++x) {
					if (neighboors.at(x).first + 1 == p.first) {
						white.push_back(neighboors.at(x));
						test_neighboor = false;
					}
				}
			}
			else {
				for (int x = 0; x < neighboors.size(); ++x) {
					if (std::find(white.begin(), white.end(), neighboors.at(x)) != white.end()) {
						neighboors.erase(neighboors.begin() + x);
						--x;
					}
					if (j > 50 && std::find(neighboors.begin(), neighboors.end(), white.at(0)) != neighboors.end()) {
						test_neighboor = false;
						testclose = false;
					}
				}
				if (neighboors.size() == 1) {
					white.push_back(neighboors.at(0));
					test_neighboor = false;
				}
				else if(neighboors.size()>1){
					for (int x = 0; x < neighboors.size(); ++x) {
						if ((p.first == neighboors.at(x).first || p.second == neighboors.at(x).second)&& test_neighboor==false) {
							white.push_back(neighboors.at(x));
							test_neighboor = false;
						}
					}
					if (test_neighboor == true) {
						float dist_mini = 40000,dist;
						int index_dist_mini;
						for (int x = 0; x < neighboors.size(); ++x) {
							dist = sqrt(pow(p.first - neighboors.at(x).first, 2) + pow(p.second - neighboors.at(x).second, 2));
							if (dist < dist_mini) {
								index_dist_mini = x;
								dist_mini = dist;
							}
						}
						white.push_back(neighboors.at(index_dist_mini));
						test_neighboor = false;

					}
				}
				else {
					++z;
				}
			}
		}		
		++j;
	}
	Mat img2 = img * 0;
	for (int i = 0; i < white.size(); ++i) {
		img2.at<uchar>(white.at(i).first, white.at(i).second) = 255;
	}
	imshow("testtamère", img2);
	waitKey(0);
}
