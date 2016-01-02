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

	for (int i = 50; i < 600; i = i + 50) {
		for (int j = 1; j < 8; ++j) {
			// Construction des classes
			ReconnaissanceHandler reconnaissance;
			reconnaissance.buildClasses(dbLearning, i, j);

			// Test pour une seule pièce
			/*PIECE_TYPE resultat =  reconnaissance.completeReconaissance_one("n_pion_face (13)");
			cout << "Ah ça, c'est un " << convert_pieceTypeToName(resultat) << endl;*/
			// Test pour une db complète
			vector<pair<DatabaseImageDescriptor, PIECE_TYPE>> results;
			reconnaissance.completeReconnaissance_db(dbTest, results, i, j);
			reconnaissance.analyseResults(results,i,j);
		}
	}
	
	waitKey(0);
 	return EXIT_SUCCESS;

	//videoTest();	// Lance la caméra avec une détection de contours 
}  
