#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cstdlib>
#include <cassert>
#include <fstream>

using namespace std;

class Sommet{

	public:
		int couleur;
		bool visite;
		vector<Arete> aretes;
		int distance;
		Sommet(int _couleur, int _distance): couleur(_couleur), distance(_distance) {
			visite = false;
		}

		void ajouterArete(Arete a){
			aretes.push_back(a);
		}
};

class Arete{

	public:
		Sommet sommet;
		int distance;
		char direction;
};


class Univers
{
	public:
	unsigned int N; 	// Nombre de ligne et nombre de colonnes
	unsigned int C; 	// Nombre de couleur
	vector<vector<Sommet>> matriceSommet;
	vector<vector<vector<Sommet>>> vectorDeMatriceSommet;
	// TODO : Complétez avec les attributs nécessaires pour représenter l'univers

public:
	Univers() {

	}

	~Univers() {

	}

	void plusCourtChemin(unsigned int x_depart, unsigned int y_depart, unsigned int couleur_depart, unsigned int x_destination, unsigned int y_destination) {
		std::cerr << "TODO : calculer le plus court chemin depuis (" << x_depart << ", " << y_depart << ") avec la couleur " << couleur_depart << " vers (" << x_destination << ", " << y_destination << ")" << std::endl;
		// TODO...
	}

	void afficher(){
		for(int i = 0; i < C; i++){
			for(unsigned int y = 0; y<N; y++) {
				for(unsigned int x = 0; x<N; x++) {
					cout << vectorDeMatriceSommet[i][y][x].couleur;
				}
				cout << endl;
			}
				cout << endl;
				cout << endl;
		}
	}

	friend std::istream& operator >> (std::istream& is, Univers& recette);
};


std::istream& operator >> (std::istream& is, Univers& univers) {

	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs

	assert(univers.N > 0);
	assert(univers.C > 0);
	

	for(unsigned int y = 0; y<univers.N; y++) {
		vector<Sommet> vs;
		for(unsigned int x = 0; x<univers.N; x++) {
			unsigned int couleur;
			is >> couleur;
			//std::cerr << "TODO : considérer la cellule (" << x << ", " << y << ") est de couleur " << couleur << std::endl;
			Sommet sommet(couleur, 100000);
			vs.push_back(sommet);
		}
		univers.matriceSommet.push_back(vs);
	}

	for(int i = 0; i < univers.C; i++){
		univers.vectorDeMatriceSommet.push_back(univers.matriceSommet);
	}
	univers.matriceSommet.clear();
	return is;
}


int main(int argc, char const *argv[])
{
	if(argc != 7) {
		std::cerr << "Utilisation : " << argv[0] << " x_depart y_depart couleur_depart x_destination y_destination" << std::endl;
		return -1;
	}

	std::ifstream entree = std::ifstream(argv[1]);

	Univers univers;
	entree >> univers;

	unsigned int x_depart = atoi(argv[2]);
	unsigned int y_depart = atoi(argv[3]);
	unsigned int couleur_depart = atoi(argv[4]);
	unsigned int x_destination = atoi(argv[5]);
	unsigned int y_destination = atoi(argv[6]);

	univers.afficher();
	univers.plusCourtChemin( x_depart, y_depart, couleur_depart, x_destination, y_destination );

	return 0;
}
