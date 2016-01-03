#include "databaseHandler.hpp"

DatabaseHandler::DatabaseHandler()
{
	this->computeNumberOfImages();
}

void DatabaseHandler::buildDatabase(DATABASE_TYPE type, vector<PIECE_TYPE> types, vector<PIECE_ANGLE> angles, vector<PIECE_COLOR> colors)
{
	this->images.clear();

	for (int i = 0; i < types.size(); ++i)
	{
		for (int j = 0; j < angles.size(); ++j)
		{
			for (int k = 0; k < colors.size(); ++k)
			{
				this->getAllImagesFromType(type, types.at(i), angles.at(j), colors.at(k), this->images);
			}
		}
	}
}

void DatabaseHandler::buildDatabase(DATABASE_TYPE dbType, vector<PIECE_TYPE> types, PIECE_ANGLE angle, PIECE_COLOR color)
{
	vector<PIECE_ANGLE> angles;
	angles.push_back(angle);
	vector<PIECE_COLOR> colors;
	colors.push_back(color);

	this->buildDatabase(dbType, types, angles, colors);
}

void DatabaseHandler::buildDatabase(DATABASE_TYPE dbType, PIECE_TYPE type, PIECE_ANGLE angle, PIECE_COLOR color)
{
	vector<PIECE_TYPE> types;
	types.push_back(type);

	vector<PIECE_ANGLE> angles;
	angles.push_back(angle);

	vector<PIECE_COLOR> colors;
	colors.push_back(color);

	this->buildDatabase(dbType, types, angles, colors);
}

void DatabaseHandler::buildDatabase_allBlackFace(DatabaseHandler& learning, DatabaseHandler& test, DatabaseHandler& all)
{
	vector<PIECE_TYPE> types;
	types.push_back(PIECE_TYPE::CAVALIER);
	types.push_back(PIECE_TYPE::FOU);
	types.push_back(PIECE_TYPE::PION);
	types.push_back(PIECE_TYPE::REINE);
	types.push_back(PIECE_TYPE::ROI);
	types.push_back(PIECE_TYPE::TOUR);

	vector<PIECE_ANGLE> angles;
	angles.push_back(FACE);

	vector<PIECE_COLOR> colors;
	colors.push_back(NOIR);

	learning.buildDatabase(LEARNING, types, angles, colors);
	test.buildDatabase(TEST, types, angles, colors);
	all.buildDatabase(ALL, types, angles, colors);
}

void DatabaseHandler::buildDatabase_allWhite(DatabaseHandler& learning, DatabaseHandler& test, DatabaseHandler& all)
{
	vector<PIECE_TYPE> types;
	types.push_back(PIECE_TYPE::CAVALIER);
	types.push_back(PIECE_TYPE::FOU);
	types.push_back(PIECE_TYPE::PION);
	types.push_back(PIECE_TYPE::REINE);
	types.push_back(PIECE_TYPE::ROI);
	types.push_back(PIECE_TYPE::TOUR);

	vector<PIECE_COLOR> colors;
	colors.push_back(BLANC);

	vector<PIECE_ANGLE> angles;
	angles.push_back(PIECE_ANGLE::COTE);
	angles.push_back(PIECE_ANGLE::FACE);
	angles.push_back(PIECE_ANGLE::HAUT);
	angles.push_back(PIECE_ANGLE::DOS);

	learning.buildDatabase(LEARNING, types, angles, colors);
	test.buildDatabase(TEST, types, angles, colors);
	all.buildDatabase(ALL, types, angles, colors);
}

void DatabaseHandler::buildDatabase_all(DatabaseHandler& learning, DatabaseHandler& test, DatabaseHandler& all)
{
	vector<PIECE_TYPE> types;
	types.push_back(PIECE_TYPE::CAVALIER);
	types.push_back(PIECE_TYPE::FOU);
	types.push_back(PIECE_TYPE::PION);
	types.push_back(PIECE_TYPE::REINE);
	types.push_back(PIECE_TYPE::ROI);
	types.push_back(PIECE_TYPE::TOUR);

	vector<PIECE_COLOR> colors;
	colors.push_back(BLANC);
	colors.push_back(NOIR);

	vector<PIECE_ANGLE> angles;
	angles.push_back(PIECE_ANGLE::COTE);
	angles.push_back(PIECE_ANGLE::FACE);
	angles.push_back(PIECE_ANGLE::HAUT);
	angles.push_back(PIECE_ANGLE::DOS);

	learning.buildDatabase(LEARNING, types, angles, colors);
	test.buildDatabase(TEST, types, angles, colors);
	all.buildDatabase(ALL, types, angles, colors);
}

vector<DatabaseImage>& DatabaseHandler::getImages()
{
	return this->images;
}

