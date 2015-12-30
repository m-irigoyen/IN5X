#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"
#include <vector>


#include "Utilities/filePaths.hpp"
#include "Utilities/exampleCodes.h"
#include "ReconaissancePreparation/tangent_descriptor.hpp"
#include "ReconaissancePreparation/box.hpp"
#include "Utilities/ImageTester.h"
#include "ReconaissancePreparation/ImageHandler.h"
#include "ReconaissancePreparation/transformPiece.hpp"
#include "Utilities/databaseHandler.hpp"

using namespace cv;


// Le main
int main(int argc, char* argv[])
{
	// construction de la base de données
	/*DatabaseHandler db;
	db.buildDatabase(false, PIECE_TYPE::CAVALIER, PIECE_ANGLE::COTE, PIECE_COLOR::NOIR);*/

	vector<pair<float, float>> points;
	points.push_back(pair<float, float>(0, 0));
	points.push_back(pair<float, float>(3, 4));
	points.push_back(pair<float, float>(5, 20));
	points.push_back(pair<float, float>(35, 40));
	points.push_back(pair<float, float>(-5, 0));

	tangent_descriptor descript(points, 1);

	
	// TEST TRAITEMENT IMAGE
	ImageTester tester;
	tester.testImage_cannyMethod("n_roi_face (1).jpg");

	ImageHandler handler;
	Mat image,contour;

	if (!ImageHandler::loadImage(PATHS::DATABASE2 + "n_cavalier_cote (1).jpg", image))
	{
		cout << "ERREUR : probleme de chargement de l'image." << endl;
		return EXIT_FAILURE;
	}
	handler.prepareImage_canny(image, contour);
	TransformPiece tpiece = TransformPiece(contour);
	tpiece.findDirection();
	vector<pair<int, int>> path = tpiece.findPathcontour();
	waitKey(0);
 	return EXIT_SUCCESS;

	//videoTest();	// Lance la caméra avec une détection de contours 
}