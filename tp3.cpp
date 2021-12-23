#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <algorithm>

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

		int getIDSommet(const P& a){
			int ia = indices[a];
			return ia;
		}

		P getPosition(const int& index){
			return sommets[index].position;
		}
};

class Position{
	public:
		int couleur; // couleur du sommet
		int x;
		int y;
		int c; // couleur de l'univers
		int n;

public:
	Position(){}
	Position(const int& couleur_, const int& x_, const int& y_, const int& c_, const int& n_){
		couleur = couleur_;
		x = x_;
		y = y_;
		c = c_;
		n = n_;
	}

	friend bool operator<(const Position& p1, const Position& p2)
    {
		int t1 = p1.c * (p1.n*p1.n) + p1.y * p1.n + p1.x;
		int t2 = p2.c * (p1.n*p1.n) + p2.y * p1.n + p2.x;
		if(t1 < t2){
			return true;
		}
		return false;
    }

	friend bool operator==(const Position& p1, const Position& p2){
		if(p1.c == p2.c && p1.couleur == p2.couleur && p1.x == p2.x && p1.y == p2.y)
			return true;
		return false;
	}
};


class Univers
{
	public:
	int N; 	// Nombre de ligne et nombre de colonnes
	int C; 	// Nombre de couleur
	Graph<Position, pair<char, int>> graph;
	// TODO : Complétez avec les attributs nécessaires pour représenter l'univers

public:
	Univers() {
		
	}

	~Univers() {

	}

	void plusCourtChemin(int x_depart, int y_depart, int couleur_depart, int x_destination, int y_destination) {
		int distance[graph.sommets.size()];
		vector<Position> precedent;
		Position target(0, x_destination, y_destination, 0, N);
		char directionPrecedente[graph.sommets.size()];
		vector<Position> visite;
		vector<bool> nonVisite;
		int indexDebut;
		Position p;
		for(int i = 0; i < graph.sommets.size(); i++){
			distance[i] = 1000000;
			visite.push_back(graph.sommets[i].position);
			nonVisite.push_back(false);
			precedent.push_back(p);
		}
		indexDebut = graph.getIDSommet(Position(0, x_depart, y_depart, couleur_depart, N));
		distance[indexDebut] = 0;

		for(int i =0; i < visite.size(); i++){
			int index = plusPetit(distance, nonVisite);
			nonVisite[index] = true;
			Position position = visite[index];
			if(target == position) break;
			auto mapArete = graph.sommets[graph.getIDSommet(position)].areteSortantes;
			int distCourante;
			for(auto iter = mapArete.begin(); iter != mapArete.end(); ++iter){
				if(!nonVisite[iter->first]){
					auto paireTemporaire = iter->second;
					distCourante = distance[graph.getIDSommet(position)] + paireTemporaire.second;
					if(distCourante < distance[graph.getIDSommet(graph.getPosition(iter->first))]){
						distance[graph.getIDSommet(graph.getPosition(iter->first))] = distCourante;
						precedent[graph.getIDSommet(graph.getPosition(iter->first))] = position;
						directionPrecedente[graph.getIDSommet(graph.getPosition(iter->first))] = paireTemporaire.first;
					}
				}
			}
		}


		vector<char> fin;
		int res = distance[graph.getIDSommet(target)];
		if(directionPrecedente[graph.getIDSommet(target)] =='c')
			res -= 2;
		else
			res -= 1;
		target = precedent[graph.getIDSommet(target)];
		while(graph.getIDSommet(target) != indexDebut){
			int id = graph.getIDSommet(target);
			fin.insert(fin.begin(),directionPrecedente[id]);
			target = precedent[graph.getIDSommet(target)];
		}
		if(graph.getPosition(indexDebut) == target){
			int id = graph.getIDSommet(target);
			fin.insert(fin.begin(),directionPrecedente[id]);
		}
		for(int i = 1; i < fin.size(); i++){
			cout << fin[i] << " ";
		}
		cout << res <<endl;
	}

	int plusPetit(int distance[], vector<bool> nonVisite){
		int minimum = 10000000, valeurDeRetour = 100000000;
		for(int i = 0; i < nonVisite.size(); i++){
			if(distance[i] <= minimum && !nonVisite[i]){
				minimum = distance[i];
				valeurDeRetour = i;
			}
		}
		return valeurDeRetour;
	}

	friend std::istream& operator >> (std::istream& is, Univers& recette);
};


std::istream& operator >> (std::istream& is, Univers& univers) {

	is >> univers.N; 		// Nombre de ligne et de colonnes
	is >> univers.C; 		// Nombre de couleurs

	assert(univers.N > 0);
	assert(univers.C > 0);

	vector<int> vectorCouleur;
	//couleur des sommets
	for(int i = 0; i < univers.N*univers.N; i++){
		int couleur;
		is >> couleur;
		vectorCouleur.push_back(couleur);
	}

	for(int c = 0; c<univers.C; c++){

		for(int i = 0; i<univers.N; i++) {
			for(int j = 0; j<univers.N; j++) {
				Position position(vectorCouleur[i*univers.N + j], j, i, c, univers.N);
				univers.graph.ajouterSommet(position);
			}
		}
	}

	int couleurUnivers;
	int couleurSommet;

	for(int i = 0; i < univers.graph.sommets.size(); i++){
		if(i-univers.N >= 0 && i / (univers.N * univers.N) == (i - univers.N) / (univers.N * univers.N) && i / (univers.N * univers.N) != univers.graph.sommets[i - univers.N].position.couleur)
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i-univers.N].position, make_pair('h',1));

		if((i+1) % univers.N != 0 && i / (univers.N * univers.N) != univers.graph.sommets[i+1].position.couleur) 
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i+1].position, make_pair('d',1));

		if(i+univers.N < univers.graph.sommets.size() && i / (univers.N * univers.N) != univers.graph.sommets[i+univers.N].position.couleur) 
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i+univers.N].position, make_pair('b',1));

		if((i-1) % univers.N != 6 && i-1 >= 0 && i / (univers.N * univers.N) != univers.graph.sommets[i-1].position.couleur) 
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i-1].position, make_pair('g',1));

		couleurUnivers = univers.graph.sommets[i].position.c;
		couleurSommet = univers.graph.sommets[i].position.couleur;

		if(couleurSommet != couleurUnivers && couleurSommet < couleurUnivers){
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i - (abs(couleurSommet-couleurUnivers)*univers.N*univers.N)].position, make_pair('c',2));
		}
		if(couleurSommet != couleurUnivers && couleurSommet > couleurUnivers){
			univers.graph.ajouterArete(univers.graph.sommets[i].position, univers.graph.sommets[i + (abs(couleurSommet-couleurUnivers)*univers.N*univers.N)].position, make_pair('c',2));
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

	int x_depart = atoi(argv[2]);
	int y_depart = atoi(argv[3]);
	int couleur_depart = atoi(argv[4]);
	int x_destination = atoi(argv[5]);
	int y_destination = atoi(argv[6]);

	univers.plusCourtChemin( x_depart, y_depart, couleur_depart, x_destination, y_destination );

	return 0;
}
