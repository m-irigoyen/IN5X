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
	void rotation(float angle, vector <pair<int, int>>& result);
	void findDirection();
	void findPathcontour(vector<pair<int, int>>& result);
	void MAJimg();
	Box box;
private:
	Mat img;
	vector<pair<int, int>> piece;
	
};

#endif //!DEF_ROTATEPIECE