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
    bouttonCalcul->setStyleSheet("background-color : grey; font-weight: bold; border-radius: 5px");
    layoutTrajet->addWidget(bouttonCalcul);

    labelResultat = new QLabel("", this);


    layoutTrajet->addWidget(labelResultat);

    connect(bouttonCalcul, SIGNAL(clicked(bool)), this, SLOT(calculerTemps()));

    //Initialisation et chargement
    g = new Graph(100); //on créé le graph pour les 100 villes
    CsvLoader loader("../../../../data/villes.csv", "../../../../data/temps.csv");

    try{
        //on essaie de charger les données depuis villes.csv dans notre listeVilles
        listeVilles = loader.charger_villes();

        //on remplit le graphe g avec les arêtes (temps) chargées depuis temps.csv
        loader.charger_temps(*g);

        //on remplit les combo box par les noms des viles
        for (const Ville &v : listeVilles){
            comboBoxDepart->addItem(QString::fromStdString(v.getNom()));
            comboBoxArivee->addItem(QString::fromStdString(v.getNom()));
        }
    } catch(const std::exception& e){
        qDebug()<< "Erreur de chargement :" << e.what();
    }

}

void MainWindow::calculerTemps(){
    labelResultat->setText("ça marche");
}

MainWindow::~MainWindow() = default;
