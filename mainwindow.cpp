#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{

    createMenu();
    setWindowTitle("Filmová databáze");
    setWindowIcon(QIcon(":/icons/icon.ico"));
    setFixedSize(700,370);
 //------LOGO--------------
    boxLay = new QVBoxLayout();
    boxLay->setAlignment(Qt::AlignTop|Qt::AlignCenter);
    widget = new QWidget();

    QPixmap p(":/icons/filmLogo.gif");
    logo = new QLabel();
    logo->setPixmap(p);
    boxLay->addWidget(logo);
//-------Vyber a info------
    infoFilmLayout = new QHBoxLayout();
    infoFilmLabel = new QLabel("Výběr filmu:");
    infoFilmBut = new QPushButton("Zobrazit info");
    comboBox = new QComboBox();
    infoFilmLabel->setFont(QFont("Times New Roman",14,87,0));
    infoFilmLayout->addWidget(infoFilmLabel);
    comboBox->addItem("Hosi od bobri rekz 2");
    comboBox->setFixedSize(410,28);
    comboBox->setFont(QFont("Times New Roman",11));
    infoFilmLayout->addWidget(comboBox);
    infoFilmBut->setFixedSize(110,30);
    infoFilmBut->setFont(QFont("Times New Roman",11));
    infoFilmLayout->addWidget(infoFilmBut);
    infoFilmLayout->setContentsMargins(0,15,0,0);
    boxLay->addLayout(infoFilmLayout);

//---------Tlacitka-----------

    filmNoteExitLay = new QHBoxLayout();
    filmNoteExitLay->setContentsMargins(0,25,0,0);
    addFilmBut = new QPushButton();
    addNoteBut = new QPushButton();
    exitBut = new QPushButton();
    addFilmBut->setIcon(QIcon(":/icons/addfilmIcon.png"));
    addFilmBut->setIconSize(QSize(100,70));
    addFilmBut->setFixedSize(150,80);
    addFilmBut->setToolTip("Přidat film");
    connect(addFilmBut,SIGNAL(clicked(bool)),this,SLOT(filmAdding()));
    filmNoteExitLay->addWidget(addFilmBut);
    addNoteBut->setIcon(QIcon(":/icons/addNoteBut.png"));
    addNoteBut->setIconSize(QSize(100,60));
    addNoteBut->setFixedSize(150,80);
    addNoteBut->setToolTip("Přidat komentář");
    filmNoteExitLay->addWidget(addNoteBut);
    exitBut->setIcon(QIcon(":/icons/exitIcon.png"));
    exitBut->setIconSize(QSize(100,60));
    exitBut->setFixedSize(150,80);
    exitBut->setToolTip("Odejit");
    connect(exitBut,SIGNAL(clicked(bool)),this,SLOT(close()));
    filmNoteExitLay->addWidget(exitBut);

    boxLay->addLayout(filmNoteExitLay);
    widget->setLayout(boxLay);
    setCentralWidget(widget);
}

void MainWindow::createMenu(){
    fileMenu = new QMenu("Nápověda");
    about = new QAction("O programu",this);
    fileMenu->addAction(about);
    connect(about,SIGNAL(triggered(bool)),this,SLOT(aboutProgram()));
    menuBar()->addMenu(fileMenu);

}

void MainWindow::aboutProgram(){
    mb = new QMessageBox();
    mb->setText("Projekt Filmová databáze do předmětu URO\n"
                "Zpracoval Miroslav Kovář - KOV0216\n"
                "Akademický rok 2015/2016");
    mb->setIcon(QMessageBox::Information);
    mb->setWindowIcon(QIcon(":/icons/icon.ico"));
    mb->show();
}

