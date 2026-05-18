#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Temps de routes"); //Titre de la fenêtre
    // setMinimumSize(600, 700); //

    //Création du widget centarl
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); // pour s'adapter au contenu
    setCentralWidget(scrollArea);
    mainWidget = new QWidget();
    scrollArea->setWidget(mainWidget);

    //Initialisation et chargement
    g = new Graph(100); //on créé le graph pour les 100 villes
    CsvLoader loader("../../../../data/villes.csv", "../../../../data/temps.csv");

    try{
        //on essaie de charger les données depuis villes.csv dans notre listeVilles
        listeVilles = loader.charger_villes();

        //on remplit le graphe g avec les arêtes (temps) chargées depuis temps.csv
        loader.charger_temps(*g);
    } catch(const std::exception& e){
        qDebug()<< "Erreur de chargement :" << e.what();
    }

    //on cherche le plus court chemin avec l'algo de floydWarshall
    g->floydWarshall();

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

    //Ligne tri et filtre
    QHBoxLayout* layoutFiltres = new QHBoxLayout();

    // ComboBox pour choisir le tri
    comboTri = new QComboBox();
    comboTri->addItem("Trier par : Nom");
    comboTri->addItem("Trier par : Population");
    comboTri->setMinimumHeight(30);

    // ComboBox pour filtrer par région
    comboRegion = new QComboBox();
    comboRegion->addItem("Toutes les régions"); // option par défaut
    // On remplit avec les régions uniques du CSV
    QStringList regions;
    for (const Ville& v : listeVilles) {
        QString r = QString::fromStdString(v.getRegion());
        if (!r.isEmpty() && !regions.contains(r))
            regions.append(r);
    }
    regions.sort();
    comboRegion->addItems(regions);
    comboRegion->setMinimumHeight(30);

    layoutFiltres->addWidget(comboTri);
    layoutFiltres->addWidget(comboRegion);
    layoutTrajet->addLayout(layoutFiltres);

    //création de la liste déroulante éditable pour la ville de départ          CHOIX VILLE
    comboBoxDepart = new QComboBox(this);
    comboBoxDepart->setEditable(true); // Laisser le choix à l'utilisateur de saisir quand même
    comboBoxDepart->lineEdit()->setPlaceholderText("Saisir ou choisir une ville de départ");
    layoutTrajet->addWidget(comboBoxDepart);

    //pour la ville d'arrivée
    comboBoxArivee = new QComboBox(this);
    comboBoxArivee->setEditable(true);
    comboBoxArivee->lineEdit()->setPlaceholderText("Saisir ou choisir une ville d'arrivée");
    layoutTrajet->addWidget(comboBoxArivee);

    //Ajout du boutton de calcul du trajet
    bouttonCalcul = new QPushButton("Calculer le trajet", this);
    bouttonCalcul->setStyleSheet("background-color : grey; border-radius: 5px");
    layoutTrajet->addWidget(bouttonCalcul);

    labelResultat = new QLabel("", this);


    layoutTrajet->addWidget(labelResultat);

    connect(bouttonCalcul, SIGNAL(clicked(bool)), this, SLOT(calculerTemps()));

    //Tableau de temps
    groupTableau = new QGroupBox("Tableau de temps", this);
    QVBoxLayout *layoutTableau = new QVBoxLayout(groupTableau); //layout vertical interne à groupTableau
    layoutTableau->setSpacing(10); // pour espacer les composants du tableau
    layoutPrincipal->addWidget(groupTableau); //on ajoute le bloc du tableau dans le layout vertical principal

    layoutOutilsTableau = new QHBoxLayout();

    comboChoixVille = new QComboBox(this);
    comboChoixVille->setEditable(true);
    comboChoixVille->lineEdit()->setPlaceholderText("Choisir une ville à ajouter ...");

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

    layoutTableau->addLayout(layoutOutilsTableau);

    //Création du QListWidget pour la liste des villes choisies
    villesSelectionnees = new QListWidget(this);
    layoutTableau->addWidget(villesSelectionnees);

    //Création du bouton pour générer la matrice de temps
    boutonGenererTableau = new QPushButton("Générer le tableau de temps", this);
    boutonGenererTableau->setStyleSheet("background-color: #5d6d7e; font-weight: bold; color : white; border-radius: 5px; min-height: 35px;");
    layoutTableau->addWidget(boutonGenererTableau);

    //Création de la matrice de temps
    matriceTemps = new QTableWidget(this);
    matriceTemps->setEditTriggers(QAbstractItemView::NoEditTriggers); //Pour éviter que l'utilisateur ne puisse saisir dans la matrice
    layoutTableau->addWidget(matriceTemps);

    //les connect des 3 bouutons à leurs actions respectifs
    connect(boutonAjouter, SIGNAL(clicked(bool)), this, SLOT(ajouterVilleListe()));
    connect(boutonSupprimer, SIGNAL(clicked(bool)), this, SLOT(supprimerVilleListe()));
    connect(boutonGenererTableau, SIGNAL(clicked(bool)), this, SLOT(genererTableauTemps()));

    connect(comboTri,     &QComboBox::currentIndexChanged, this, &MainWindow::trierVilles);
    connect(comboRegion,  &QComboBox::currentIndexChanged, this, &MainWindow::filtrerParRegion);

    mettreAJourComboBox();

    QHBoxLayout *layoutChoixOptimal = new QHBoxLayout;
    radioSomme = new QRadioButton("Minimiser la somme des temps", this);
    radioSomme->setChecked(true);
    layoutChoixOptimal->addWidget(radioSomme);

    radioMax = new QRadioButton("Minimiser le temps maximum", this);
    layoutChoixOptimal->addWidget(radioMax);
    layoutTableau->addLayout(layoutChoixOptimal);

    boutonCalculerDepot = new QPushButton("Trouver l'emplacement du dépôt idéal", this);
    boutonCalculerDepot->setStyleSheet("background-color: #7f8c8d; color: white; font-weight: bold; border-radius: 5px; min-height: 35px;");
    layoutTableau->addWidget(boutonCalculerDepot);

    labelResultatDepot = new QLabel("", this);
    labelResultatDepot->setWordWrap(true);
    layoutTableau->addWidget(labelResultatDepot);

    connect(boutonCalculerDepot, SIGNAL(clicked(bool)), this, SLOT(trouverDepotOptimal()));

    // Création du bouton Quitter
    boutonQuitter = new QPushButton("Quitter l'application", this);
    boutonQuitter->setStyleSheet("background-color: red;");
    layoutPrincipal->addWidget(boutonQuitter);

    connect(boutonQuitter, SIGNAL(clicked(bool)), this, SLOT(close()));
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

