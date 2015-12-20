#ifndef DEF_CANNYOPERATORHANDLER
#define DEF_CANNYOPERATORHANDLER

/*
Fonctions d'aide qui simplifient l'utilisation de l'op�rateur de Canny (d�tection de contours)
*/

#include "opencv2/opencv.hpp"
#include "gaussianBlurHandler.hpp"

using namespace cv;

class CannyOperatorHandler
{
public : 
	// Le treshold utilis� par l'op�rateur de canny
	enum THRESHOLD_SIZE
	{
		LOW = 3,
		MED = 50,
		HIGH = 99,
		//TODO: a impl�menter une fois qu'on aura trouv� les valeurs optimales
		//OPTIMAL
	};

	// La taille du kernel utilis�e par l'op�rateur de canny
	enum KERNEL_SIZE
	{
		SMALL = 3,		// garde peu de contours
		MEDIUM = 7,		// garde les contours en moyenne
		BIG = 15,		// garde beaucoup de contours
		//TODO: a impl�menter une fois qu'on aura trouv� les valeurs optimales
		//OPTIMAL		
	};

	// Applique un op�rateur de canny sur l'image (d�j� flout�e) pass�e en param�tre. 
	void static basic(Mat src, Mat& output, KERNEL_SIZE kernelSize);

	// Applique un flou gaussien puis op�rateur de canny sur l'image pass�e en param�tre. 
	void static complete(Mat src, Mat& output, KERNEL_SIZE kernelSize);

private :
	static const float ratio;	// le ratio pour l'op�rateur de Canny. Par d�faut mis � 3, comme recommand� par Canny
};


#endif // !DEF_CANNYOPERATORHANDLER
