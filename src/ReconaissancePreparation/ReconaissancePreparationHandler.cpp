#include "ReconaissancePreparationHandler.h"

void ReconnaissancePreparationHandler::buildCaracteristicVector(Mat image, vector<float>& caracteristicVector)
{
	Mat edges;
	ImageHandler::prepareImage_canny(image, edges);

	// TODO: impl�menter la normalisation du nombre de points dans le contour

	//TODO: impl�menter la construction du vecteur caract�ristique
	//caracteristicVector = 
}

void ReconnaissancePreparationHandler::learning(DatabaseHandler & database, PCA& pca, Mat& reducedLearnDB)
{
	vector<DatabaseImage>& images = database.getImages();
	Mat caracteristicVectors; // contients tout les vecteurs de la base d'aprentissage ou chaque colonne est un de ces vecteurs
	int c = 0;
	for (DatabaseImage i : images)
	{
		vector<float> caracteristicVector;
		buildCaracteristicVector(i.mat, caracteristicVector);
		// ajout� le vecteur a la matrice caracteristicVectors
		for (int r = 0; r < caracteristicVector.size; ++r) {
			caracteristicVectors.at<float>(r, c) = caracteristicVector[r];
		}
		++c;
	}

	//TODO impl�menter l'apprentissage des classes : ici c'est avec le pca, c'est pas vraiment de l'aprentissage mais bon..
	
	pca = PCA(caracteristicVectors, Mat(), CV_PCA_DATA_AS_COL);
	reducedLearnDB = pca.project(caracteristicVectors);

}