// Met à jour les 3 ComboBox de villes selon tri et filtre actifs
void MainWindow::mettreAJourComboBox() {

    // Récupération du filtre région actif
    QString regionChoisie = comboRegion->currentText();

    // On filtre les villes selon la région
    std::vector<Ville> villesFiltrees;
    for (const Ville& v : listeVilles) {
        QString r = QString::fromStdString(v.getRegion());
        // "Toutes les régions" → on prend tout
        if (regionChoisie == "Toutes les régions" || r == regionChoisie)
            villesFiltrees.push_back(v);
    }

    // Tri selon le choix
    if (comboTri->currentIndex() == 0) {
        // Tri par nom alphabétique
        std::sort(villesFiltrees.begin(), villesFiltrees.end(),
                  [](const Ville& a, const Ville& b) {
                      return a.getNom() < b.getNom();
                  });
    } else {
        // Tri par population décroissante
        std::sort(villesFiltrees.begin(), villesFiltrees.end(),
                  [](const Ville& a, const Ville& b) {
                      return a.getPopulation() > b.getPopulation();
                  });
    }

    // Vidage et reremplissage des 3 ComboBox
    comboBoxDepart->clear();
    comboBoxArivee->clear();
    comboChoixVille->clear();

    for (const Ville& v : villesFiltrees) {
        QString nom = QString::fromStdString(v.getNom());
        comboBoxDepart->addItem(nom);
        comboBoxArivee->addItem(nom);
        comboChoixVille->addItem(nom);
    }

    // Réinitialisation des index
    comboBoxDepart->setCurrentIndex(-1);
    comboBoxArivee->setCurrentIndex(-1);
    comboChoixVille->setCurrentIndex(-1);
}

void MainWindow::trierVilles() {
    mettreAJourComboBox(); //on met à jour lorsque le tri change
}

