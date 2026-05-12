#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Temps de routes"); //Titre de la fenêtre
    setMinimumSize(600, 700);
}

MainWindow::~MainWindow() = default;
