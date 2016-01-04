#ifndef DEF_DATABASEHANDLER
#define DEF_DATABASEHANDLER

#include "../Utilities/enums.h"

#include <vector>
#include <map>

#include "filePaths.hpp"
#include "Helper.h"
#include "../ReconaissancePreparation/ImageHandler.h"

#define DATABASE_LEARNINGRATIO 60.0f

using namespace std;

/*
Fonctions d'aide qui simplifient l'utilisation des images de la base de données : chargement d'images, prendre des images random parmi certaines, etc
*/
class DatabaseHandler
{
public:
	DatabaseHandler();

	enum DATABASE_TYPE
	{
		TEST,
		LEARNING,
		ALL
	};

	// Construit une base de donnée
	static void buildDatabase_allBlackFace(DatabaseHandler& learning, DatabaseHandler& test, DatabaseHandler& all);
	static void buildDatabase_allBlack(DatabaseHandler& learning, DatabaseHandler& test, DatabaseHandler& all);
	static void buildDatabase_allWhite(DatabaseHandler& learning, DatabaseHandler& test, DatabaseHandler& all);
	static void buildDatabase_all(DatabaseHandler& learning, DatabaseHandler& test, DatabaseHandler& all);

	vector<DatabaseImage>& getImages();

private:
	vector<DatabaseImage> images;

	void buildDatabase(DATABASE_TYPE type, vector<PIECE_TYPE> types, vector<PIECE_ANGLE> angles, vector<PIECE_COLOR> colors);
	void buildDatabase(DATABASE_TYPE dbType, vector<PIECE_TYPE> types, PIECE_ANGLE angle, PIECE_COLOR color);
	void buildDatabase(DATABASE_TYPE dbType, PIECE_TYPE type, PIECE_ANGLE angle, PIECE_COLOR color);

	// map qui stocke pour chaque type de pièce le nombre d'images qu'on en a
	// pair<pair<type,angle>, color>, nombre>
	map< pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int> numberOfImages;
	// Nombre d'images

	// Fonctions
	void computeNumberOfImages();
	void getAllImagesFromType(DATABASE_TYPE type, DatabaseImageDescriptor d, vector<DatabaseImage>& images);
	void getAllImagesFromType(DATABASE_TYPE type, PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, vector<DatabaseImage>& images);
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
