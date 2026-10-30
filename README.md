# Villes & Routes

Application de bureau avec interface graphique **Qt**, réalisée dans le cadre d’une **SAE** et développée avec **Qt Creator**. Elle permet d’étudier des trajets entre des villes françaises, de comparer leurs temps de parcours et de rechercher un emplacement de dépôt pertinent.

## Fonctionnalités

- Calcul du temps minimal entre une ville de départ et une ville d’arrivée.
- Affichage de l’itinéraire correspondant, avec le nom des villes traversées.
- Comparaison des temps de trajet sous forme de matrice pour une sélection de villes.
- Tri des villes par nom ou par population.
- Filtrage des villes par région.
- Recherche d’un emplacement de dépôt desservant les villes sélectionnées, selon l’un des critères suivants :
  - minimiser la somme des temps de trajet ;
  - minimiser le temps maximal de trajet.
- Indication lorsqu’aucun itinéraire n’est disponible.

## Technologies et méthodes

- **C++17**
- **Qt Widgets** pour l’interface graphique
- **qmake** pour la configuration de la compilation Qt
- **Fichiers CSV** pour les données
- **Graphe pondéré non orienté** : les villes sont les sommets et les liaisons routières sont pondérées par leur temps de parcours
- **Algorithme de Floyd–Warshall** pour calculer les plus courts temps entre toutes les paires de villes et reconstruire les itinéraires

L’algorithme de Floyd–Warshall a une complexité en temps de `O(V³)` et une complexité en mémoire de `O(V²)`, où `V` est le nombre de villes.

## Données

Les données sont fournies dans le répertoire [`data/`](data/) :

- [`villes.csv`](data/villes.csv) contient les informations sur les villes, notamment leur identifiant, leur nom, leurs coordonnées, leur région et leur population.
- [`temps.csv`](data/temps.csv) contient les liaisons entre villes et leurs temps de parcours, en minutes.

Le jeu fourni contient **100 villes** et **542 liaisons**. Les identifiants des villes sont utilisés comme indices dans le graphe ; le programme crée actuellement un graphe de 100 sommets.

## Organisation du projet

```text
.
├── data/
│   ├── temps.csv
│   └── villes.csv
├── include/
│   ├── CsvLoader.hpp
│   ├── Graph.hpp
│   └── Ville.hpp
├── src/
│   ├── CsvLoader.cpp
│   ├── Graph.cpp
│   ├── Ville.cpp
│   └── main.cpp
└── ui/
    └── villes_routes/
        ├── main.cpp
        ├── mainwindow.cpp
        ├── mainwindow.h
        └── villes_routes.pro
```

- `Ville` représente une ville et ses attributs.
- `CsvLoader` charge les villes et les temps de parcours depuis les fichiers CSV.
- `Graph` stocke les temps et les itinéraires, puis calcule les plus courts chemins.
- `ui/villes_routes/` contient l’application principale : l’interface graphique Qt.
- `src/main.cpp` contient un point d’entrée console secondaire, utile pour tester le chargement des données et les calculs sans l’interface.


## Démonstration

[Video de démonstration](https://github.com/user-attachments/assets/3a87c5ff-3210-4f61-b973-5933b0c01a64)