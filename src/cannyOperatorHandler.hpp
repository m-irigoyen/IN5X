#ifndef DEF_CANNYOPERATORHANDLER
#define DEF_CANNYOPERATORHANDLER

/*
Fonctions d'aide qui simplifient l'utilisation de l'opérateur de Canny (détection de contours)
*/

#include "opencv2/opencv.hpp"
#include "gaussianBlurHandler.hpp"

using namespace cv;

class CannyOperatorHandler
{
public : 
	// Le treshold utilisé par l'opérateur de canny
	enum THRESHOLD_SIZE
	{
		LOW = 3,
		MED = 50,
		HIGH = 99,
		//TODO: a implémenter une fois qu'on aura trouvé les valeurs optimales
		//OPTIMAL
	};

	// La taille du kernel utilisée par l'opérateur de canny
	enum KERNEL_SIZE
	{
		SMALL = 3,		// garde peu de contours
		MEDIUM = 7,		// garde les contours en moyenne
		BIG = 15,		// garde beaucoup de contours
		//TODO: a implémenter une fois qu'on aura trouvé les valeurs optimales
		//OPTIMAL		
	};

	// Applique un opérateur de canny sur l'image (déjà floutée) passée en paramètre. 
	void static basic(Mat src, Mat& output, KERNEL_SIZE kernelSize);

	// Applique un flou gaussien puis opérateur de canny sur l'image passée en paramètre. 
	void static complete(Mat src, Mat& output, KERNEL_SIZE kernelSize);

private :
	static const float ratio;	// le ratio pour l'opérateur de Canny. Par défaut mis à 3, comme recommandé par Canny
};


#endif // !DEF_CANNYOPERATORHANDLER
