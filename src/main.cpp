#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"

#include "filePaths.hpp"
#include "exampleCodes.h"
#include "Polynome.hpp"
#include "tangent_descriptor.hpp"
#include <vector>
using namespace cv;

/*
TOUT CA : c'est un bon gros test codé dans le main, bien sale, comme on l'aime.
Pour l'instant, ça prend une image et ça fait flou gaussien + opérateur de canny, avec des sliders pour paramétrer les valeurs
*/

// CODE POUR LES SLIDERS
void update(int, void*);
void updateG(int, void*);

Mat src, src_binary, src_quadRemoved, src_gray, output;
int gaussianSize = 11;
int cannySize = 5;
int cannyThreshold = 89;
int thresh = 127;

// Le main
int main(int argc, char* argv[])
{
	// DESCRIPTEUR
	vector<pair<float, float>> points = *new vector<pair<float, float>>(5, *new pair<float, float>(0, 0));
	points.at(0) = (*new pair<float, float>(0, 0));
	points.at(1) = (*new pair<float, float>(3, 4));
	points.at(2) = (*new pair<float, float>(5, 20));
	points.at(3) = (*new pair<float, float>(35, 40));
	points.at(4) = (*new pair<float, float>(-5, 0));

	tangent_descriptor descript = *new tangent_descriptor(points, 1);


	// TEST TRAITEMENT IMAGE
	//videoTest();	// Lance la caméra avec une détection de contours 
	
	// Test des sliders
	Mat image;
	image = imread(PATHS::DATABASE + "b_roi_face (paint).jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
	if (!image.data)
	{
		cout << "ERROR : couldn't load image" << endl;
		return -1;
	}

	resize(image, src, Size(), 0.4, 0.4);		// L'image en taille réduite
	//resize(image, src, image.size(), 0, 0);	// L'image en taille totale

	namedWindow("test");

	// Conversion en image niveau de gris
	cvtColor(src, src_gray, CV_BGR2GRAY);

	createTrackbar("Gauss:", "test", &gaussianSize, 63, updateG);		// La taille du kernel du filtre gaussien
	createTrackbar("tresh:", "test", &thresh, 255, updateG);		// La taille du kernel du filtre gaussien

	// Suppression du quadrillage par création d'un masque en binarizant
	updateG(0, 0);
	waitKey(0);
	return 0;

	//// Conversion en image niveau de gris
	//src_gray.create(src_hsl.size(), src_hsl.type());
	//cvtColor(src_hsl, src_gray, CV_BGR2GRAY);
	//
	////output.create(src_gray.size(), src_gray.type());
	////output.create(src.size(), src.type());

	//// Ouvre une fenêtre
	//namedWindow("test");
	//imshow("test", src_gray);
	//
	//// Les trackbars sont des sliders modifiables par l'utilisateur.
	//// Modifier les chiffres ici augmente les valeurs max des sliders
	//createTrackbar("G Size:", "test", &gaussianSize, 63, update);		// La taille du kernel du filtre gaussien
	//createTrackbar("C Size:", "test", &cannySize, 5, update);			// La taille du kernel de l'opérateur de canny
	//createTrackbar("C Thresh:", "test", &cannyThreshold, 127, update);	// La limite basse de l'opérateur de canny

	////update(0, 0);

	//waitKey(0);
	//
	//return EXIT_SUCCESS;
}

void updateG(int, void*)
{
	if (gaussianSize % 2 != 1)
		return;
	GaussianBlur(src_gray, src_binary, Size(gaussianSize, gaussianSize), 0, 0);
	threshold(src_binary, src_binary, thresh, 255, THRESH_BINARY);
	imshow("test", src_binary);
}

void update(int, void*)
{
	// La kernelSize doit être impaire et plus grande que 0. Sinon, ça plante.
	if (gaussianSize % 2 != 1 || cannySize < 3 || cannySize % 2 != 1  || cannySize >= 7)
		return;

	// On applique le flou gaussien
	Mat edges;
	GaussianBlur(src_gray, edges, Size(gaussianSize, gaussianSize), 0, 0);

	// L'opérateur de canny : on lui met comme treshold (limite) la valeur du slider, et comme max la valeur du slider *3 (comme conseillé par Canny lui même)
	Canny(edges, edges, cannyThreshold, cannyThreshold *3, cannySize);
	//Canny(edges, edges, 1, 1 * 3, 3);

	/// Using Canny's output as a mask, we display our result
	output = Scalar::all(0);

	src.copyTo(output, edges);
	//imshow(window_name, dst);
	

	imshow("test", output);
}