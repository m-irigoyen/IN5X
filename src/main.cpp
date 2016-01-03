#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"
#include <vector>

#include "Reconaissance/ReconaissanceHandler.h"
#include "Utilities/ImageTester.h"

using namespace cv;

// Le main
int main(int argc, char* argv[])
{
		// POUR TESTER DES IMAGES C'EST LA
	/*ImageTester test;
	test.testImage_cannyMethod("b_cavalier_cote (1)");*/

	// Création de la base de données
	DatabaseHandler dbLearning, dbTest, dbAll;
	DatabaseHandler::buildDatabase_allBlackFace(dbLearning, dbTest, dbAll);

	cout << "Database built" << endl;

	for (int i = 50; i < 600; i = i + 50) {
		for (int j = 1; j < 3; ++j) {
			// Construction des classes
			ReconnaissanceHandler reconnaissance;
			reconnaissance.buildClassesPCA(dbLearning, i, j);
			//reconnaissance.buildClasses(dbLearning, 350, 1);

			// Test pour une seule pièce
			/*PIECE_TYPE resultat =  reconnaissance.completeReconaissance_one("n_pion_face (13)");
			cout << "Ah ça, c'est un " << convert_pieceTypeToName(resultat) << endl;*/
			// Test pour une db complète
			vector<pair<DatabaseImageDescriptor, PIECE_TYPE>> results;
			//reconnaissance.completeReconnaissance_db(dbTest, results, 350, 1);
			reconnaissance.completeReconnaissance_dbPCA(dbTest, results, i,j);
			reconnaissance.analyseResults(results,i,j);
			cout << "i = " << i << " j = " << j << endl;
		}
	}
	
	waitKey(0);
 	return EXIT_SUCCESS;
}  
