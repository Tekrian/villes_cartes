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
    comboBoxDepart->setPlaceholderText("Saisir ou choisir une ville de départ");
    comboBoxDepart->setEditable(true); // Laisser le choix à l'utilisateur de saisir quand même
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

    //on cherche le plus court chemin avec l'algo de floydWarshall
    g->floydWarshall();

    //Tableau de temps
    groupTableau = new QGroupBox("Tableau de temps", this);
    QVBoxLayout *layoutTableau = new QVBoxLayout(groupTableau); //layout vertical interne à groupTableau
    layoutTableau->setSpacing(10); // pour espacer les composants du tableau
    layoutPrincipal->addWidget(groupTableau); //on ajoute le bloc du tableau dans le layout vertical principal

    layoutOutilsTableau = new QHBoxLayout();

    comboChoixVille = new QComboBox(this);
    comboChoixVille->setPlaceholderText("Choisir une ville à ajouter ...");

    //On remplie le combox avec les données (villes)
    for(const Ville &v : listeVilles)
        comboChoixVille->addItem(QString::fromStdString(v.getNom()));
    layoutOutilsTableau->addWidget(comboChoixVille);

    //Création du bouton +
    boutonAjouter = new QPushButton("+", this);
    boutonAjouter->setFixedWidth(40);
    boutonAjouter->setStyleSheet("background-color: #2ecc71; font-weight: bold; color : white; ");
    layoutOutilsTableau->addWidget(boutonAjouter);

    //Création du bouton -
    boutonSupprimer = new QPushButton("-", this);
    boutonSupprimer->setFixedWidth(40);
    boutonSupprimer->setStyleSheet("background-color: #e74c3c; font-weight: bold; color: white; ");
    layoutOutilsTableau->addWidget(boutonSupprimer);

    //border-radius: 5px
    // boutonAjouter->setFixedSize(40, 40);
    // boutonSupprimer->setFixedSize(40, 40);

    layoutTableau->addLayout(layoutOutilsTableau);

    //Création du QListWidget pour la liste des villes choisies
    villesSelectionnees = new QListWidget(this);
    layoutTableau->addWidget(villesSelectionnees);

    //Création du bouton pour générer la matrice de temps
    boutonGenererTableau = new QPushButton("Générer le tableau de temps", this);
    boutonGenererTableau->setStyleSheet("background-color: #34495e; font-weight: bold; color : white; border-radius: 5px; min-height: 35px;");
    layoutTableau->addWidget(boutonGenererTableau);

    //Création de la matrice de temps
    matriceTemps = new QTableWidget(this);
    layoutTableau->addWidget(matriceTemps);

    //les connect des 3 bouutons à leurs actions respectifs
    connect(boutonAjouter, SIGNAL(clicked(bool)), this, SLOT(ajouterVilleListe()));
    connect(boutonSupprimer, SIGNAL(clicked(bool)), this, SLOT(supprimerVilleListe()));
    connect(boutonGenererTableau, SIGNAL(clicked(bool)), this, SLOT(genererTableauTemps()));
}//Constructeur


void MainWindow::calculerTemps(){
    labelResultat->setStyleSheet("color: black"); // pOur rénitialiser la couleur du label après affichage d'un text en rouge pour les erreurs

    //On récupère les text (les villes) sélectionnés dans dans combo box
    QString villeDepart = comboBoxDepart->currentText();
    QString villeArrivee = comboBoxArivee->currentText();

    //Si les deux villes n'ont pas été sélectionnées
    if(villeDepart.isEmpty() || villeArrivee.isEmpty()){
        labelResultat->setText("Veuillez saisir une ville de départ et une ville d'arrivée");
        labelResultat->setStyleSheet("color: #c0392b");
        return; // la fonction s'arrête alors là
    }

    //les variables pour stockés les id des villes choisies
    int idDepart = -1;
    int idArrivee = -1;

    for(const Ville& v : listeVilles){
        if(QString::fromStdString(v.getNom()) == villeDepart)
            idDepart = v.getId();
        if(QString::fromStdString(v.getNom()) == villeArrivee)
            idArrivee = v.getId();
    }

    //Si la ville saisie n'existe pas
    if(idDepart == -1 || idArrivee == -1){
        labelResultat->setText("Une ville saisie est introuvable");
        labelResultat->setStyleSheet("color: #c0392b");
        return; // on arrête alors la fonction ici
    }
    double tempsMinutes = g->getTemps(idDepart, idArrivee); // variable pour stocker le temps entre les deux ville en minutes

    if(tempsMinutes == inf){
        labelResultat->setText("Aucun itinéraire entre ces deux villes");
        labelResultat->setStyleSheet("color: #c0392b");
        return;
    }
    //conversion du temps sous forme  heure minutes
    int heures = static_cast<int> (tempsMinutes)/60 ;
    int minutes = static_cast<int> (tempsMinutes) % 60;

    QString texteTemps = QString("Temps : %1h %2min").arg(heures).arg(minutes);
    QString texteChemins = "Chemin : "; //variable pour stocker les chemins du trajet

    std::vector<unsigned int> iDsChemins = g->getChemin(idDepart, idArrivee); // liste des iDs constituant le plus court chemin

    // Boucle sur la liste pour l'affichage des chemins (le nom des villes) dans tetxteChemins avec -> (suivant)
    for (size_t i = 0; i < iDsChemins.size(); i++){
        unsigned int idCourrant = iDsChemins[i]; // l'id courrant
        for(const Ville& v : listeVilles){
            if(v.getId() == idCourrant)
                texteChemins += QString::fromStdString(v.getNom());
        }
        if(i < iDsChemins.size() -1) //si ce n'est pas la dernière, on ajoute ->
            texteChemins += " -> ";
    }

    labelResultat->setText(texteTemps + "\n" + texteChemins);

}

