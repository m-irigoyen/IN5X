#ifndef DEF_DATABASEHANDLER
#define DEF_DATABASEHANDLER

#include "Utilities/enums.h"

#include <vector>
#include <map>


#define DATABASE_LEARNINGRATIO 60.0f

using namespace std;

/*
Fonctions d'aide qui simplifient l'utilisation des images de la base de données : chargement d'images, prendre des images random parmi certaines, etc
*/
class DatabaseHandler
{
public:
	DatabaseHandler();

	// Construit une base de donnée contenant les types et angles passés en paramètre
	void buildDatabase(bool isLearningDatabase, vector<PIECE_TYPE> types, vector<PIECE_ANGLE> angles, vector<PIECE_COLOR> colors);

	vector<DatabaseImage>& getImages();

private:
	vector<DatabaseImage> images;

	// map qui stocke pour chaque type de pièce le nombre d'images qu'on en a
	//map< pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR> , int>
	// Nombre d'images
	int n_roi_face;
	int n_roi_dessus;
	int n_roi_cote;
	int n_reine_face;
	int n_reine_dessus;
	int n_reine_cote;
	int n_fou_face;
	int n_fou_dessus;
	int n_fou_cote;
	int n_cavalier_face;
	int n_cavalier_dessus;
	int n_cavalier_cote;
	int n_tour_face;
	int n_tour_dessus;
	int n_tour_cote;
	int n_pion_face;
	int n_pion_dessus;
	int n_pion_cote;

	// Fonctions
	void computeNumberOfImages();
	void getAllImagesFromType(bool learning, DatabaseImageDescriptor d, vector<DatabaseImage>& images);
	void getAllImagesFromType(bool learning, PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, vector<DatabaseImage>& images);
	string getNameFromType(DatabaseImageDescriptor d);
	string getNameFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c);
	string getNumber(int n);
	string getExtension();
	int getNumberOfImagesFromType(DatabaseImageDescriptor d);
	int getNumberOfImagesFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c);
};

#endif // !DEF_GAUSSIANBLURHANDLER
