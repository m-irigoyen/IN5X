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

	// Pour le vecteur caractéristique et les classes données, retourne les probabilités d'appartenance à chaque pièce
	vector<float> recognise(vector<float>& caracteristicVector, vector<vector<float>>& classes);
};

#endif 