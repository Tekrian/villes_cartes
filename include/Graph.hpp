#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <limits> //pour l'infini

const double inf = std::numeric_limits<double> ::infinity();

const unsigned int max_villes = 100;

class Graph {
    private:
        unsigned int nb_villes;
        double w[max_villes][max_villes]; // la matrice des temps
        int next[max_villes][max_villes]; //la matrice des chemins
    
        public:
            Graph(unsigned int);    //Constructeur de Graphe
            ~Graph();

            void ajouterChemin(unsigned int, unsigned int, double); //fonction qui ajoute unChemin entre deux ville
            void floydWarshall(); //la fonction de l'algo de Floyd Warshall qui calcule le plus court chemin
            double getTemps() const;
            std::vector<unsigned int> getChemin() const;
            unsigned int getNombreVilles()const;
};

#endif