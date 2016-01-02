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
	// DESCRIPTEUR
	/*vector<pair<float, float>> points = *new vector<pair<float, float>>(5, *new pair<float, float>(0, 0));
	points.at(0) = (*new pair<float, float>(0, 0));
	points.at(1) = (*new pair<float, float>(3, 4));
	points.at(2) = (*new pair<float, float>(5, 20));
	points.at(3) = (*new pair<float, float>(35, 40));
	points.at(4) = (*new pair<float, float>(-5, 0));

	tangent_descriptor descript = *new tangent_descriptor(points, 1);*/



	/*DatabaseHandler db;
	db.buildDatabase(false, PIECE_TYPE::CAVALIER, PIECE_ANGLE::COTE, PIECE_COLOR::NOIR);

	namedWindow("test");
	vector<DatabaseImage>& images = db.getImages();
	for (DatabaseImage dbi : images)
	{
		cout << "Type : " << dbi.descriptor.type << endl;
		cout << "Angle : " << dbi.descriptor.angle << endl;
		cout << "Color : " << dbi.descriptor.color << endl;
		imshow("test", dbi.mat);
		waitKey(0);
	}*/

	//UNCOMMENT THAT

	//// fix des fuites de mémoire par rapport au code ci-dessus
	//vector<pair<float, float>> points;
	//points.push_back(pair<float, float>(0, 0));
	//points.push_back(pair<float, float>(3, 4));
	//points.push_back(pair<float, float>(5, 20));
	//points.push_back(pair<float, float>(35, 40));
	//points.push_back(pair<float, float>(-5, 0));

	//tangent_descriptor descript(points, 1);

	//
	//// TEST TRAITEMENT IMAGE
	/*namedWindow("sisimagueule");
	ImageTester tester;
	tester.testImage_cannyMethod("n_cavalier_face (1).jpg");
	waitKey(0);

	tester.setImage("n_roi_face (1).jpg");
	tester.testImageCallback_cannyMethod(0, &tester);
	waitKey(0);

	tester.setImage("n_cavalier_cote (1).jpg");
	tester.testImageCallback_cannyMethod(0, &tester);
	waitKey(0);

	tester.setImage("n_fou_face (1).jpg");
	tester.testImageCallback_cannyMethod(0, &tester);
	waitKey(0);

	tester.setImage("n_fou_cote (1).jpg");
	tester.testImageCallback_cannyMethod(0, &tester);
	waitKey(0);

	tester.setImage("n_reine_face (1).jpg");
	tester.testImageCallback_cannyMethod(0, &tester);
	waitKey(0);*/

	ImageHandler handler;
	Mat image,contour;

	if (!ImageHandler::loadImage("n_roi_face (10)", image))

	{
		cout << "erreur : probleme de chargement de l'image." << endl;
		return EXIT_FAILURE;
	}
	handler.prepareImage_canny(image, contour);

	imshow("Image1", contour);
	waitKey(0);
	TransformPiece tpiece = TransformPiece(contour);
	rectangle(contour, Point(tpiece.box.points_box.at(0).first, tpiece.box.points_box.at(0).second), Point(tpiece.box.points_box.at(2).first, tpiece.box.points_box.at(2).second), Scalar(255, 255, 255));
	imshow("Image1", contour);
	waitKey(0);
 	tpiece.findDirection();
	vector<pair<int, int>> path = tpiece.findPathcontour();
	waitKey(0);
 	return EXIT_SUCCESS;

	//videoTest();	// Lance la caméra avec une détection de contours 
}  
