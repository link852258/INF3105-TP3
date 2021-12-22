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



template <class P, class A>
class Graph{
	public:
		struct Sommet{
			Sommet(const P& p_) : position(p_){}
			P position;
			map<int, A> areteSortantes;
		};

		map<P, int> indices;
		vector<Sommet> sommets;
		void ajouterSommet(const P& p){
			assert(!indices.count(p) == 0);
			int indice  = indices.size();
			indices[p] = indice;
			sommets.push_back(Sommet(p));
		}

		void ajouterArete(const P& a, const P& b, const A& etiquette){
			int ia = indices[a];
			int ib = indices[b];
			sommets[ia].areteSortantes[ib] = etiquette;
		}
};

class Position{
	public:
		int couleur;
		int x;
		int y;
		int c;

public:
	Position(const int& couleur_, const int& x_, const int& y_, const int& c_){
		couleur = couleur_;
		x = x_;
		y = y_;
		c = c_;
	}

	friend
};


class Univers
{
	public:
	unsigned int N; 	// Nombre de ligne et nombre de colonnes
	unsigned int C; 	// Nombre de couleur
	Graph<Position, int> graph;
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
	friend std::istream& operator >> (std::istream& is, Univers& recette);
};


std::istream& operator >> (std::istream& is, Univers& univers) {

	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs

	assert(univers.N > 0);
	assert(univers.C > 0);

	for(unsigned int c = 0; c<univers.C; c++){

		for(unsigned int i = 0; i<univers.N; i++) {
			for(unsigned int j = 0; j<univers.N; j++) {
				unsigned int couleur;
				is >> couleur;
				Position position(couleur, j, i, c);
				univers.graph.ajouterSommet(position);
				//std::cerr << "TODO : considérer la cellule (" << x << ", " << y << ") est de couleur " << couleur << std::endl;
			}
		}
	}

	
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
	univers.plusCourtChemin( x_depart, y_depart, couleur_depart, x_destination, y_destination );

	return 0;
}
