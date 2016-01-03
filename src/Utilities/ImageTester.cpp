#include "ImageTester.h"

ImageTester::ImageTester()
{
	this->gaussianSize = GaussianBlurHandler::GBK_OPTIMAL;
	this->cannySize = CannyOperatorHandler::KERNEL_SIZE::CK_OPTIMAL;
	this->cannyThreshold = CannyOperatorHandler::THRESHOLD_SIZE::CT_OPTIMAL;
	this->threshold = TresholdingHandler::T_OPTIMAL;
}

void ImageTester::setImage(string imageName)
{
	Mat image;
	ImageHandler::loadImage(imageName, image);   // Read the file
	if (!image.data)
	{
		cout << "ERROR : couldn't load image" << endl;
		return;
	}
	this->src = image;
}

void ImageTester::testImage_cannyMethod(string imageName)
{
	

	// Ouvre une fenêtre
	namedWindow("test");
	this->setImage(imageName);

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

	ImageHandler::prepareImage_canny(t->src, t->output, t->gaussianSize, t->cannySize, t->cannyThreshold, t->threshold);

	//resize(t->output, t->output, cv::Size(), 0.6, 0.6);
	imshow("test", t->output);

	// Code pour utiliser canny comme un masque sur l'image initiale
	///// Using Canny's output as a mask, we display our result
	//masked = Scalar::all(0);

	//src.copyTo(masked, output);
}