void MainWindow::ajouterVilleListe(){
    QString nomVille =  comboChoixVille->currentText(); //on récupère le nom de la ville sélectionnée dans le combo box

    if(nomVille.isEmpty())
        return;

    //On vérifie si la ville est déja dans la liste
    for(int i =0; i < villesSelectionnees->count(); i++)
        if(villesSelectionnees->item(i)->text() == nomVille) //item(i) qui récupere la ligne i et text() son text
            return; //on ajoute pas si elle existe déja (on ne fait rien)

    villesSelectionnees->addItem(nomVille);
}

void MainWindow::supprimerVilleListe(){
    QListWidgetItem *ligneSelectionnee = villesSelectionnees->currentItem();
    if(ligneSelectionnee != nullptr){
        int ligne = villesSelectionnees->row(ligneSelectionnee);
        delete villesSelectionnees->takeItem(ligne);
    }
}
void MainWindow::genererTableauTemps(){
    //On crée un vecteur pour stocker les IDs des villes sélectionnées
    std::vector<unsigned int> idsSelectionnes;

    //On parcourt le QListWidget pour retrouver l'id de chaque ville affichée
    for (int i = 0; i < villesSelectionnees->count(); ++i) {
        QString nomVille = villesSelectionnees->item(i)->text();

        // On cherche cette ville dans notre vecteur global de villes pour récupérer son ID
        for (const Ville& v : listeVilles)
            if (QString::fromStdString(v.getNom()) == nomVille)
                idsSelectionnes.push_back(v.getId());
    }

    //si l'utilisateur ne met aucune ville ou une seule, on ne fait rien
    if (idsSelectionnes.size() < 2) {
        return;
    }

    std::vector<std::vector<double>> matriceMinutes = g->getMatriceTemps(idsSelectionnes);

    //On configure les dimensions de notre grille de composants Qt (QTableWidget)
    int taille = idsSelectionnes.size();
    matriceTemps->setRowCount(taille);    // Nombre de lignes
    matriceTemps->setColumnCount(taille); // Nombre de colonnes

    //On prépare les titres des lignes et des colonnes avec le nom des villes
    QStringList listeNomsEnTetes;
    for (int i = 0; i < taille; ++i) {
        // On récupère le texte directement depuis la liste visuelle dans le même ordre
        listeNomsEnTetes << villesSelectionnees->item(i)->text();
    }

    // On applique ces noms aux en-têtes du tableau
    matriceTemps->setHorizontalHeaderLabels(listeNomsEnTetes);
    matriceTemps->setVerticalHeaderLabels(listeNomsEnTetes);

    //Double boucle pour remplir toutes les cellules
    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < taille; ++j) {
            double minutesBrutes = matriceMinutes[i][j];
            QString texteCellule;

            // Si c'est la même ville (la diagonale de la matrice)
            if (i == j) {
                texteCellule = "0";
            }
            // Si la valeur est l'infini c'est qu'il n'y a aucun trajet possible
            else if (minutesBrutes == inf) {
                texteCellule = "-";
            }
            // Sinon, on convertit les minutes en format heure min
            else {
                int h = static_cast<int>(minutesBrutes) / 60;
                int m = static_cast<int>(minutesBrutes) % 60;
                if (h > 0) {
                    texteCellule = QString("%1h %2m").arg(h).arg(m);
                } else {
                    texteCellule = QString("%1m").arg(m);
                }
            }

            QTableWidgetItem* itemCellule = new QTableWidgetItem(texteCellule);

            //On empêche l'utilisateur de modifier les chiffres du tableau au clavier
            itemCellule->setFlags(itemCellule->flags() ^ Qt::ItemIsEditable);

            // On centre le texte à l'intérieur de la cellule
            itemCellule->setTextAlignment(Qt::AlignCenter);

            // On injecte le composant dans la grille à la position (ligne i, colonne j)
            matriceTemps->setItem(i, j, itemCellule);
        }
    }
}

MainWindow::~MainWindow() = default;
