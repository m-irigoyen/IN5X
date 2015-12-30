#include "databaseHandler.hpp"

DatabaseHandler::DatabaseHandler()
{
}

void DatabaseHandler::buildDatabase(bool isLearningDatabase, vector<PIECE_TYPE> types, vector<PIECE_ANGLE> angles, vector<PIECE_COLOR> colors)
{
	this->images.clear();

	for (PIECE_TYPE type : types)
	{
		for (PIECE_ANGLE angle : angles)
		{
			//TODO: fill database
		}
	}
}

vector<DatabaseImage>& DatabaseHandler::getImages()
{
	// TODO: insérer une instruction return ici
	return this->images;
}

void DatabaseHandler::computeNumberOfImages()
{
	this->n_roi_face = 10;
	this->n_roi_dessus = 0;
	this->n_roi_cote = 0;

	this->n_reine_face = 12;
	this->n_reine_dessus = 0;
	this->n_reine_cote = 0;

	this->n_fou_face = 10;
	this->n_fou_dessus = 0;
	this->n_fou_cote = 10;

	this->n_cavalier_face = 14;
	this->n_cavalier_dessus = 0;
	this->n_cavalier_cote = 10;

	this->n_tour_face = 11;
	this->n_tour_dessus = 0;
	this->n_tour_cote = 11;

	this->n_pion_face = 13;
	this->n_pion_dessus = 0;
	this->n_pion_cote = 0;
}

void DatabaseHandler::getAllImagesFromType(bool learning, DatabaseImageDescriptor d, vector<DatabaseImage>& images)
{
	this->getAllImagesFromType(learning, d.type, d.angle, d.color, images);
}

void DatabaseHandler::getAllImagesFromType(bool learning, PIECE_TYPE t, PIECE_ANGLE a, PIECE_COLOR c, vector<DatabaseImage>& images)
{
	if (learning)
	{
		//for (int i = 0; i < )
	}
	else
	{

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
		name += "cote";
		break;
	}

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
	
	return 0;
}