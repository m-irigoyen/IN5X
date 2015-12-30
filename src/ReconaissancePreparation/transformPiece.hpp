#ifndef DEF_TRANSFORMPIECE
#define DEF_TRANSFORMPIECE

#include <stdio.h>
#include <stdlib.h>
#include "box.hpp"
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

class TransformPiece {
public:
	transformPiece(Mat);
	vector <pair<int,int>> rotation(float angle);
	vector <pair<int, int>> findDirection();
private:
	Mat img;
	vector<pair<int, int>> piece;
	Box box;
};

#endif //!DEF_ROTATEPIECE