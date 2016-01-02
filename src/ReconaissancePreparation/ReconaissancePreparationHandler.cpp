#include "ReconaissancePreparationHandler.h"

void ReconnaissancePreparationHandler::buildCaracteristicVector(Mat image, vector<float>& caracteristicVector)
{
	Mat edges;
	ImageHandler::prepareImage_canny(image, edges);
	vector<pair<int, int>> contour = ImageHandler::findContour(edges);
	// TODO: implémenter la normalisation du nombre de points dans le contour
	float gap = contour.size() / 500;
	vector<pair<int, int>> normalized_contour;
	//TODO: implémenter la construction du vecteur caractéristique
	for (int i = 0; i < 500; ++i) {
		normalized_contour.push_back(contour.at(round(i*gap)));
	}
	int x = 6; //x is the number of points take before and after actual point in lagrange interpolation
	tangent_descriptor descriptor(normalized_contour, x);

	caracteristicVector = descriptor.angle;

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
		// ajouté le vecteur a la matrice caracteristicVectors
		for (int r = 0; r < caracteristicVector.size; ++r) {
			caracteristicVectors.at<float>(r, c) = caracteristicVector[r];
		}
		++c;
	}

	//TODO implémenter l'apprentissage des classes : ici c'est avec le pca, c'est pas vraiment de l'aprentissage mais bon..
	pca = PCA(caracteristicVectors, Mat(), CV_PCA_DATA_AS_COL);
	reducedLearnDB = pca.project(caracteristicVectors);

}
