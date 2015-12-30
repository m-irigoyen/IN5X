#ifndef DEF_BOX
#define DEF_BOX

#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

class Box {
public:
	Box();
	Box(vector<pair<int,int>>);

	vector<pair<int, int>> points_box;
	float aire;
};

#endif //!DEF_BOX