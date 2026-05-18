#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QRadioButton>

#include <QDebug>

#include "../../include/CsvLoader.hpp"
#include "../../include/Graph.hpp"
#include "../../include/Ville.hpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    QScrollArea *scrollArea;

    QWidget *mainWidget; //Le conteneur principal
    QVBoxLayout *layoutPrincipal; // l'objet pour organiser les widgets verticalement
    QLabel *titre; //titre de l'application
    QGroupBox *groupTrajet;
    QComboBox *comboBoxDepart;
    QComboBox *comboBoxArivee;
    QPushButton *bouttonCalcul;
    QLabel *labelResultat;
    QGroupBox *groupTableau;
    QComboBox *comboChoixVille; // la liste déroulante pour ajouter une ville au tableu de temps
    QPushButton *boutonAjouter; // Bouton [+] pour ajouter une ville
    QPushButton *boutonSupprimer; // Bouton [-] pour supprimer un ville
    QHBoxLayout *layoutOutilsTableau; // le layout H pour aligner le combo box et les boutons
    QListWidget *villesSelectionnees;
    QPushButton *boutonGenererTableau;
    QTableWidget *matriceTemps;

    QRadioButton *radioSomme;
    QRadioButton *radioMax;
    QPushButton *boutonCalculerDepot;
    QLabel *labelResultatDepot;

    Graph *g;
    std::vector<Ville> listeVilles; //vecteur pour stockés les villes chargées

    QComboBox* comboTri;     // Trier par nom ou population
    QComboBox* comboRegion;  // Filtrer par région

    QPushButton *boutonQuitter; // Bouton pour fermer l'application

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void calculerTemps(); // méthode qui va connecter le boutton de calcul
    void ajouterVilleListe();
    void supprimerVilleListe();
    void genererTableauTemps();

    void mettreAJourComboBox(); //méthode pour mettre à jour les ComBox selon les tri et filtre
    void trierVilles();// méthode qui sera appelé quand l'utilisateur change le tri
    void filtrerParRegion(); // méthode qui sera appelé quand l'utilisateur change le filtre région

    void trouverDepotOptimal();
};
#endif // MAINWINDOW_H
