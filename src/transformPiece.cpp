#include "transformPiece.hpp"
#include "box.hpp"
#define PI 3.14159265

TransformPiece::transformPiece(Mat img)
{
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == 255) {
				piece.push_back(pair<int, int>(i, j));
			}
		}
	}
	box = Box(piece);
}

vector<pair<int,int>> TransformPiece::rotation(float angle) {
	vector<pair<int, int>> rotate_piece = piece;
	angle = angle * PI / 180;
	pair<int, int> center = pair<int, int>((box.points_box.at(0).first + box.points_box.at(2).first) / 2, (box.points_box.at(0).second + box.points_box.at(2).second) / 2);
	for (int j = 0; j < piece.size(); ++j) {
		rotate_piece.at(j).first = ((piece.at(j).first - center.first) * cos(angle) + (piece.at(j).second - center.second) * sin(angle)) + center.first;
		rotate_piece.at(j).second = - ((piece.at(j).first - center.first)* sin(angle) + (piece.at(j).second - center.second)* cos(angle)) + center.second;
	}
}

vector<pair<int, int>> TransformPiece::findDirection() {
	vector<pair<int, int>> pieceTmp, finalPiece;
	imshow("Test1", img);
	waitKey(0);
	finalPiece = piece;
	for (int i = 0; i < 360; ++i) {
		pieceTmp = rotation(i);
		Box boxtmp = Box(pieceTmp);
		if (box.aire > boxtmp.aire) {
			box.points_Box = boxtmp.points_box;
			box.aire = boxtmp.aire;
			finalPiece = pieceTmp;
		}
	}
	if (box.points_box.at(2).first - box.points_box.at(0).first > box.points_box.at(1).second - box.points_box.at(0).second) {
		piece = rotation(90);
		box = Box(finalPiece);
	}
	for (int i = 0; i < piece.size(); ++i) {
		img.at<uchar>(piece.at(i).first, piece.at(i).second) = 255;
	}

	imshow("Test2", img);
	waitKey(0);
	img = img * 0;
	int count_up = 0, count_down = 0;
	for (int i = box.points_box.at(0).second; i <= box.points_box.at(2).second; ++i) {
		if (img.at<uchar>(box.points_box.at(0).first, i) == 255) {
			count_up++;
		}
		if (img.at<uchar>(box.points_box.at(2).first, i) == 255) {
			count_down++;
		}
	}

	if (count_up > count_down) {
		piece = rotation(180);
	}
	img = img * 0;
	for (int i = 0; i < piece.size(); ++i) {
		img.at<uchar>(piece.at(i).first, piece.at(i).second) = 255;
	}
	
	imshow("Test3", img);
	waitKey(0);
	img = img * 0;
}
