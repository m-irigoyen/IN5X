#include "gaussianBlurHandler.hpp"

// Applique un flou gaussien sur l'image pass�e en param�tre. 
void GaussianBlurHandler::basic(Mat src, Mat & output, KERNEL_SIZE size)
{
	// Applying a gaussian blur, using the opencv function
	GaussianBlur(src, output, Size(static_cast<int>(size), static_cast<int>(size)), 0, 0);
}
