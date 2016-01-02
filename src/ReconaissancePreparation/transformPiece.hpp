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
	TransformPiece(Mat&);
	vector<pair<int,int>> rotation(float angle, vector <pair<int, int>> result);
	void findDirection();
	void findPathcontour(vector<pair<int, int>>& result);
	void MAJimg();
	Box box;
	Mat img;
private:
	vector<pair<int, int>> piece;
	
};

#endif //!DEF_ROTATEPIECE