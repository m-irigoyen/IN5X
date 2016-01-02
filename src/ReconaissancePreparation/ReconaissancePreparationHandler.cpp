#include "ReconaissancePreparationHandler.h"


void ReconnaissancePreparationHandler::prepareImage_method1(string imageName, Mat & output)
{
	Mat src, src_prepared;
	ImageHandler::loadImage(imageName, src);
	ImageHandler::prepareImage_canny(src, src_prepared);

}

void ReconnaissancePreparationHandler::buildCaracteristicVector(Mat image, vector<float>& caracteristicVector, int n, int x)
{
	Mat edges;
	ImageHandler::prepareImage_canny(image, edges);
	vector<pair<int, int>> contour = ImageHandler::findContour(edges);
	float gap = contour.size() / n;
	if (gap < 1) {
		cout << "ReconnaissancePreparationHandler::buildCaracteristicVector : Erreur! La pièce est trop petite" << std::endl;
	}
	else {
		vector<pair<int, int>> normalized_contour;
		for (int i = 0; i < n; ++i) {
			normalized_contour.push_back(contour.at(round(i*gap)));
		}
		tangent_descriptor descriptor(normalized_contour, x);

		caracteristicVector = descriptor.angle;
	}
}

void ReconnaissancePreparationHandler::learning(DatabaseHandler & database, PCA& pca, Mat& reducedLearnDB)
{
	vector<DatabaseImage>& images = database.getImages();
	Mat caracteristicVectors; // contients tout les vecteurs de la base d'aprentissage ou chaque colonne est un de ces vecteurs
	int c = 0;
	for (DatabaseImage i : images)
	{
		//TODO: mais comment tu sais quel vecteur est quoi là? Dans la base de données, ya genre N images de pions, M images de Rois, etc. Comment tu tries ça là?
		vector<float> caracteristicVector;
		buildCaracteristicVector(i.mat, caracteristicVector);
		// ajouté le vecteur a la matrice caracteristicVectors
		for (int r = 0; r < caracteristicVector.size(); ++r) {
			caracteristicVectors.at<float>(r, c) = caracteristicVector[r];
		}
		++c;
	}

	//TODO implémenter l'apprentissage des classes : ici c'est avec le pca, c'est pas vraiment de l'aprentissage mais bon..
	
	pca = PCA(caracteristicVectors, Mat(), CV_PCA_DATA_AS_COL);
	reducedLearnDB = pca.project(caracteristicVectors);

}

void ReconnaissancePreparationHandler::learning(DatabaseHandler & database, vector<vector<float>>& classes)
{
	vector<DatabaseImage>& images = database.getImages();
	
	vector<vector<vector<float>>> fullClasses;

	// Initialisation des classes
	for (int i = 0; i < 6; ++i)
		fullClasses.push_back(vector<vector<float>>());

	for (DatabaseImage i : images)
	{
		vector<float> caracteristicVector;
		buildCaracteristicVector(i.mat, caracteristicVector);
		fullClasses.at((int)i.descriptor.type).push_back(caracteristicVector);
	}

	// Donc là, fullClasses contient pour chaque classe TOUS les vecteurs caractéristiques de cette classe. Maintenant, on en fait la moyenne
	//TODO: faire la moyenne
}
