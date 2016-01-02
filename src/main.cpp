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
	cout << "THIS IS A TESTS" << endl;

	// Création de la base de données
	DatabaseHandler dbLearning, dbTest;
	vector<PIECE_TYPE> types;
	types.push_back(PIECE_TYPE::CAVALIER);
	types.push_back(PIECE_TYPE::FOU);
	types.push_back(PIECE_TYPE::PION);
	types.push_back(PIECE_TYPE::REINE);
	types.push_back(PIECE_TYPE::ROI);
	types.push_back(PIECE_TYPE::TOUR);

	dbLearning.buildDatabase(true, types, PIECE_ANGLE::FACE, PIECE_COLOR::NOIR);
	dbTest.buildDatabase(false, types, PIECE_ANGLE::FACE, PIECE_COLOR::NOIR);


	// Construction des classes
	ReconnaissanceHandler reconnaissance;
	reconnaissance.buildClasses(dbLearning);

	// Test pour une seule pièce
	/*PIECE_TYPE resultat =  reconnaissance.completeReconaissance_one("n_reine_face (8)");
	cout << "Ah ça, c'est un " << convert_pieceTypeToName(resultat) << endl;*/
	// Test pour une db complète
	vector<pair<DatabaseImageDescriptor, PIECE_TYPE>> results;
	reconnaissance.completeReconnaissance_db(dbTest, results);
	reconnaissance.analyseResults(results);
		
	waitKey(0);
 	return EXIT_SUCCESS;

	//videoTest();	// Lance la caméra avec une détection de contours 
}  
