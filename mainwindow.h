#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMenuBar>
#include <QCheckBox>
#include <QSpinBox>
#include <QStringList>
#include <QDebug>
#include <QTextEdit>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = 0);


    ~MainWindow();


private:
    QMenu* fileMenu;
    QAction* about;
    QMainWindow* aboutWindow;
    QGridLayout* gridLay;
    QMessageBox* mb;
    QLabel* logo;
    QLabel* infoFilmLabel;
    QWidget* widget;
    QVBoxLayout* boxLay;
    QHBoxLayout* infoFilmLayout;
    QComboBox* comboBox;
    QPushButton* infoFilmBut;
    QPushButton* addFilmBut;
    QHBoxLayout* filmNoteExitLay;
    QPushButton* addNoteBut;
    QPushButton* exitBut;

//-------Pridat film----------
    QMainWindow* mw;
    QWidget* widget2;
    QVBoxLayout* vboxlay2;
    QHBoxLayout* hboxlay2;
    QLabel* filmNameLabel;
    QLineEdit* filmNameLE;
    QGridLayout* genreLay;
    QList<QCheckBox*>* genreCH;
    QLineEdit* filmLength;
    QSpinBox* filmYear;
    QGridLayout* yearLengthDirect;
    QLabel* yearLabel;
    QLabel* lengthLabel;
    QLabel* directorLabel;
    QLabel* countryLabel;
    QLabel* noteLabel;
    QTextEdit* filmNote;
    QLineEdit* filmDirector;
    QLineEdit* filmCountry;
    QPushButton* filmADDBut;
    QPushButton* filmCLEAREBut;
    QPushButton* filmCloseBut;
    QHBoxLayout* filmButLay;
    QCheckBox* ch;
    int genre_size;
    QMessageBox* q;






public slots:





private slots:
    void createMenu();
    void aboutProgram();
    void filmAdding();
    void cleareFilm();





};

#endif // MAINWINDOW_H
