#include "../include/CsvLoader.hpp"

#include <sstream>
#include <fstream>
#include <stdexcept>

CsvLoader::CsvLoader(const std::string& ch_villes, const std::string& ch_temps)
    : cheminVilles(ch_villes), cheminTemps(ch_temps)
{

}

CsvLoader::~CsvLoader()
{

}

std::vector<std::string> CsvLoader::splitLigne(const std::string& ligne) const{
    std::vector<std::string> str;
    std::stringstream ss(ligne);
    std::string caractere;

    while(std::getline(ss, caractere, ','))
        str.push_back(caractere);

    return str;
}

std::vector<Ville> CsvLoader::charger_villes() const{
    //la fonction qui charge les villes en ouvrant villes.csv et créé une Ville pour chaque ligne
    std::ifstream file(cheminVilles);
    
    if(!file.is_open())
        throw std::runtime_error("Impossible d'ouvrir " + cheminVilles);

    std::vector<Ville> villes;
    std::string ligne;
    
    std::getline(file, ligne); //on saute la première ligne de villes.csv car c'est l'en tête
    while (std::getline(file,ligne))
    {
        if(!ligne.empty()){
            std::vector<std::string> cols = splitLigne(ligne);

            //transformation des strings récupérés en colones en leurs types équivalents
            unsigned int id = std::stoi(cols[1]);
            std::string name = cols[0];
            double _lat = std::stod(cols[3]);   //cols[2] correspond à l'espace
            double _lng = std::stod(cols[4]);
            std::string _region = cols[8];
            unsigned int population  = 0;
            // comme la population peutetre vide dans le csv, on vérifie avant de la convertir en entier
            if (!cols[14].empty())
                population = std::stoul(cols[14]);

            Ville city(id, name, _lat, _lng, _region, population); //création de la ville
            villes.push_back(city);             //l'ajout de la ville créée au vecteur
        }
    }

    std::cout << villes.size() <<" villes ont été chargé depuis " << cheminVilles;
    std::cout << std::endl;
    return villes;    
}

void CsvLoader::charger_temps(Graph& g) const{
    //la fonction qui charge les temps de route en ouvrant temps.csv et ajoute les arêtes au graphe
    std::ifstream file(cheminTemps);

    if(!file.is_open())
        throw std::runtime_error("Impossible d'ouvrir " + cheminTemps);
    std::string ligne;
    std::size_t nb_arete  = 0;
    while(std::getline(file,ligne)){
        if(!ligne.empty()){
            std::vector<std::string> cols = splitLigne(ligne);
        
            unsigned int id1 = std::stoi(cols[0]);
            unsigned int id2 = std::stoi(cols[1]);
            double tmps = std::stod(cols[2]);

            //on ajoute l'arete entre les deux villes au graphe
            g.ajouterChemin(id1, id2, tmps);
            nb_arete++;
        }
    }
    std::cout << nb_arete <<" arêtes ont été chargés depuis " << cheminTemps;
    std::cout << std::endl;
}