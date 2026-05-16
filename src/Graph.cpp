#include"../include/Graph.hpp"

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
        throw std::out_of_range ("Identifiant de ville hors limite dans ajouterChemin");
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

std::vector<unsigned int> Graph::getChemin(unsigned int u, unsigned int v) const{
    //vérification des identifiants
    if(u < 0 || u >= nb_villes || v < 0 || v >= nb_villes)
        throw std::out_of_range ("Identifiant de ville hors limite dans ajouterChemin");

    std::vector<unsigned int> chemin;
    if(next[u][v] == -1) //Cas où il n'existe pas de chemin entre u et v
        return {};
    unsigned int courrant = u;

    while(courrant != v){
        chemin.push_back(courrant);
        courrant = next[courrant][v];
    }
    chemin.push_back(v); //on ajoute la ville d'arrivé à la fin du chemin
    return chemin;
}//la fonction qui retourne le chemin entre u et v en utilisant la matrice next


std::vector<std::vector<double>> Graph::getMatriceTemps(const  std::vector<unsigned int>& id_villes) const{
    
    //Création et Initialisation de la matrice
    std::vector<std::vector<double>> tableau_temps(id_villes.size(), std::vector<double>(id_villes.size(), 0.0));
    // On cré un vecteur de ligne de id_villes.size(), initialisé à 0 et * id_villes.sizes colones
   
    for(size_t i =0; i < id_villes.size(); i++){
        for(size_t j = 0; j < id_villes.size(); j++){
            unsigned int u = id_villes[i];
            unsigned int v = id_villes[j];
            tableau_temps[i][j] = getTemps(u,v);
        }
    }
    return tableau_temps;
}//la fonction qui construit un tableau de temps entre un ensemble de villes choisies
