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
			assert(indices.count(p) == 0);
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

	friend bool operator<(const Position& p1, const Position& p2)
    {
		if(p1.c < p2.c || p1.x < p2.x || p1.y < p2.y)
			return true;
        return false;
    }
};


class Univers
{
	public:
	int N; 	// Nombre de ligne et nombre de colonnes
	int C; 	// Nombre de couleur
	Graph<Position, int> graph;
	// TODO : Complétez avec les attributs nécessaires pour représenter l'univers

public:
	Univers() {
		
	}

	~Univers() {

	}

	void plusCourtChemin(int x_depart, int y_depart, int couleur_depart, int x_destination, int y_destination) {
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

	vector<int> vectorCouleur;

	for(int i = 0; i < univers.N*univers.N; i++){
		int couleur;
		is >> couleur;
		vectorCouleur.push_back(couleur);
	}

	for(int c = 0; c<univers.C; c++){

		for(int i = 0; i<univers.N; i++) {
			for(int j = 0; j<univers.N; j++) {
				Position position(vectorCouleur[i*univers.N + j], j, i, c);
				univers.graph.ajouterSommet(position);
				cout << position.x << "," << position.y << " " << position.couleur << "   ";
				//std::cerr << "TODO : considérer la cellule (" << x << ", " << y << ") est de couleur " << couleur << std::endl;
			}
			cout << endl;
		}
		cout << endl;
	}

	int couleurUnivers;
	int couleurSommet;

	for(int i = 0; i < univers.graph.sommets.size(); i++){
		if(i-univers.N >= 0)
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i-univers.N].position, 1);
		if((i+1) % univers.N != 0) 
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i+1].position, 1);
		if(i+univers.N < univers.graph.sommets.size()) 
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i+univers.N].position, 1);
		if((i-1) % univers.N == 6) 
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i-1].position, 1);

		couleurUnivers = univers.graph.sommets[i].position.c;
		couleurSommet = univers.graph.sommets[i].position.couleur;

		if(couleurSommet != couleurUnivers && couleurSommet < couleurUnivers){
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i - (couleurUnivers-couleurSommet*univers.N*univers.N)].position, 2);
		}
		if(couleurSommet != couleurUnivers && couleurSommet > couleurUnivers){
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i + (couleurUnivers+couleurSommet*univers.N*univers.N)].position, 2);
		}
	}

	/*for(unsigned int c = 0; c<univers.C; c++){

		for(unsigned int i = 0; i<univers.N; i++) {
			for(unsigned int j = 0; j<univers.N; j++) {
				Position position(vectorCouleur[i*univers.N + j], j, i, c);
				univers.graph.ajouterSommet(position);
				cout << position.x << "," << position.y << " " << position.c << "   ";
				//std::cerr << "TODO : considérer la cellule (" << x << ", " << y << ") est de couleur " << couleur << std::endl;
			}
			cout << endl;
		}
		cout << endl;
	}*/

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

	int x_depart = atoi(argv[2]);
	int y_depart = atoi(argv[3]);
	int couleur_depart = atoi(argv[4]);
	int x_destination = atoi(argv[5]);
	int y_destination = atoi(argv[6]);

	univers.plusCourtChemin( x_depart, y_depart, couleur_depart, x_destination, y_destination );

	return 0;
}
