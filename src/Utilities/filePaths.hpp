#ifndef DEF_FILEPATHS
#define DEF_FILEPATHS

/* Les chemins vers les diff�rents dossiers/fichiers qu'on utilise
SUIVEZ LA STRUCTURE RECURSIVE! 
	- D�j�, �a vous �vite des fautes de frappe (le genre qui font que le programme plantera chez quelqu'un d'autre mais pas chez vous)
	- Quand on rendra le programme final, �a sera beaucoup plus simple de juste changer le "#define DEBUG" ci-dessous en "RELEASE" plut�t que de changer TOUT nos chemins dans TOUT le programme pour que �a marche quand m�me.
*/

#include <string>

using namespace std;

#define RELEASE

class PATHS
{
public : 
	static const string PROJECT;	// Chemin du dossier global
	static const string RES;		// Chemin vers le dossier res
	static const string DATABASE;	// Chemin vers la base de donn�es de photos avec quadrillage
	static const string DATABASE2;	// Chemin vers la base de donn�es de photos sans quadrillage
};



#endif // !DEF_FILEPATHS
