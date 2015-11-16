#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"

int imageExample(int argc, char* argv[]);

int videoTest();

using namespace cv;

int main(int argc, char* argv[])
{
	videoTest();
	
	return EXIT_SUCCESS;
}


int imageExample(int argc, char* argv[])
{
	IplImage* img = NULL;
	const char* window_title = "Hello, OpenCV!";

	/* Vérification: au moins un argument doit être passé au programme.*/
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s IMAGE\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Chargement de l'image passée en argument */
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);

	if (!img)
	{
		fprintf(stderr, "couldn't open image file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	/* Création d'une fenêtre intitulée "Hello, OpenCV!" */
	cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);

	/* Affichage de l'image */
	cvShowImage(window_title, img);

	/* Pause le temps que l'utilisateur appuie sur une touche */
	cvWaitKey(0);

	/* Destruction de la fenêtre */
	cvDestroyAllWindows();

	/* Libération de la mémoire */
	cvReleaseImage(&img);
}


int videoTest()
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

