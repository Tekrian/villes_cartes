#ifndef VILLES_HPP
#define VILLES_HPP

#include <string>
#include <iostream>

class Ville{
    private :
        unsigned int id; //identifiant d'une ville
        std::string nom;   //le nom de la ville
        double lat; // la latittude
        double lng; // la longitude
        std::string region;     // la région de la ville
        unsigned int population; // la population de la ville

    public :
        Ville(const unsigned int, const std::string, const double, const double, const std::string, const unsigned int); //Constructeur de ville;
        ~Ville(); //Destructeur de ville

        inline unsigned int getId() const {return id;}; //Accessuer de consultation qui permet de consulter l'id d'une ville
        inline std::string getNom() const {return nom;};    //Accessuer de consultation qui permet de consulter le nom d'une ville
        inline double getLat() const {return lat;}; //Accessuer de consultation qui permet de consulter la lattitude d'une ville
        inline double getLong() const {return lng;};    //Accessuer de consultation qui permet de consulter la longitude d'une ville
        inline std::string getRegion() const {return region;}; //Accessuer de consultation qui permet de consulter la région d'une ville
        inline unsigned int getPopulation() const {return population;}; //Accessuer de consultation qui permet de consulter la population d'une ville

        friend std::ostream& operator<<(std::ostream&, const Ville&); // fonction qui affiche les infos d'une ville 

};

#endif 