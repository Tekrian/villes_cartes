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

    Graph *g;
    std::vector<Ville> listeVilles; //vecteur pour stockés les villes chargées

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void calculerTemps(); // fonction qui va connecter le boutton de calcul
    void ajouterVilleListe();
    void supprimerVilleListe();
    void genererTableauTemps();
};
#endif // MAINWINDOW_H
