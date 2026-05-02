#include "Ville.hpp"

Ville::Ville(unsigned int _id, std::string _nom, double _lat, double _lng)
    : id(_id), nom(_nom), lat(_lat), lng(_lng)
{

} // Constructeur de la classe ville

std::ostream& operator<<(std::ostream& os, const Ville& ville){
    os << "Ville [" << ville.id <<"] "
       << ville.nom
       << " (lat : " << ville.lat
       << ", long : " << ville.lng << ")";
    os << std::endl;

    return os;
}