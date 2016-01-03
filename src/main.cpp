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
	DatabaseHandler dbLearning, dbTest, dbAll;
	DatabaseHandler::buildDatabase_allBlackFace(dbLearning, dbTest, dbAll);

	for (int i = 50; i < 600; i = i + 50) {
		for (int j = 1; j < 3; ++j) {
			// Construction des classes
			ReconnaissanceHandler reconnaissance;
			reconnaissance.buildClassesPCA(dbLearning, i, j);
			//reconnaissance.buildClasses(dbLearning, i, j);

			// Test pour une seule pièce
			/*PIECE_TYPE resultat =  reconnaissance.completeReconaissance_one("n_pion_face (13)");
			cout << "Ah ça, c'est un " << convert_pieceTypeToName(resultat) << endl;*/
			// Test pour une db complète
			vector<pair<DatabaseImageDescriptor, PIECE_TYPE>> results;
			//reconnaissance.completeReconnaissance_db(dbTest, results, i, j);
			reconnaissance.completeReconnaissance_dbPCA(dbTest, results, i, j);
			reconnaissance.analyseResults(results,i,j);
		}
	}
	
	waitKey(0);
 	return EXIT_SUCCESS;
}  
