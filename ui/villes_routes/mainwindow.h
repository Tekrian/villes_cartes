#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
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

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};
#endif // MAINWINDOW_H
