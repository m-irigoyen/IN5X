#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"
#include <vector>

#include "Reconaissance/ReconaissanceHandler.h"

using namespace cv;

// Le main
int main(int argc, char* argv[])
{
	// Création de la base de données
	DatabaseHandler db;
	vector<PIECE_TYPE> types;
	types.push_back(PIECE_TYPE::CAVALIER);
	types.push_back(PIECE_TYPE::FOU);
	types.push_back(PIECE_TYPE::PION);
	types.push_back(PIECE_TYPE::REINE);
	types.push_back(PIECE_TYPE::ROI);
	types.push_back(PIECE_TYPE::TOUR);

	db.buildDatabase(true, types, PIECE_ANGLE::FACE, PIECE_COLOR::NOIR);


	// Construction des classes
	ReconnaissanceHandler reconnaissance;
	reconnaissance.buildClasses(db);

	PIECE_TYPE resultat =  reconnaissance.completeReconaissance("n_roi_face (10)");

	cout << "Ah ça, c'est un " << convert_pieceTypeToName(resultat) << endl;

		
	waitKey(0);
 	return EXIT_SUCCESS;

	//videoTest();	// Lance la caméra avec une détection de contours 
}  
