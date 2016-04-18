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
#include <QFile>
#include <QDate>
#include <QTime>
#include <QRadioButton>
#include <QGroupBox>


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

    bool isFilled();
    void showMSG(QString msg);
//-------přidat komentář------
    QMainWindow* comMainWin;
    QVBoxLayout* vNoteLay;
    QHBoxLayout* hGenderLay;
    QHBoxLayout* hButLay;
    QComboBox* combobox2;
    QWidget* noteWIDG;
    QLabel* nickLabel;
    QLabel* filmLabel;
    QLineEdit* nickLE;
    QLabel* mailLabel;
    QLineEdit* mailLE;
    QLabel* genderLabel;
    QList<QRadioButton*>*gRad;
    QRadioButton* r;
    int gender_size;
    QGridLayout*g;
    QLabel* commentLabel;
    QTextEdit* commentTE;
    QPushButton* comCloseBut;
    QPushButton* comCLearBut;
    QPushButton* comAddBut;
    bool isFilledComment();

    void showComMSG(QString s);

//-----Info o filmu--------
    QMainWindow* infoMW;
    QVBoxLayout* vInfoLay;
    QWidget* infoWIDG;
    QHBoxLayout* hInfoLay;
    QLabel* extFilm;
    QGridLayout* gridLay2;

//--------- Komentare---------
    QMainWindow* noteWindow;
    QVBoxLayout* vComLay;
    QHBoxLayout*hComLay;
    QWidget* comWidg;





    QList<QStringList>* listFIlms;
    void aboutFilm(QStringList filmInfo);
    void aboutComment(QStringList CovCOmmmentInfo);
    void comboInsert();
    void comboInsert2();








public slots:





private slots:
    void createMenu();
    void aboutProgram();
    void filmAdding();
    void cleareFilm();
    void closeFilm();
    void addFilm();
    void commentAdding();
    void clearComment();
    void addComment();
    void closeComment();
    void LoadComment();
    void LoadFilm();





};

#endif // MAINWINDOW_H
