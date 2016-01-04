#ifndef DEF_FILEPATHS
#define DEF_FILEPATHS

/* Les chemins vers les différents dossiers/fichiers qu'on utilise
SUIVEZ LA STRUCTURE RECURSIVE! 
	- Déjà, ça vous évite des fautes de frappe (le genre qui font que le programme plantera chez quelqu'un d'autre mais pas chez vous)
	- Quand on rendra le programme final, ça sera beaucoup plus simple de juste changer le "#define DEBUG" ci-dessous en "RELEASE" plutôt que de changer TOUT nos chemins dans TOUT le programme pour que ça marche quand même.
*/

#include <string>

using namespace std;

#define RELEASE

class PATHS
{
public : 
	static const string PROJECT;	// Chemin du dossier global
	static const string RES;		// Chemin vers le dossier res
	static const string DATABASE;	// Chemin vers la base de données de photos avec quadrillage
	static const string DATABASE2;	// Chemin vers la base de données de photos sans quadrillage
};



#endif // !DEF_FILEPATHS
