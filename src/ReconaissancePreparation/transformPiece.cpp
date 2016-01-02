#include "transformPiece.hpp"
#define PI 3.14159265

TransformPiece::TransformPiece(Mat& i){
	img = i;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == 255) {
				piece.push_back(pair<int, int>(i, j));
			}
		}
	}
	box = Box(piece);
}
void TransformPiece::MAJimg() {
	for (int i = 0; i < piece.size(); ++i) {
		img.at<uchar>(piece.at(i).first, piece.at(i).second) = 255;
	}
}
void TransformPiece::rotation(float angle, vector <pair<int, int>>& result) {
	result = piece;
	angle = angle * PI / 180;
	pair<int, int> center = pair<int, int>((box.points_box.at(0).second + box.points_box.at(2).second) / 2, (box.points_box.at(0).first + box.points_box.at(2).first) / 2);
	for (int j = 0; j < piece.size(); ++j) {
		result.at(j).first = ((piece.at(j).first - center.first) * cos(angle) + (piece.at(j).second - center.second) * sin(angle)) + center.first;
		result.at(j).second =  (-(piece.at(j).first - center.first)* sin(angle) + (piece.at(j).second - center.second)* cos(angle)) + center.second;
	}
}

void TransformPiece::findDirection() {
	vector<pair<int, int>> pieceTmp, finalPiece;
	finalPiece = piece;
	Box box_final = box;
	for (int i = 0; i < 360; ++i) {
		rotation(i, pieceTmp);
		Box boxtmp = Box(pieceTmp);
		if (box_final.aire > boxtmp.aire) {
			box_final.points_box = boxtmp.points_box;
			box_final.aire = boxtmp.aire;
			finalPiece = pieceTmp;
		}
	}
	box.points_box = box_final.points_box;
	box.aire = box_final.aire;
	piece = finalPiece;
	if (box.points_box.at(2).first - box.points_box.at(0).first > box.points_box.at(1).second - box.points_box.at(0).second) {
		rotation(90, piece);
		box = Box(piece);
	}
	img = img * 0;
	MAJimg();
	int first_up = -1, first_down = -1, last_up, last_down;
	for (int i = box.points_box.at(0).first; i <= box.points_box.at(2).first; ++i) {
		if (img.at<uchar>(box.points_box.at(0).second+4, i) == 255) {
			if (first_up == -1) {
				first_up = i;
			}
			last_up = i;
		}
		if (img.at<uchar>(box.points_box.at(2).second-4, i) == 255) {
			if (first_down == -1) {
				first_down = i;
			}
			last_down = i;
		}
	}
		
   	if (last_up-first_up > last_down-first_down) {
		rotation(180,piece);
		box = Box(piece);
	}

	img = img * 0;
	MAJimg();
}

void TransformPiece::findPathcontour(vector<pair<int, int>>& result) {
	result.clear()
		;
	bool test = true;
 	int i = img.rows - 1;

	int x = box.points_box.at(0).first;
	while (test) {
		if (img.at<uchar>(i, x) == 255) {
			result.push_back(pair<float, float>(i, x));
			test = false;
		}
		--i;
		if (i == -1) {
			i = img.rows - 1;
			x++;
		}
	}
	int j = 0;
	bool testclose = true;


	while (testclose) {
		pair<int, int> p = result.at(j);
		bool test_neighboor = true;
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

			if (j == 0) {
				for (int x = 0; x < neighboors.size(); ++x) {
					if (neighboors.at(x).first + 1 == p.first) {
						result.push_back(neighboors.at(x));
						test_neighboor = false;
					}
				}
			}
			else {
				for (int x = 0; x < neighboors.size(); ++x) {
					if (j > 50 && std::find(neighboors.begin(), neighboors.end(), result.at(0)) != neighboors.end()) {
						test_neighboor = false;
						testclose = false;
					}
					if (std::find(result.begin(), result.end(), neighboors.at(x)) != result.end()) {
						neighboors.erase(neighboors.begin() + x);
						--x;
					}
				}
				if (neighboors.size() == 1) {
					result.push_back(neighboors.at(0));
					test_neighboor = false;
				}
				else if (neighboors.size()>1) {
					for (int x = 0; x < neighboors.size(); ++x) {
						if ((p.first == neighboors.at(x).first || p.second == neighboors.at(x).second) && test_neighboor == false) {
							result.push_back(neighboors.at(x));
							test_neighboor = false;
						}
					}
					if (test_neighboor == true) {
						float dist_mini = 40000, dist;
						int index_dist_mini;
						for (int x = 0; x < neighboors.size(); ++x) {
							dist = sqrt(pow(p.first - neighboors.at(x).first, 2) + pow(p.second - neighboors.at(x).second, 2));
							if (dist < dist_mini) {
								index_dist_mini = x;
								dist_mini = dist;
							}
						}
						result.push_back(neighboors.at(index_dist_mini));
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
	for (int i = 0; i < result.size(); ++i) {
		img2.at<uchar>(result.at(i).first, result.at(i).second) = 255;
	}
}