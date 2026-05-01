#ifndef CSVLOADER_HPP
#define CSVLOADER_HPP

#include "Ville.hpp"
#include "Graph.hpp"
#include <vector>

class CsvLoader {
    private :
        std::string cheminVilles;   // Chemin vers villes.csv
        std::string cheminTemps;    // Chemin vers le fichier temps.csv
    
    public :
        CsvLoader(const std::string&, const std::string&);
        ~CsvLoader();

        std::vector<Ville> charger_villes() const;

        void charger_temps(Graph& g) const;
    
};

#endif