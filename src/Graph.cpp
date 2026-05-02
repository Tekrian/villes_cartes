#include"Graph.hpp"

#include <stdexcept>

Graph::Graph(unsigned int nbr)
    : nb_villes(nbr)
{
    for(unsigned int u = 0; u < nbr; u++){
        for(unsigned int v = 0; v < nbr; v++){
            w[u][v] = inf; //initialise à l'infini pour signifier pas de route entre u et v
            next[u][v] = -1; //initialise à -1 car pas de chemin connu pour l'instant
        }
        w[u][u] = 0;  //initialise 0 sur la diagonale car une ville est à 0 min d'elle même
        next[u][u] = u; //une ville pointe vers elle même
    }
}

Graph::~Graph(){

}

void Graph::ajouterChemin(unsigned int u, unsigned int v, double temps){
    if(u < 0 || u >= nb_villes || v < 0 || v >= nb_villes)
        throw std::out_of_range ("Identifiant de ville hors limite");
    if(temps < 0)
        throw std::out_of_range("Le temps ne peut pas être négatif");
    
        if(temps < w[u][v]) //pour garder le minimum coût pour le chemin
        {
            w[u][v] = w[v][u] = temps; // car c'est le même temps qui sépare deux ville donc Graphe non orienté
            next[u][v] = v; // la prochaine ville de u à v zest v;
            next[v][u] = u;
        }
}

void Graph::floydWarshall(){
    for(unsigned int k = 0; k < nb_villes; k++){ //k, la ville intermédiaire
        for(unsigned int u = 0; u < nb_villes; u++){  //u est la ville de départ
            for(unsigned int v = 0; v < nb_villes; v++){  //v:la ville d'arrivé

                if(w[u][k] != inf && w[k][v] != inf){       //s'il existe de chemin intermédiare
                    double min = w[u][k] + w[k][v];
                    if(min < w[u][v]){                    // et que ce chemin est plus court,
                        w[u][v] =  min;                    //ce chemin devient le noveau plus optimale
                        next[u][v] = next[u][k];           // et on passe d'abord par cet intermédiaire
                    }

                }
            }
        }
    }
}