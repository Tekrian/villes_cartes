#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Temps de routes"); //Titre de la fenêtre
    // setMinimumSize(600, 700); //

    //Création du widget centarl
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    //layout vertical
    layoutPrincipal = new QVBoxLayout();
    mainWidget->setLayout(layoutPrincipal);

    titre = new QLabel("Calculateur de temps de route ", this);
    titre->setFont(QFont("Arial", 18));
    titre->setAlignment(Qt::AlignCenter);
    layoutPrincipal->addWidget(titre);

    groupTrajet = new QGroupBox("Trouver un trajet", this);
    QVBoxLayout *layoutTrajet = new QVBoxLayout(groupTrajet);
    layoutTrajet->setSpacing(10);
    layoutPrincipal->addWidget(groupTrajet);

    //création de la liste déroulante éditable pour la ville de départ
    comboBoxDepart = new QComboBox(this);
    comboBoxDepart->setEditable(true); // Laisser le choix à l'utilisateur de saisir quand même
    comboBoxDepart->setPlaceholderText("Saisir ou choisir une ville de départ");
    layoutTrajet->addWidget(comboBoxDepart);

    //pour la ville d'arrivée
    comboBoxArivee = new QComboBox(this);
    comboBoxArivee->setEditable(true);
    comboBoxArivee->setPlaceholderText("Saisir ou choisir une ville d'arrivée");
    layoutTrajet->addWidget(comboBoxArivee);

    //Ajout du boutton de calcul du trajet
    bouttonCalcul = new QPushButton("Calculer le trajet", this);
    bouttonCalcul->setStyleSheet("background-color : #2ecc71; font-weight: bold; border-radius: 5px");
    layoutTrajet->addWidget(bouttonCalcul);

    labelResultat = new QLabel("", this);
    labelResultat->setStyleSheet(
        "QLabel {"
        "   background-color: #f8f9fa;"
        "   border: 1px dashed #bdc3c7;"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "   font-size: 14px;"
        "   color: #2c3e50;"
        "}"
        );

    layoutTrajet->addWidget(labelResultat);

}

MainWindow::~MainWindow() = default;
