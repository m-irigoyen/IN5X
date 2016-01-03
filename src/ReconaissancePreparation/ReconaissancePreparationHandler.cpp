#include "ReconaissancePreparationHandler.h"


void ReconnaissancePreparationHandler::buildCaracteristicVector(Mat image, vector<float>& caracteristicVector, int n, int x)
{
	Mat edges;
	ImageHandler::prepareImage_canny(image, edges);
	imshow("Image", image);
	waitKey(0);
	imshow("Edges", edges);
	waitKey(0);
	vector<pair<int, int>> contour;
	ImageHandler::findContour(edges, contour);
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

void ReconnaissancePreparationHandler::learningPCA(DatabaseHandler & database, PCA& pca, vector<vector<float>>& classes,int n,int x)
{
	// Nettoyage et préparation des classes
	classes.clear();
	vector<DatabaseImage>& images = database.getImages();
	Mat caracteristicVectors(n,images.size(), CV_32F); // contients tout les vecteurs de la base d'aprentissage ou chaque colonne est un de ces vecteurs
	int c = 0;
	for (DatabaseImage i : images)
	{
		vector<float> caracteristicVector;
		buildCaracteristicVector(i.mat, caracteristicVector,n,x);
		// ajouté le vecteur a la matrice caracteristicVectors
		for (int r = 0; r < caracteristicVector.size(); ++r) {
			caracteristicVectors.at<float>(r, c) = caracteristicVector[r];
		}
		++c;
	}

	
	pca = PCA(caracteristicVectors, Mat(), CV_PCA_DATA_AS_COL);
	Mat reducedLearnDB = pca.project(caracteristicVectors);

	vector<vector<vector<float>>> fullClasses;

	// Initialisation des classes
	for (int i = 0; i < 6; ++i)
	{
		fullClasses.push_back(vector<vector<float>>());
		classes.push_back(vector<float>());
	}


	for (int i = 0; i < images.size();++i)
	{
		vector<float> v;
		for (int j = 0; j < reducedLearnDB.rows; j++)
		{
			v.push_back(reducedLearnDB.at<float>(j, i));
		}
		fullClasses.at((int)(images.at(i)).descriptor.type).push_back(v);
	}

	// Donc là, fullClasses contient pour chaque classe TOUS les vecteurs caractéristiques de cette classe. Maintenant, on en fait la moyenne
	for (int i = 0; i < 6; ++i)
	{
		classes.at(i) = ReconnaissancePreparationHandler::meanVectorClass(fullClasses.at(i));
	}

}

vector<float> ReconnaissancePreparationHandler::meanVectorClass(vector<vector<float>> vectorsClass) {
	vector<float> mean;
	for (int i = 0; i < vectorsClass.size(); ++i) {
		vector<float> caracPiece = vectorsClass.at(i);
		if (i == 0) {
			mean = caracPiece;
		}
		else if (i<vectorsClass.size()-1){
			for (int j = 0; j < caracPiece.size(); ++j) {
				mean.at(j) += caracPiece.at(j);
			}
		}
		else {
			for (int j = 0; j < caracPiece.size(); ++j) {
				mean.at(j) += caracPiece.at(j);
				mean.at(j) = mean.at(j) / vectorsClass.size();
			}
		}
	}
	return mean;
}

void ReconnaissancePreparationHandler::learning(DatabaseHandler & database, vector<vector<float>>& classes, int n, int x)
{
	// Nettoyage et préparation des classes
	classes.clear();

	vector<DatabaseImage>& images = database.getImages();
	
	vector<vector<vector<float>>> fullClasses;

	// Initialisation des classes
	for (int i = 0; i < 6; ++i)
	{
		fullClasses.push_back(vector<vector<float>>());
		classes.push_back(vector<float>());
	}
		

	for (DatabaseImage i : images)
	{
		vector<float> caracteristicVector;
		buildCaracteristicVector(i.mat, caracteristicVector, n , x);
		fullClasses.at((int)i.descriptor.type).push_back(caracteristicVector);
	}

	// Donc là, fullClasses contient pour chaque classe TOUS les vecteurs caractéristiques de cette classe. Maintenant, on en fait la moyenne
	for (int i = 0; i < 6; ++i)
	{
		classes.at(i) = ReconnaissancePreparationHandler::meanVectorClass(fullClasses.at(i));
	}
}
