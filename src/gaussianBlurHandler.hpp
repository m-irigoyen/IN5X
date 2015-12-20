#ifndef DEF_GAUSSIANBLURHANDLER
#define DEF_GAUSSIANBLURHANDLER

/*
Fonctions d'aide qui simplifient l'utilisation du flou gaussien
*/

#include "opencv2/opencv.hpp"

using namespace cv;

class GaussianBlurHandler
{
public:
	// La taille du kernel utilisé pour le flou gaussien
	enum KERNEL_SIZE
	{
		SMALL = 15,
		MEDIUM = 31,
		HIGH = 63,
		//TODO: a implémenter une fois qu'on aura trouvé les valeurs optimales
		//OPTIMAL		
	};

	// Applique un flou gaussien sur l'image passée en paramètre. 
	void static basic(Mat src, Mat& output, KERNEL_SIZE size = MEDIUM);
};


#endif // !DEF_GAUSSIANBLURHANDLER
