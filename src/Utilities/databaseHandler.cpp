#include "databaseHandler.hpp"

DatabaseHandler::DatabaseHandler()
{
	this->computeNumberOfImages();
}

void DatabaseHandler::buildDatabase(bool isLearningDatabase, vector<PIECE_TYPE> types, vector<PIECE_ANGLE> angles, vector<PIECE_COLOR> colors)
{
	this->images.clear();

	for (PIECE_TYPE type : types)
	{
		for (PIECE_ANGLE angle : angles)
		{
			for (PIECE_COLOR color : colors)
			{
				this->getAllImagesFromType(isLearningDatabase, type, angle, color, this->images);
			}
		}
	}
}

void DatabaseHandler::buildDatabase(bool isLearningDatabase, PIECE_TYPE type, PIECE_ANGLE angle, PIECE_COLOR color)
{
	vector<PIECE_TYPE> types;
	types.push_back(type);

	vector<PIECE_ANGLE> angles;
	angles.push_back(angle);

	vector<PIECE_COLOR> colors;
	colors.push_back(color);

	this->buildDatabase(isLearningDatabase, types, angles, colors);
}

vector<DatabaseImage>& DatabaseHandler::getImages()
{
	return this->images;
}

void DatabaseHandler::computeNumberOfImages()
{
	// ET BIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIM L'insertion du swag

	//roi
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, FACE), NOIR), 10)); 
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(ROI, COTE), NOIR), 0));

	//reine
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, FACE), NOIR), 12));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(REINE, COTE), NOIR), 0));

	//cavalier
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, FACE), NOIR), 14));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(CAVALIER, COTE), NOIR), 10));

	//fou
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, FACE), NOIR), 10));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(FOU, COTE), NOIR), 10));

	//pion
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, FACE), NOIR), 13));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(PION, COTE), NOIR), 0));

	//tour
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, FACE), NOIR), 11));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, HAUT), NOIR), 0));
	this->numberOfImages.insert(pair<pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>, int>(pair<pair<PIECE_TYPE, PIECE_ANGLE>, PIECE_COLOR>(pair<PIECE_TYPE, PIECE_ANGLE>(TOUR, COTE), NOIR), 11));
}

void DatabaseHandler::getAllImagesFromType(bool learning, DatabaseImageDescriptor d, vector<DatabaseImage>& images)
{
	this->getAllImagesFromType(learning, d.type, d.angle, d.color, images);
}

void DatabaseHandler::getAllImagesFromType(bool learning, PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, vector<DatabaseImage>& images)
{

	int start, finish;
	//TODO: finish that
	if (learning)
	{
		start = 1;
		finish = static_cast<int>(this->getNumberOfImagesFromType(t, a, c) / 100.0f * DATABASE_LEARNINGRATIO);
	}
	else
	{
		start = static_cast<int>(this->getNumberOfImagesFromType(t, a, c) / 100.0f * DATABASE_LEARNINGRATIO) + 1;
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

	switch (t)
	{
	case PIECE_TYPE::CAVALIER :
		name += "cavalier";
		break;
	case PIECE_TYPE::FOU:
		name += "fou";
		break;
	case PIECE_TYPE::PION :
		name += "pion";
		break;
	case PIECE_TYPE::REINE:
		name += "reine";
		break;
	case PIECE_TYPE::ROI:
		name += "roi";
		break;
	case PIECE_TYPE::TOUR:
		name += "tour";
		break;
	}
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
	}
	name += " ";

	return name;
}

string DatabaseHandler::getNumber(int n)
{
	string s = "(" + to_string(n) + ")";
	return s;
}

string DatabaseHandler::getExtension()
{
	return string(".jpg");
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
		ImageHandler::loadImage(this->buildPath(d, number), image);
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

string DatabaseHandler::buildPath(DatabaseImageDescriptor d, int number)
{
	if (number <= this->getNumberOfImagesFromType(d))
	{
		string path = PATHS::DATABASE2;
		path += this->getNameFromType(d);
		path += this->getNumber(number);
		path += this->getExtension();
		return path;
	}
	else
		cout << "ERREUR : numéro d'image incorrect" << endl;
}