#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

#include <QDebug>

#include "../../include/CsvLoader.hpp"
#include "../../include/Graph.hpp"
#include "../../include/Ville.hpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    QWidget *mainWidget; //Le conteneur principal
    QVBoxLayout *layoutPrincipal; // l'objet pour organiser les widgets verticalement
    QLabel *titre; //titre de l'application
    QGroupBox *groupTrajet;
    QComboBox *comboBoxDepart;
    QComboBox *comboBoxArivee;
    QPushButton *bouttonCalcul;
    QLabel *labelResultat;

    Graph *g;
    std::vector<Ville> listeVilles; //vecteur pour stockés les villes chargées

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void calculerTemps(); // fonction qui va connecter le boutton de calcul
};
#endif // MAINWINDOW_H
