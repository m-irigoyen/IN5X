#ifndef DEF_DATABASEHANDLER
#define DEF_DATABASEHANDLER

#include "Utilities/enums.h"

#include <vector>
using namespace std;

/*
Fonctions d'aide qui simplifient l'utilisation des images de la base de données : chargement d'images, prendre des images random parmi certaines, etc
*/
class DatabaseHandler
{
public:
	DatabaseHandler();

	void buildDatabase(bool isLearningDatabase, int pieceType, bool includeFace, bool includeSide, bool includeTop);

	vector<DatabaseImage>& getImages();

private:
	vector<DatabaseImage> images;
};

#endif // !DEF_GAUSSIANBLURHANDLER
