#include "filePaths.hpp"

// Chemin du projet global
#ifdef RELEASE
	 const string PATHS::PROJECT = "";
#endif
#ifdef DEBUG
	 const string PATHS::PROJECT = "../Project/";
#endif

 const string PATHS::RES = PROJECT + "res/";	// Chemin vers le dossier res
 const string PATHS::DATABASE = RES + "database/";	// Chemin vers la base de données de photos