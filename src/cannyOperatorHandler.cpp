#include "cannyOperatorHandler.hpp"

const float CannyOperatorHandler::ratio = 3;

// Applique un op�rateur de canny sur l'image (d�j� flout�e) pass�e en param�tre. 
void CannyOperatorHandler::basic(Mat src, Mat& output, KERNEL_SIZE kernelSize)
{
	// Converting source to gray
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//TODO: d�terminer la traille du treshold
	Mat edges;
	edges.copySize(src_gray);
	Canny(src_gray, edges, 50, 50 * CannyOperatorHandler::ratio, static_cast<int>(kernelSize));

	output = Scalar::all(0);
}

// Applique un flou gaussien puis op�rateur de canny sur l'image pass�e en param�tre. 
void CannyOperatorHandler::complete(Mat src, Mat & output, KERNEL_SIZE kernelSize)
{
	// Applying gaussian blur
	Mat blurred;
	//TODO: determiner la kernelSize du flou gaussien en fonction de la valeur pr�cision voulue pour le canny.
	GaussianBlurHandler::basic(src, blurred, GaussianBlurHandler::KERNEL_SIZE::MEDIUM);

	// Doing edge detection
	CannyOperatorHandler::basic(blurred, output, kernelSize);
}
