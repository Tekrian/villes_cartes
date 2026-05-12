#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    QWidget *mainWidget; //Le conteneur principal
    QVBoxLayout *layoutPrincipal; // l'objet pour organiser les widgets verticalement
    QLabel *titre; //titre de l'application
    QGroupBox *groupTrajet;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};
#endif // MAINWINDOW_H
