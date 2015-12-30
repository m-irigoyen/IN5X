#include "gaussianBlurHandler.hpp"

// Applique un flou gaussien sur l'image passée en paramètre. 
void GaussianBlurHandler::basic(Mat src, Mat & output, int size)
{
	if (size % 2 != 1)
	{
		std::cout << "GaussianBlurHandler : ERROR : size must be odd (impaire)" << std::endl;
		return;
	}
	// Applying a gaussian blur, using the opencv function
	GaussianBlur(src, output, Size(static_cast<int>(size), static_cast<int>(size)), 0, 0);
}

//void GaussianBlurHandler::basic(Mat src, Mat & output, GB_KERNEL_SIZE size)
//{
//	GaussianBlurHandler::basic(src, output, (int)size);
//}
