#include "transformPiece.hpp"
#define PI 3.14159265

TransformPiece::TransformPiece(Mat& i){
	img = i;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == 255) {
				piece.push_back(pair<int, int>(i, j));
			}
		}
	}
	box = Box(piece);
}
//met à jour l'image
void TransformPiece::MAJimg() {
	for (int i = 0; i < piece.size(); ++i) {
		img.at<uchar>(piece.at(i).first, piece.at(i).second) = 255;
	}
}

//rote les points de la pièce d'un angle donné
vector<pair<int,int>> TransformPiece::rotation(float angle, vector <pair<int, int>> result) {
	result = piece;
	angle = angle * PI / 180;
	pair<int, int> center = pair<int, int>((box.points_box.at(0).second + box.points_box.at(2).second) / 2, (box.points_box.at(0).first + box.points_box.at(2).first) / 2);
	for (int j = 0; j < piece.size(); ++j) {
		result.at(j).first = ((piece.at(j).first - center.first) * cos(angle) + (piece.at(j).second - center.second) * sin(angle)) + center.first;
		result.at(j).second =  (-(piece.at(j).first - center.first)* sin(angle) + (piece.at(j).second - center.second)* cos(angle)) + center.second;
	}

	return result;
}

//trouve la bonne direction de la pièce
void TransformPiece::findDirection() {
	vector<pair<int, int>> pieceTmp, finalPiece;
	finalPiece = piece;
	Box box_final = box;
	//fait roter la pièce entre 0 et 360° avec un pas d'1° pour trouver une potentiel boite englobante ayant une aire plus petite
	for (int i = 0; i < 360; ++i) {
		pieceTmp = rotation(i, pieceTmp);
		Box boxtmp = Box(pieceTmp);
		if (box_final.aire > boxtmp.aire) {
			box_final.points_box = boxtmp.points_box;
			box_final.aire = boxtmp.aire;
			finalPiece = pieceTmp;
		}
	}
	//garde la pièce ayant la boite englobante ayant une aire la plus petite
 	box.points_box = box_final.points_box;
	box.aire = box_final.aire;
	piece = finalPiece;
	img = img * 0;
	rectangle(img, Point(box.points_box.at(0).first, box.points_box.at(0).second), Point(box.points_box.at(2).first, box.points_box.at(2).second), Scalar(255, 255, 255));
	MAJimg();
	//si la boite englobante est plus large que haute, on rote la pièce de 90°
	if (box.points_box.at(2).first - box.points_box.at(0).first > box.points_box.at(1).second - box.points_box.at(0).second) {
		piece = rotation(90, piece);
		box = Box(piece);
	}
	img = img * 0;
	MAJimg();
	//compte l'écart entre le premier et le dernier pixel blancs en haut et en bas de la pièce
	//on prend en compte la 4ème ligne en partant du haut et la 4ème en partant du bas, pour éviter une pièce légérement de travers qui commencerait avec une ligne de un pixels
	int first_up = -1, first_down = -1, last_up, last_down;
	for (int i = box.points_box.at(0).first; i <= box.points_box.at(2).first; ++i) {
		if (img.at<uchar>(box.points_box.at(0).second+4, i) == 255) {
			if (first_up == -1) {
				first_up = i;
			}
			last_up = i;
		}
		if (img.at<uchar>(box.points_box.at(2).second-4, i) == 255) {
			if (first_down == -1) {
				first_down = i;
			}
			last_down = i;
		}
	}
		
	//si la pièce est plus large en haut qu'en bas, on rote la pièce de 180°
   	if (last_up-first_up > last_down-first_down) {
		piece = rotation(180,piece);
		box = Box(piece);
	}

	img = img * 0;
	MAJimg();
	
}

//trouve le chemin du contour
void TransformPiece::findPathcontour(vector<pair<int, int>>& result) {
	result.clear();
	bool test = true;
 	int i = img.rows - 1;

	int x = box.points_box.at(0).first;
	//trouve le point zéro, premier point en bas à gauche
	while (test) {
		if (img.at<uchar>(i, x) == 255) {
			result.push_back(pair<float, float>(i, x));
			test = false;
		}
		--i;
		if (i == -1) {
			i = img.rows - 1;
			x++;
		}
	}
	int j = 0;
	bool testclose = true;

	//testclose devient vrai lorsque le point zéro et dans les voisins
	while (testclose) {
		pair<int, int> p = result.at(j);
		bool test_neighboor = true;
		int z = 1;
		//test_neighboor devient vrai losqu'un voisin a été ajouté
		while (test_neighboor) {
			vector<pair<int, int>> neighboors = vector<pair<int, int>>();
			//trouve les voisins blancs
			for (int x = p.second - z; x <= p.second + z; ++x) {
				for (int y = p.first - z; y <= p.first + z; ++y) {
					if (x != p.second || y != p.first) {
						if (img.at<uchar>(y, x) == 255) {
							neighboors.push_back(pair<int, int>(y, x));
						}
					}
				}
			}
			//gère le premier voisins
			if (j == 0) {
				for (int x = 0; x < neighboors.size(); ++x) {
					if (neighboors.at(x).first + 1 == p.first) {
						result.push_back(neighboors.at(x));
						test_neighboor = false;
					}
				}
			}
			else {
				for (int x = 0; x < neighboors.size(); ++x) {
					if (j > 50 && std::find(neighboors.begin(), neighboors.end(), result.at(0)) != neighboors.end()) {
						test_neighboor = false;
						testclose = false;
					}
					//supprime le voisin actuel si il est déjà dans le chemin du contour
					if (std::find(result.begin(), result.end(), neighboors.at(x)) != result.end()) {
						neighboors.erase(neighboors.begin() + x);
						--x;
					}
				}
				//rajoute le vosin s'il n'y en a qu'un
				if (neighboors.size() == 1) {
					result.push_back(neighboors.at(0));
					test_neighboor = false;
				}
				//ajoute un voisin connexe avec le point actuel
				else if (neighboors.size()>1) {
					//il met la priorité sur les 4-connexes
					for (int x = 0; x < neighboors.size(); ++x) {
						if ((p.first == neighboors.at(x).first || p.second == neighboors.at(x).second) && test_neighboor == false) {
							result.push_back(neighboors.at(x));
							test_neighboor = false;
						}
					}
					//ajoute le 8-connexe le plus proche s'il n'a pas de voisin 4-connexe
					if (test_neighboor == true) {
						float dist_mini = 40000, dist;
						int index_dist_mini;
						for (int x = 0; x < neighboors.size(); ++x) {
							dist = sqrt(pow(p.first - neighboors.at(x).first, 2) + pow(p.second - neighboors.at(x).second, 2));
							if (dist < dist_mini) {
								index_dist_mini = x;
								dist_mini = dist;
							}
						}
						result.push_back(neighboors.at(index_dist_mini));
						test_neighboor = false;

					}
				}
				//augmente le cercle de voisins s'il n'en trouve pas
				else {
					++z;
				}
			}
		}
		++j;
	}
	Mat img2 = img * 0;
	for (int i = 0; i < result.size(); ++i) {
		img2.at<uchar>(result.at(i).first, result.at(i).second) = 255;
	}
}