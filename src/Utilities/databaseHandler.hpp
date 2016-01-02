#ifndef DEF_DATABASEHANDLER
#define DEF_DATABASEHANDLER

#include "Utilities/enums.h"

#include <vector>
#include <map>

#include "filePaths.hpp"
#include "Helper.h"
#include "ReconaissancePreparation/ImageHandler.h"

#define DATABASE_LEARNINGRATIO 60.0f

using namespace std;

/*
Fonctions d'aide qui simplifient l'utilisation des images de la base de donn�es : chargement d'images, prendre des images random parmi certaines, etc
*/
class DatabaseHandler
{
public:
	DatabaseHandler();

	// Construit une base de donn�e contenant les types et angles pass�s en param�tre
	
	void buildDatabase(bool isLearningDatabase, vector<PIECE_TYPE> types, PIECE_ANGLE angle, PIECE_COLOR color);
	void buildDatabase(bool isLearningDatabase, PIECE_TYPE type, PIECE_ANGLE angle, PIECE_COLOR color);

	vector<DatabaseImage>& getImages();

private:
	vector<DatabaseImage> images;

	// map qui stocke pour chaque type de pi�ce le nombre d'images qu'on en a
	// pair<pair<type,angle>, color>, nombre>
	map< pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int> numberOfImages;
	// Nombre d'images

	// Fonctions
	void computeNumberOfImages();
	void getAllImagesFromType(bool learning, DatabaseImageDescriptor d, vector<DatabaseImage>& images);
	void getAllImagesFromType(bool learning, PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, vector<DatabaseImage>& images);
	string getNameFromType(DatabaseImageDescriptor d);
	string getNameFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c);
	string getNumber(int n);
	int getNumberOfImagesFromType(DatabaseImageDescriptor d);
	int getNumberOfImagesFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c);
	void loadImageFromType(DatabaseImageDescriptor d, int number, Mat& image);
	void loadImageFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, int number, Mat& image);
	string buildName(DatabaseImageDescriptor d, int number);

	void buildDatabase(bool isLearningDatabase, vector<PIECE_TYPE> types, vector<PIECE_ANGLE> angles, vector<PIECE_COLOR> colors);
};

#endif // !DEF_GAUSSIANBLURHANDLER