void MainWindow::filtrerParRegion() {
    mettreAJourComboBox(); // Le filtre a changé, on met à jour
}

void MainWindow::trouverDepotOptimal() {
    // Réinitialisation du style pour effacer les anciens affichages
    labelResultatDepot->setStyleSheet("color: black; background-color: none; border: none;");

    // 1. Extraction des IDs des villes cibles depuis le QListWidget
    std::vector<unsigned int> villesCibles; //vecteur pour stocker les id des villes sélectionnées
    for (int i = 0; i < villesSelectionnees->count(); ++i) {
        QString nomVilleCible = villesSelectionnees->item(i)->text();

        //on cherche cette ville dans notre liste globale pour récupérer son id
        for (const Ville& v : listeVilles) 
            if (QString::fromStdString(v.getNom()) == nomVilleCible) 
                villesCibles.push_back(v.getId());
        
    }

    // on vérifie que la liste des villes ciblées n'est pas vide
    if (villesCibles.empty()) {
        labelResultatDepot->setText("Erreur : Veuillez ajouter des villes dans la liste pour effectuer le calcul.");
        labelResultatDepot->setStyleSheet("color: #c0392b;");
        return;
    }

    int idMeilleurDepot = -1; // variable pour stocker l'id du meilleur depot
    double meilleurScore = -1.0; // variable pour stocker le score du meilleur depot (soit la somme des temps, soit le temps max)

    //on parcours de tous les sommets pour évaluer chaque ville comme depot candidat
    for (const Ville& depotCandidat : listeVilles) {
        unsigned int idCandidat = depotCandidat.getId();
        double scoreCandidat = 0.0;
        bool cheminImpossible = false;

        // evaluation de la distance du candidat courant vers toutes les cibles
        for (unsigned int idCible : villesCibles) {
            double temps = g->getTemps(idCandidat, idCible);

            //lorsqu'il n'existe pas de chemin,
            if (temps == inf) {
                cheminImpossible = true;    //on marque cette ville comme un candidat impossible
                break; // et on arrête d'évaluer cette ville
            }

            // selon la stratégie choisie par l'utilisateur, on met à jour le score du candidat
            if (radioMax->isChecked()) {
                // minimisation du temps maximum,
                if (temps > scoreCandidat) {
                    scoreCandidat = temps;
                }
            } else {
                //minimisation de la somme des temps
                scoreCandidat += temps;
            }
        }

        if (!cheminImpossible) {           

            // Recherche du minimum dans toutes les villes
            if (meilleurScore == -1.0 || scoreCandidat < meilleurScore) {
                meilleurScore = scoreCandidat;
                idMeilleurDepot = idCandidat;
            }
        }
    }

    //si aucun ville candidate n'est valide (pas de chemin vers au moins une cible),
    if (idMeilleurDepot == -1) {
        labelResultatDepot->setText("Erreur : Aucun dépôt ne peut desservir l'ensemble de ces villes.");
        labelResultatDepot->setStyleSheet("color: #c0392b;");
        return;
    }

    //recuperation du nom de la ville correspondant à l'id optimal
    QString nomMeilleurDepot;
    for (const Ville& v : listeVilles) {
        if (v.getId() == static_cast<unsigned int>(idMeilleurDepot)) {
            nomMeilleurDepot = QString::fromStdString(v.getNom());
        }
    }

    //Conversion des minutes en format heures minutes
    int h = static_cast<int>(meilleurScore) / 60;
    int m = static_cast<int>(meilleurScore) % 60;
    QString texteDuree = (h > 0) ? QString("%1h %2min").arg(h).arg(m) : QString("%1min").arg(m);

    // on affiche le resultat selon la strategie choisie par l'utilisateur
    QString messageFinal;
    if (radioMax->isChecked()) {
        messageFinal = QString("Emplacement optimal : %1\n(Temps maximum : %2)")
        .arg(nomMeilleurDepot).arg(texteDuree);
    } else {
        messageFinal = QString("Emplacement optimal : %1\n(Somme cumulée des temps de trajet : %2)")
                           .arg(nomMeilleurDepot).arg(texteDuree);
    }

    labelResultatDepot->setText(messageFinal);
}

MainWindow::~MainWindow() = default;
