#include "../include/Ville.hpp"

Ville::Ville(unsigned int _id, std::string _nom, double _lat, double _lng, std::string _region, unsigned int _population)
    : id(_id), nom(_nom), lat(_lat), lng(_lng), region(_region), population(_population)
{

} // Constructeur de la classe ville

Ville::~Ville()
{
    
}

std::ostream& operator<<(std::ostream& os, const Ville& ville){
    os << "Ville [" << ville.id <<"] "
       << ville.nom
       << " (lat : " << ville.lat
       << ", long : " << ville.lng << ")";
    os << std::endl;

    return os;
}