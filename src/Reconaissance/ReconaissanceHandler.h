#ifndef DEF_RECONNAISSANCEHANDLER
#define DEF_RECONNAISSANCEHANDLER

#include <string>
#include <vector>

using namespace std;

class ReconnaissanceHandler
{

public:
	enum PIECE_TYPE
	{
		PION = 0,
		TOUR,
		FOU,
		CAVALIER,
		REINE,
		ROI
	};

	// Pour le vecteur caract�ristique et les classes donn�es, retourne les probabilit�s d'appartenance � chaque pi�ce
	vector<float> recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes);
};

#endif 