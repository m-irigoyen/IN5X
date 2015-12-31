#include "transformPiece.hpp"
#define PI 3.14159265

TransformPiece::TransformPiece(Mat i){
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
vector<pair<int,int>> TransformPiece::rotation(float angle) {
	vector<pair<int, int>> rotate_piece = piece;
	angle = angle * PI / 180;
	pair<int, int> center = pair<int, int>((box.points_box.at(0).second + box.points_box.at(2).second) / 2, (box.points_box.at(0).first + box.points_box.at(2).first) / 2);
	for (int j = 0; j < piece.size(); ++j) {
		rotate_piece.at(j).first = ((piece.at(j).first - center.first) * cos(angle) + (piece.at(j).second - center.second) * sin(angle)) + center.first;
		rotate_piece.at(j).second =  (-(piece.at(j).first - center.first)* sin(angle) + (piece.at(j).second - center.second)* cos(angle)) + center.second;
	}

	return rotate_piece;
}

void TransformPiece::findDirection() {
	vector<pair<int, int>> pieceTmp, finalPiece;
	finalPiece = piece;
	Box box_final = box;
	for (int i = 0; i < 360; ++i) {
		pieceTmp = rotation(i);
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
		piece = rotation(90);
		box = Box(finalPiece);
	}

	MAJimg();
	imshow("bite", img);
	waitKey(0);
	int count_up = 0, count_down = 0;
	for (int i = box.points_box.at(0).first; i <= box.points_box.at(2).first; ++i) {
		if (img.at<uchar>(box.points_box.at(0).second, i) == 255) {
			count_up++;
		}
		if (img.at<uchar>(box.points_box.at(2).second, i) == 255) {
			count_down++;
		}
	}
		
   	if (count_up > count_down) {
		piece = rotation(180);
		box = Box(piece);
	}
	/*img = img * 0;
	for (int i = 0; i < piece.size(); ++i) {
		img.at<uchar>(piece.at(i).first, piece.at(i).second) = 255;
	}*/
	img = img * 0;
	MAJimg();
	imshow("Test3", img);
	waitKey(0);
}

vector<pair<int,int>> TransformPiece::findPathcontour() {
	vector<pair<int, int>> path = vector<pair<int, int>>();
	bool test = true;
 	int i = img.rows - 1;

	int x = box.points_box.at(0).first;
	while (test) {
		if (img.at<uchar>(i, x) == 255) {
			path.push_back(pair<float, float>(i, x));
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
		pair<int, int> p = path.at(j);
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
						path.push_back(neighboors.at(x));
						test_neighboor = false;
					}
				}
			}
			else {
				for (int x = 0; x < neighboors.size(); ++x) {
					if (j > 50 && std::find(neighboors.begin(), neighboors.end(), path.at(0)) != neighboors.end()) {
						test_neighboor = false;
						testclose = false;
					}
					if (std::find(path.begin(), path.end(), neighboors.at(x)) != path.end()) {
						neighboors.erase(neighboors.begin() + x);
						--x;
					}
				}
				if (neighboors.size() == 1) {
					path.push_back(neighboors.at(0));
					test_neighboor = false;
				}
				else if (neighboors.size()>1) {
					for (int x = 0; x < neighboors.size(); ++x) {
						if ((p.first == neighboors.at(x).first || p.second == neighboors.at(x).second) && test_neighboor == false) {
							path.push_back(neighboors.at(x));
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
						path.push_back(neighboors.at(index_dist_mini));
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
	for (int i = 0; i < path.size(); ++i) {
		img2.at<uchar>(path.at(i).first, path.at(i).second) = 255;
	}
	imshow("testtamère", img2);
	waitKey(0);
	return path;
}