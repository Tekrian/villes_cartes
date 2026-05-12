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


}

MainWindow::~MainWindow() = default;
