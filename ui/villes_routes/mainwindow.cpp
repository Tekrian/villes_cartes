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

    //création de la liste déroulante pour la ville de départ
    comboBoxDepart = new QComboBox(this);
    comboBoxDepart->setEditable(true); // Laisser le choix à l'utilisateur de saisir quand même
    comboBoxDepart->setPlaceholderText("Saisir ou choisir une ville de départ");
    layoutTrajet->addWidget(comboBoxDepart);



}

MainWindow::~MainWindow() = default;
