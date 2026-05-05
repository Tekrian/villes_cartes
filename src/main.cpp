#include <iostream>
#include <vector>
#include "../include/Graph.hpp"
#include "../include/Ville.hpp"
#include "../include/CsvLoader.hpp"

/*
 * Fonction utilitaire : affiche un temps en heures et minutes
 * Exemple : 137 minutes → "2h 17min"
 * On utilise "inf" (minuscule) car c'est le nom défini dans Graph.hpp
 */
void afficherTemps(double minutes) {
    if (minutes == inf) {
        std::cout << "Aucun chemin trouvé";
        return;
    }
    int h   = (int)minutes / 60;
    int min = (int)minutes % 60;
    if (h > 0) std::cout << h << "h ";
    std::cout << min << "min";
}

int main() {

    // ----------------------------------------------------------
    // 1. Chargement des données
    // ----------------------------------------------------------
    std::cout << "=== Chargement des données ===\n";

    // Création du loader avec les chemins des deux CSV
    CsvLoader loader("data/villes.csv", "data/temps.csv");

    // Chargement des villes → retourne un vector<Ville>
    std::vector<Ville> villes = loader.charger_villes();

    // Création du graphe avec 100 villes
    Graph g(100);

    // Remplissage du graphe depuis temps.csv
    loader.charger_temps(g);

    // ----------------------------------------------------------
    // 2. Floyd-Warshall
    // ----------------------------------------------------------
    std::cout << "\n=== Calcul des chemins optimaux (Floyd-Warshall) ===\n";
    g.floydWarshall();
    std::cout << "Floyd-Warshall terminé avec succès.\n";

    // ----------------------------------------------------------
    // 3. Test : afficher quelques villes chargées
    // ----------------------------------------------------------
    std::cout << "\n=== 5 premières villes chargées ===\n";
    for (int i = 0; i < 5 && i < (int)villes.size(); i++) {
        // On utilise l'opérateur << que tu as défini dans Ville.cpp
        std::cout << villes[i];
    }

    // ----------------------------------------------------------
    // 4. Test : temps et chemin entre deux villes
    // ----------------------------------------------------------
    unsigned int depart  = 94;  // Paris
    unsigned int arrivee = 6;

    std::cout << "\n=== Trajet ville " << depart
              << " → ville " << arrivee << " ===\n";

    // Affichage du temps optimal
    double temps = g.getTemps(depart, arrivee);
    std::cout << "Temps optimal : ";
    afficherTemps(temps);
    std::cout << " (" << temps << " min)\n";

    // Affichage du chemin
    std::vector<unsigned int> chemin = g.getChemin(depart, arrivee);

    std::cout << "Chemin : ";
    for (int i = 0; i < (int)chemin.size(); i++) {
        unsigned int id = chemin[i];

        // On cherche le nom de la ville correspondant à cet ID
        std::string nom = "Inconnue";
        for (const Ville& v : villes) {
            if (v.getId() == id) {
                nom = v.getNom();
                break;
            }
        }
        std::cout << nom;
        if (i < (int)chemin.size() - 1) std::cout << " → ";
    }
    std::cout << "\n";

    return 0;
}