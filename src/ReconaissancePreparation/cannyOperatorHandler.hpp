#ifndef DEF_CANNYOPERATORHANDLER
#define DEF_CANNYOPERATORHANDLER

/*
Fonctions d'aide qui simplifient l'utilisation de l'op�rateur de Canny (d�tection de contours)
*/

#include "opencv2/opencv.hpp"

using namespace cv;

class CannyOperatorHandler
{
public : 
	// Le treshold utilis� par l'op�rateur de canny
	enum THRESHOLD_SIZE
	{
		CT_LOW = 3,
		CT_MED = 50,
		CT_HIGH = 99,
		CT_OPTIMAL = 70
	};

	// La taille du kernel utilis�e par l'op�rateur de canny
	enum KERNEL_SIZE
	{
		CK_SMALL = 3,		// garde peu de contours
		CK_MEDIUM = 7,		// garde les contours en moyenne
		CK_BIG = 15,		// garde beaucoup de contours
		CK_OPTIMAL = 3
	};

	// Applique un op�rateur de canny sur l'image (d�j� flout�e) pass�e en param�tre. 
	void static basic(Mat src, Mat& output, int kernelSize = (int)KERNEL_SIZE::CK_OPTIMAL, int threshold = (int)THRESHOLD_SIZE::CT_OPTIMAL);
	// Applique un op�rateur de canny sur l'image (d�j� flout�e) pass�e en param�tre. 
	//void static basic(Mat src, Mat& output, KERNEL_SIZE kernelSize = KERNEL_SIZE::CK_OPTIMAL, THRESHOLD_SIZE thresholdSize = THRESHOLD_SIZE::CT_OPTIMAL);

private :
	static const float ratio;	// le ratio pour l'op�rateur de Canny. Par d�faut mis � 3, comme recommand� par Canny
};


#endif // !DEF_CANNYOPERATORHANDLER
