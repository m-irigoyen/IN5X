#include "ImageTester.h"

ImageTester::ImageTester()
{
	this->gaussianSize = GaussianBlurHandler::GBK_OPTIMAL;
	this->cannySize = CannyOperatorHandler::KERNEL_SIZE::CK_OPTIMAL;
	this->cannyThreshold = CannyOperatorHandler::THRESHOLD_SIZE::CT_OPTIMAL;
	this->threshold = TresholdingHandler::T_OPTIMAL;
}

void ImageTester::testImage_cannyMethod(string imageName)
{
	Mat image;
	image = imread(PATHS::DATABASE2 + imageName, CV_LOAD_IMAGE_COLOR);   // Read the file
	if (!image.data)
	{
		cout << "ERROR : couldn't load image" << endl;
		return;
	}

	// Resizing image, and converting to grayscale
	resize(image, src, Size(), 0.4, 0.4);		
	//resize(image, src, image.size(), 0, 0);	// L'image en taille totale
	ImageHandler::convert_colorToGray(src, src_gray);

	// Ouvre une fenêtre
	namedWindow("test");

	// Les trackbars sont des sliders modifiables par l'utilisateur.
	// Modifier les chiffres ici augmente les valeurs max des sliders
	createTrackbar("G Size:", "test", &gaussianSize, 63, &testImageCallback_cannyMethod,this);		// La taille du kernel du filtre gaussien
	createTrackbar("C Size:", "test", &cannySize, 5, &testImageCallback_cannyMethod, this);			// La taille du kernel de l'opérateur de canny
	createTrackbar("C Thresh:", "test", &cannyThreshold, 127, &testImageCallback_cannyMethod, this);	// La limite basse de l'opérateur de canny
	createTrackbar("Thresh:", "test", &threshold, 255, &testImageCallback_cannyMethod, this);	// La limite basse de l'opérateur de canny

	this->testImageCallback_cannyMethod(0,this);
}

void ImageTester::testImageCallback_cannyMethod(int, void * object)
{
	ImageTester* t = static_cast<ImageTester*>(object);

	if (t == NULL)
		return;

	// La kernelSize doit être impaire et plus grande que 0. Sinon, ça plante.
	if (t->gaussianSize % 2 != 1 || t->cannySize < 3 || t->cannySize % 2 != 1 || t->cannySize >= 7)
		return;

	ImageHandler::prepareImage_canny(t->src_gray, t->output, t->gaussianSize, t->cannySize, t->cannyThreshold, t->threshold);

	imshow("test", t->output);

	// Code pour utiliser canny comme un masque sur l'image initiale
	///// Using Canny's output as a mask, we display our result
	//masked = Scalar::all(0);

	//src.copyTo(masked, output);
}
