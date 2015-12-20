#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"

#include "filePaths.hpp"
#include "exampleCodes.h"

using namespace cv;


// CODE POUR LES SLIDERS
void update(int, void*);
Mat src, src_gray, output;
int gaussianSize = 11;
int cannySize = 5;
int cannyThreshold = 89;

// Le main
int main(int argc, char* argv[])
{
	//videoTest();	// Lance la caméra avec une détection de contours 
	
	// Test des sliders
	Mat image;
	image = imread(PATHS::DATABASE + "b_reine_face (1).jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
	if (!image.data)
	{
		cout << "ERROR : couldn't load image" << endl;
		return -1;
	}

	resize(image, src, Size(), 0.4, 0.4);		// L'image en taille réduite
	//resize(image, src, image.size(), 0, 0);	// L'image en taille totale

	// Conversion en image niveau de gris
	src_gray.create(src.size(), src.type());
	cvtColor(src, src_gray, CV_BGR2GRAY);
	
	output.create(src_gray.size(), src_gray.type());

	
	
	//output.create(src.size(), src.type());

	// Ouvre une fenêtre
	namedWindow("test");
	
	// Les trackbars sont des sliders modifiables par l'utilisateur.
	// Modifier les chiffres ici augmente les valeurs max des sliders
	createTrackbar("G Size:", "test", &gaussianSize, 63, update);		// La taille du kernel du filtre gaussien
	createTrackbar("C Size:", "test", &cannySize, 127, update);			// La taille du kernel de l'opérateur de canny
	createTrackbar("C Thresh:", "test", &cannyThreshold, 127, update);	// La limite basse de l'opérateur de canny

	update(0, 0);

	waitKey(0);
	
	return EXIT_SUCCESS;
}

void update(int, void*)
{
	// La kernelSize doit être impaire et plus grande que 0. Sinon, ça plante.
	if (gaussianSize % 2 != 1 || cannySize < 3 || cannySize % 2 != 1)
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