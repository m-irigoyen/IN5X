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

	ReconnaissanceHandler reconnaissance;
	reconnaissance.buildClassesPCA(dbLearning);


	vector<pair<DatabaseImageDescriptor, PIECE_TYPE>> results;
	reconnaissance.completeReconnaissance_dbPCA(dbTest, results);
	reconnaissance.analyseResults(results);
	
	waitKey(0);
 	return EXIT_SUCCESS;
}  