void DatabaseHandler::computeNumberOfImages()
{
	// ET BIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIM L'insertion du swag

	//roi
	//TODO : le 8 est temporaire, remettre à 10 après
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, FACE), NOIR), 10)); 
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, COTE), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, DOS), NOIR), 0));

	//reine
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, FACE), NOIR), 12));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, COTE), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, DOS), NOIR), 0));

	//cavalier
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, FACE), NOIR), 14));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, COTE), NOIR), 10));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, DOS), NOIR), 0));

	//fou
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, FACE), NOIR), 10));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, COTE), NOIR), 10));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, DOS), NOIR), 0));

	//pion
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, FACE), NOIR), 13));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, COTE), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, DOS), NOIR), 0));

	//tour
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, FACE), NOIR), 11));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, COTE), NOIR), 11));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, DOS), NOIR), 0));


			// BLANCHES
	//roi
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, FACE), BLANC), 10));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, HAUT), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, COTE), BLANC), 6));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, DOS), BLANC), 0));

	//reine
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, FACE), BLANC), 8));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, HAUT), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, COTE), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, DOS), BLANC), 0));

	//cavalier
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, FACE), BLANC), 8));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, HAUT), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, COTE), BLANC), 7));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, DOS), BLANC), 7));

	//fou
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, FACE), BLANC), 9));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, HAUT), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, COTE), BLANC), 6));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, DOS), BLANC), 7));

	//pion
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, FACE), BLANC), 7));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, HAUT), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, COTE), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, DOS), BLANC), 0));

	//tour
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, FACE), BLANC), 8));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, HAUT), BLANC), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, COTE), BLANC), 7));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, DOS), BLANC), 0));
}

void DatabaseHandler::getAllImagesFromType(DATABASE_TYPE type, DatabaseImageDescriptor d, vector<DatabaseImage>& images)
{
	this->getAllImagesFromType(type, d.type, d.angle, d.color, images);
}

void DatabaseHandler::getAllImagesFromType(DATABASE_TYPE type, PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, vector<DatabaseImage>& images)
{

	int start, finish;
	if (type == DATABASE_TYPE::LEARNING)
	{
		start = 1;
		finish = static_cast<int>(this->getNumberOfImagesFromType(t, a, c) / 100.0f * DATABASE_LEARNINGRATIO);
	}
	else if (type == DATABASE_TYPE::TEST)
	{
		start = static_cast<int>(this->getNumberOfImagesFromType(t, a, c) / 100.0f * DATABASE_LEARNINGRATIO) + 1;
		finish = this->getNumberOfImagesFromType(t, a, c);
	}
	else
	{
		start = 1;
		finish = this->getNumberOfImagesFromType(t, a, c);
	}


	for (int i = start; i <= finish; ++i)
	{
		Mat img;
		this->loadImageFromType(t, a, c, i, img);
		if (!img.data)
		{
			cout << "WOWOWOWOWO CEYLAMERDE" << endl;
		}
		else
		{
			DatabaseImageDescriptor d;
			d.type = t;
			d.color = c;
			d.angle = a;
			d.number = i;

			DatabaseImage imgFinal;
			imgFinal.descriptor = d;
			imgFinal.mat = img;
			images.push_back(imgFinal);
		}
	}
}

string DatabaseHandler::getNameFromType(DatabaseImageDescriptor d)
{
	return this->getNameFromType(d.type, d.angle, d.color);
}

string DatabaseHandler::getNameFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c)
{
	string name;
	string separator = "_";

	switch (c)
	{
	case PIECE_COLOR::BLANC :
		name += "b";
		break;
	case PIECE_COLOR::NOIR:
		name += "n";
		break;
	}
	name += separator;

	name += convert_pieceTypeToName(t);
	name += separator;

	switch (a)
	{
	case PIECE_ANGLE::COTE :
		name += "cote";
		break;
	case PIECE_ANGLE::HAUT:
		name += "haut";
		break;
	case PIECE_ANGLE::FACE:
		name += "face";
		break;
	case PIECE_ANGLE::DOS:
		name += "dos";
		break;
	}
	name += " ";

	return name;
}

string DatabaseHandler::getNumber(int n)
{
	string s = "(" + to_string(n) + ")";
	return s;
}

int DatabaseHandler::getNumberOfImagesFromType(DatabaseImageDescriptor d)
{
	return this->getNumberOfImagesFromType(d.type, d.angle, d.color);
}

int DatabaseHandler::getNumberOfImagesFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c)
{
	// map< pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>
	//		pair<pair<type,angle>, color>, nombre>
	return this->numberOfImages.at(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(t, a), c));	// et BIM l'accesseur du swag
}

void DatabaseHandler::loadImageFromType(DatabaseImageDescriptor d, int number, Mat& image)
{
	if (number <= this->getNumberOfImagesFromType(d))
		ImageHandler::loadImage(this->buildName(d, number), image);
	else
		cout << "ERREUR : numéro d'image incorrect" << endl;
}

void DatabaseHandler::loadImageFromType(PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, int number, Mat & image)
{
	DatabaseImageDescriptor d;
	d.type = t;
	d.angle = a;
	d.color = c;
	this->loadImageFromType(d, number, image);
}

string DatabaseHandler::buildName(DatabaseImageDescriptor d, int number)
{
	if (number <= this->getNumberOfImagesFromType(d))
	{
		string name = this->getNameFromType(d);
		name += this->getNumber(number);
		return name;
	}
	else
		cout << "ERREUR : numéro d'image incorrect" << endl;
}