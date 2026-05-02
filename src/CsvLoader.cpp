#include "CsvLoader.hpp"
#include <ifstream>

CsvLoader::CsvLoader(const std::string& ch_villes, const std::string& ch_temps)
    : cheminVilles(ch_temps), cheminTemps(ch_temps)
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