void MainWindow::filmAdding(){
    mw = new QMainWindow();
    widget2 = new QWidget();
    vboxlay2 = new QVBoxLayout();
    filmNameLE = new QLineEdit();
    hboxlay2 = new QHBoxLayout();
    yearLengthDirect = new QGridLayout();
    mw->setWindowTitle("Přidat film");
    mw->setWindowIcon(QIcon(":/icons/icon.ico"));
    mw->resize(400,400);
    filmNameLabel = new QLabel("Název filmu");
    filmNameLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    filmNameLabel->setFont(QFont("",9));
    vboxlay2->setAlignment(Qt::AlignTop);
    vboxlay2->addWidget(filmNameLabel);

    filmNameLE->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    vboxlay2->addWidget(filmNameLE);
//------------Zanr------------------------

    QString genre[] = {"Horor","Komedie","Sci-fi","Drama","Akcni","Kresleny",
                       "Romanticky","Western","Thriller","Hudebni"};
    genre_size = sizeof(genre)/ sizeof(QString);
    genreLay = new QGridLayout();
    genreCH = new QList<QCheckBox*>();
    int row = 0;
    for(int i = 0; i<genre_size;i++){
        int col = (i < (genre_size / 2)) ? i : i - (genre_size / 2);
        if(i == (genre_size / 2)) row++;
        ch = new QCheckBox(genre[i]);
        genreCH->append(ch);
        genreLay->addWidget(ch,row,col);
        ch->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    }

    vboxlay2->addLayout(genreLay);
//-----------Rok,Delka,Rezie,Zeme--------------
    yearLengthDirect->setContentsMargins(0,5,0,0);
    yearLabel = new QLabel("Rok filmu");
    lengthLabel = new QLabel("Délka filmu");
    directorLabel = new QLabel("Režie");
    countryLabel = new QLabel("Původ");
    filmDirector = new QLineEdit();
    filmCountry = new QLineEdit();
    yearLabel->setFont(QFont("",9));
    lengthLabel->setFont(QFont("",9));
    directorLabel->setFont(QFont("",9));
    countryLabel->setFont(QFont("",9));

    filmYear = new QSpinBox();
    filmLength = new QLineEdit();
    filmYear->setMinimum(1920);
    filmYear->setMaximum(2016);
    filmLength->setFixedWidth(50);
    filmCountry->setFixedWidth(100);

    yearLengthDirect->addWidget(yearLabel,0,0);
    yearLengthDirect->addWidget(filmYear,1,0);
    yearLengthDirect->addWidget(lengthLabel,0,1);
    yearLengthDirect->addWidget(filmLength,1,1);
    yearLengthDirect->addWidget(directorLabel,0,2);
    yearLengthDirect->addWidget(filmDirector,1,2);
    yearLengthDirect->addWidget(countryLabel,0,3);
    yearLengthDirect->addWidget(filmCountry,1,3);
    vboxlay2->addLayout(yearLengthDirect);
//--------------POznamka-------------------
    filmNote = new QTextEdit();
    noteLabel = new QLabel("Obsah filmu");
    vboxlay2->addWidget(noteLabel);
    vboxlay2->addWidget(filmNote);
    widget2->setLayout(vboxlay2);

//---------tlacitka--------------
    filmButLay = new QHBoxLayout();
    filmCloseBut = new QPushButton("Zrušit");
    filmCLEAREBut = new QPushButton("Vymazat");
    filmADDBut = new QPushButton("Přidat");
    filmCloseBut->setFixedHeight(40);
    filmADDBut->setFixedHeight(40);
    filmCLEAREBut->setFixedHeight(40);

    filmButLay->addWidget(filmCloseBut);
    filmButLay->addWidget(filmCLEAREBut);
    connect(filmCLEAREBut,SIGNAL(clicked(bool)),this,SLOT(cleareFilm()));
    filmButLay->addWidget(filmADDBut);
    vboxlay2->addLayout(filmButLay);
    mw->setCentralWidget(widget2);
    mw->show();

}
void MainWindow::cleareFilm(){
//    q = new QMessageBox;
//    q->QMessageBox::question(this,"Warning","Are you sure?",QMessageBox::Yes|
//                              QMessageBox::No);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Upozorneni");
    msgBox.setText("Opravdu chcete vse smazat?");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setWindowIcon(QIcon(":/icons/icon.ico"));
    if(msgBox.exec() == QMessageBox::Yes){
        filmNameLE->clear();
        filmNameLE->setFocus();
        for(int i = 0;i<genreCH->size();i++){
            genreCH->at(i)->setChecked(false);
        }

        filmYear->setValue(1920);
        filmLength->clear();
        filmDirector->clear();
        filmCountry->clear();
        filmNote->clear();
    }


}

MainWindow::~MainWindow()
{

}