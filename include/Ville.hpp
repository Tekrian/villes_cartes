#ifndef VILLES_HPP
#define VILLES_HPP

#include <string>
#include <iostream>

class Ville{
    private :
        unsigned int id;
        std::string nom;
        double lat;
        double lng;

    public :
        Ville(const size_t, const std::string, const double, const double); //Constructeur de ville;
       Ville(const Ville&); //Constructeur par copie
        ~Ville(); //Destructeur de ville

        inline unsigned int getId() const {return id;}; //Accessuer de consultation qui permet de consulter l'id d'une ville
        inline std::string getNom() const {return nom;};    //Accessuer de consultation qui permet de consulter le nom d'une ville
        inline double getLat() const {return lat;}; //Accessuer de consultation qui permet de consulter la lattitude d'une ville
        inline double getLong() const {return lng;};    //Accessuer de consultation qui permet de consulter la longitude d'une ville

        friend std::ostream& operator<<(std::ostream&, const Ville&); // fonction qui affiche les infos d'une ville 

};

#endif 