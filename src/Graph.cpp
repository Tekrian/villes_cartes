#include"Graph.hpp"

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

