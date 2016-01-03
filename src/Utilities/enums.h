#ifndef DEF_ENUMS
#define DEF_ENUMS

#include "opencv2/opencv.hpp"
using namespace cv;

enum PIECE_COLOR
{
	BLANC = 0,
	NOIR
};

enum PIECE_TYPE
{
	PION = 0,
	TOUR,
	FOU,
	CAVALIER,
	REINE,
	ROI
};

enum PIECE_ANGLE
{
	FACE = 0,
	HAUT,
	COTE,
	DOS
};

struct DatabaseImageDescriptor
{
	PIECE_TYPE type;
	PIECE_ANGLE angle;
	PIECE_COLOR color;
	int number;
};

struct DatabaseImage
{
	Mat mat;
	DatabaseImageDescriptor descriptor;
};

#endif