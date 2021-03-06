#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
{

    boxLay = new QVBoxLayout();
    widget = new QWidget();
    QPixmap p(":/icons/filmLogo.gif");
    logo = new QLabel();
    infoFilmLayout = new QHBoxLayout();
    infoFilmLabel = new QLabel("Výběr filmu:");
    infoFilmBut = new QPushButton("Zobrazit info");
    comboBox = new QComboBox();
    filmNoteExitLay = new QHBoxLayout();
    filmNoteExitLay->setContentsMargins(0,25,0,0);
    addFilmBut = new QPushButton();
    addNoteBut = new QPushButton();
    exitBut = new QPushButton();
    //------Hlavni okno-------
    createMenu();
    setWindowTitle("Filmová databáze");
    setWindowIcon(QIcon(":/icons/icon.ico"));
    setFixedSize(700,370);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::WindowTitleHint);

    //------LOGO--------------
    boxLay->setAlignment(Qt::AlignTop|Qt::AlignCenter);
    logo->setPixmap(p);
    boxLay->addWidget(logo);

    //------Vyber a info------
    infoFilmLabel->setFont(QFont("Times New Roman",14,87,0));
    infoFilmLayout->addWidget(infoFilmLabel);
    comboInsert();
    comboBox->setFixedSize(410,28);
    comboBox->setFont(QFont("Times New Roman",11));
    infoFilmLayout->addWidget(comboBox);
    infoFilmBut->setFixedSize(110,30);
    infoFilmBut->setFont(QFont("Times New Roman",11));
    infoFilmLayout->addWidget(infoFilmBut);
    connect(infoFilmBut,SIGNAL(clicked(bool)),this,SLOT(LoadFilm()));
    infoFilmLayout->setContentsMargins(0,15,0,0);
    boxLay->addLayout(infoFilmLayout);

    //---------Tlacitka--------
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
    connect(addNoteBut,SIGNAL(clicked(bool)),this,SLOT(commentAdding()));
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
    mb->setText("Projekt: Filmová databáze do předmětu URO\n"
                "Zpracoval: Miroslav Kovář - KOV0216\n"
                "Akademický rok 2015/2016");
    mb->setIcon(QMessageBox::Information);
    mb->setWindowIcon(windowIcon());
    mb->show();
}

void MainWindow::filmAdding(){
    mw = new QMainWindow();
    widget2 = new QWidget();
    vboxlay2 = new QVBoxLayout();
    filmNameLE = new QLineEdit();
    hboxlay2 = new QHBoxLayout();
    yearLengthDirect = new QGridLayout();
    filmNameLabel = new QLabel("Název filmu");
    genreLay = new QGridLayout();
    genreCH = new QList<QCheckBox*>();
    yearLabel = new QLabel("Rok filmu");
    lengthLabel = new QLabel("Délka filmu");
    directorLabel = new QLabel("Režie");
    countryLabel = new QLabel("Původ");
    filmDirector = new QLineEdit();
    filmCountry = new QLineEdit();
    filmYear = new QSpinBox();
    filmLength = new QLineEdit();
    filmNote = new QTextEdit();
    noteLabel = new QLabel("Obsah filmu");
    filmButLay = new QHBoxLayout();
    filmCloseBut = new QPushButton("Zavřít");
    filmCLEAREBut = new QPushButton("Vymazat");
    filmADDBut = new QPushButton("Přidat");

    //-----Hlavni okno-----------
    mw->setWindowTitle("Přidat film");
    mw->setWindowIcon(windowIcon());
    mw->resize(400,400);

    //-----Nazev filmu-----------
    filmNameLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    vboxlay2->setAlignment(Qt::AlignTop);
    vboxlay2->addWidget(filmNameLabel);
    filmNameLE->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    vboxlay2->addWidget(filmNameLE);

    //------------Zanr-----------
    QString genre[] = {"Horor","Komedie","Sci-fi","Drama","Akční","Kreslený",
                       "Romantický","Dobrodružný","Thriller","Rodinný"};
    genre_size = sizeof(genre)/ sizeof(QString);
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
    filmLength->setValidator(new QIntValidator(0,999,this));
    filmYear->setMinimum(1920);
    filmYear->setMaximum(QDate().currentDate().toString("yyyy").toInt());
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

    //--------------Poznamka---------
    vboxlay2->addWidget(noteLabel);
    vboxlay2->addWidget(filmNote);
    widget2->setLayout(vboxlay2);

    //---------Tlacitka--------------
    filmCloseBut->setFixedHeight(40);
    filmADDBut->setFixedHeight(40);
    filmCLEAREBut->setFixedHeight(40);
    filmButLay->addWidget(filmCloseBut);
    connect(filmCloseBut,SIGNAL(clicked(bool)),this,SLOT(closeFilm()));
    filmButLay->addWidget(filmCLEAREBut);
    connect(filmCLEAREBut,SIGNAL(clicked(bool)),this,SLOT(cleareFilm()));
    filmButLay->addWidget(filmADDBut);
    connect(filmADDBut,SIGNAL(clicked(bool)),this,SLOT(addFilm()));
    vboxlay2->addLayout(filmButLay);
    mw->setCentralWidget(widget2);
    mw->show();
}
void MainWindow::cleareFilm(){

    QMessageBox added;
    if((filmNameLE->text().length()|| filmLength->text().length()||
        filmDirector->text().length()||filmCountry->text().length()||
        filmNote->document()->toPlainText().length())==0){
        added.setText("Neni co mazat!");
        added.setIcon(QMessageBox::Warning);
        added.setWindowIcon(windowIcon());
        added.exec();
    }
    else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozorneni");
        msgBox.setText("Opravdu chcete vse smazat?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setWindowIcon(windowIcon());
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
}
void MainWindow::closeFilm(){
    QMessageBox closeMsg;
    closeMsg.setWindowTitle("Upozornění");
    closeMsg.setText("Opravdu chcete odejít?");
    closeMsg.setWindowIcon(windowIcon());
    closeMsg.setIcon(QMessageBox::Question);
    closeMsg.setStandardButtons(QMessageBox::Yes);
    closeMsg.addButton(QMessageBox::No);
    if(closeMsg.exec()==QMessageBox::Yes){
        mw->close();
    }
}
void MainWindow::addFilm()
{
    if(!isFilled())
        return;
    QString str = "";
    str.append(filmNameLE->text()+ "\t" );
    for(int i = 0;i<genreCH->size();i++){
        QString tmp = (genreCH->at(i)->checkState() == Qt::CheckState::Checked) ? "1" : "0";
        str.append(tmp + "\t");
    }
    str.append(QString::number(filmYear->value()) + "\t");
    str.append(filmLength->text() + "\t");
    str.append(filmDirector->text() + "\t");
    str.append(filmCountry->text().toUpper() + "\t");
    str.append(filmNote->document()->toPlainText() + "\n");

    QFile file("FIlmy.txt");
    QTextStream ts(&file);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        return;
    }
    ts.setCodec("UTF-8");
    ts << str;
    QMessageBox added;
    added.setText("Film byl úspěšně přidán!");
    added.setIcon(QMessageBox::Information);
    added.setWindowIcon(windowIcon());
    comboBox->addItem(filmNameLE->text());
    added.exec();
}

void MainWindow::commentAdding()
{
    comMainWin = new QMainWindow();
    combobox2 = new QComboBox();
    comboInsert2();
    filmLabel = new QLabel("Název filmu");
    vNoteLay = new QVBoxLayout();
    hGenderLay = new QHBoxLayout();
    noteWIDG = new QWidget();
    nickLabel = new QLabel("Název nicku");
    nickLE = new QLineEdit();
    mailLabel = new QLabel("E-mail");
    mailLE = new QLineEdit();
    gRad = new QList<QRadioButton*>();
    g = new QGridLayout();
    genderLabel = new QLabel("Pohlaví");
    hButLay = new QHBoxLayout();
    comCloseBut = new QPushButton("Zavřít");
    comCLearBut = new QPushButton("Vymazat");
    comAddBut = new QPushButton("Přidat");

    //-------hlavni okno---------
    hGenderLay->setAlignment(Qt::AlignLeft);
    g->setAlignment(Qt::AlignLeft);
    combobox2->model()->sort(0);
    vNoteLay->setAlignment(Qt::AlignTop);
    comMainWin->setWindowTitle("Přidat komentář");
    comMainWin->setWindowIcon(windowIcon());
    comMainWin->resize(350,300);

    //-----Vzber filmu, Nick, mail---
    vNoteLay->addWidget(filmLabel);
    vNoteLay->addWidget(combobox2);
    vNoteLay->addWidget(nickLabel);
    vNoteLay->addWidget(nickLE);
    vNoteLay->addWidget(mailLabel);
    vNoteLay->addWidget(mailLE);

    //--------Pohlavi-------------
    vNoteLay->addWidget(genderLabel);
    QString sex[] = {"Muž","Žena"};
    gender_size = sizeof(sex)/sizeof(QString);
    int col = 0;
    for(int i = 0; i<gender_size;i++){
        r = new QRadioButton(sex[i]);
        col++;
        gRad->append(r);
        hGenderLay->addWidget(r);
    }
    vNoteLay->addLayout(hGenderLay);

    //------------Komentar------------
    commentLabel = new QLabel("Komentář");
    commentTE = new QTextEdit();
    vNoteLay->addWidget(commentLabel);
    vNoteLay->addWidget(commentTE);

    //---------Tlacitka-----------
    comCloseBut->setFixedHeight(40);
    comCLearBut->setFixedHeight(40);
    comAddBut->setFixedHeight(40);
    connect(comCloseBut,SIGNAL(clicked(bool)),this,SLOT(closeComment()));
    hButLay->addWidget(comCloseBut);
    connect(comCLearBut,SIGNAL(clicked(bool)),this,SLOT(clearComment()));
    hButLay->addWidget(comCLearBut);
    connect(comAddBut,SIGNAL(clicked(bool)),this,SLOT(addComment()));
    hButLay->addWidget(comAddBut);
    vNoteLay->addLayout(hButLay);
    noteWIDG->setLayout(vNoteLay);
    comMainWin->setCentralWidget(noteWIDG);
    comMainWin->show();
}

void MainWindow::clearComment()
{
    if((nickLE->text().length()||mailLE->text().length()||
        gRad->at(0)->isChecked()||gRad->at(1)->isChecked()||
        commentTE->document()->toPlainText().length())==0){
        QMessageBox added;
        added.setText("Neni co mazat!");
        added.setIcon(QMessageBox::Warning);
        added.setWindowIcon(windowIcon());
        added.exec();
    }
    else{
        QMessageBox clrscr;
        clrscr.setWindowTitle("Upozorneni");
        clrscr.setText("Opravdu chcete vse smazat?");
        clrscr.setIcon(QMessageBox::Question);
        clrscr.setStandardButtons(QMessageBox::Yes);
        clrscr.addButton(QMessageBox::No);
        clrscr.setDefaultButton(QMessageBox::No);
        clrscr.setWindowIcon(windowIcon());
        if(clrscr.exec() == QMessageBox::Yes){
            nickLE->clear();
            nickLE->setFocus();
            mailLE->clear();
            for(int i = 0;i<gRad->size();i++){
                gRad->at(i)->setAutoExclusive(false);
                gRad->at(i)->setChecked(false);
                gRad->at(i)->setAutoExclusive(true);
            }
            commentTE->clear();
        }
    }
}

void MainWindow::addComment()
{
    QDate d;
    QTime t;
    if(!isFilledComment())
        return;

    QString comStr = "";
    comStr.append(combobox2->currentText() + "\t");
    comStr.append(nickLE->text() + "\t");
    comStr.append(d.currentDate().toString("yyyy-MM-dd") + ", "
                  + t.currentTime().toString("hh:mm:ss") + "\t");
    comStr.append(mailLE->text() + "\t");
    for(int i = 0; i<gRad->size();i++){
        if(gRad->at(i)->isChecked()){
            comStr.append(gRad->at(i)->text() + "\t");
        }
    }
    comStr.append(commentTE->document()->toPlainText()+"\n");

    QFile comFile("Komentare.txt");
    QTextStream comTS(&comFile);
    if (!comFile.open(QIODevice::Append | QIODevice::Text))
    {
        return;
    }
    comTS.setCodec("UTF-8");
    comTS << comStr;
    comFile.close();

    QMessageBox comMB;
    comMB.setText("Komentář byl úsěšně přidán");
    comMB.setIcon(QMessageBox::Information);
    comMB.setWindowIcon(windowIcon());
    comMB.exec();
}

void MainWindow::closeComment()
{
    QMessageBox clrscr;
    clrscr.setWindowTitle("Upozorneni");
    clrscr.setText("Opravdu chcete odejít?");
    clrscr.setIcon(QMessageBox::Question);
    clrscr.setStandardButtons(QMessageBox::Yes);
    clrscr.addButton(QMessageBox::No);
    clrscr.setDefaultButton(QMessageBox::No);
    clrscr.setWindowIcon(windowIcon());
    if(clrscr.exec() == QMessageBox::Yes){
        comMainWin->close();
    }
}

void MainWindow::LoadComment()
{
    QFile komentar("Komentare.txt");
     QList<QStringList>infoComment;
    if(!komentar.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox mb;
        mb.setWindowTitle("Upozornění");
        mb.setText("K tomuto filmu zatím není přidán žádný komentář!");
        mb.setWindowIcon(windowIcon());
        mb.setIcon(QMessageBox::Warning);
        mb.exec();

        return;
    }
    while(!komentar.atEnd()){
        QString line = komentar.readLine();
        QStringList st2;
        st2 = line.split("\t");
        infoComment.append(st2);
    }
    komentar.close();

    QMainWindow* comWindow = new QMainWindow();
    QVBoxLayout* vvb = new QVBoxLayout();
    QWidget* wdg = new QWidget();
    comWindow->setWindowIcon(windowIcon());
    comWindow->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    vvb->setAlignment(Qt::AlignTop);
    bool isExist = false;
    for(int i = 0;i<infoComment.size();i++){
        if(comboBox->currentText() == infoComment.at(i).at(0)){
            comWindow->setWindowTitle(infoComment.at(i).at(0));
            QHBoxLayout* hvb = new QHBoxLayout();
            QGroupBox* nick = new QGroupBox("Nick");
            QGroupBox* dateTime = new QGroupBox("Datum a čas");
            QGroupBox* mail = new QGroupBox("E-mail");
            QGroupBox* gender = new QGroupBox("Pohlaví");
            QGroupBox* comment = new QGroupBox("Komentář");
            QLabel* nick2 = new QLabel();
            QLabel* dateTime2 = new QLabel();
            QLabel* mail2 = new QLabel();
            QLabel* gender2 = new QLabel();
            QLabel* comment2 = new QLabel();
            QVBoxLayout* nickLay = new QVBoxLayout();
            QVBoxLayout* dateTimeLay = new QVBoxLayout();
            QVBoxLayout* mailLay = new QVBoxLayout();
            QVBoxLayout* genderLay = new QVBoxLayout();
            QVBoxLayout* commentLay = new QVBoxLayout();
            comment2->setWordWrap(true);
            commentLay->setAlignment(Qt::AlignTop);
            comment->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

            nick2->setText(infoComment.at(i).at(1));
            dateTime2->setText(infoComment.at(i).at(2));
            mail2->setText(infoComment.at(i).at(3));
            gender2->setText(infoComment.at(i).at(4));
            comment2->setText(infoComment.at(i).at(5));

            nick->setStyleSheet("font-weight:bold");
            nick2->setStyleSheet("font-weight:normal");
            dateTime->setStyleSheet("font-weight:bold");
            dateTime2->setStyleSheet("font-weight:normal");
            mail->setStyleSheet("font-weight:bold");
            mail2->setStyleSheet("font-weight:normal");
            gender->setStyleSheet("font-weight:bold");
            gender2->setStyleSheet("font-weight:normal");
            comment->setStyleSheet("font-weight:bold");
            comment2->setStyleSheet("font-weight:normal");
            //---Nick v groupBoxu---------
            nick->setLayout(nickLay);
            nickLay->addWidget(nick2);
            hvb->addWidget(nick);
            //---Datum a cas v Group------
            dateTime->setLayout(dateTimeLay);
            dateTimeLay->addWidget(dateTime2);
            hvb->addWidget(dateTime);
            //---Mail v Group-------------
            mail->setLayout(mailLay);
            mailLay->addWidget(mail2);
            hvb->addWidget(mail);
            //---Pohlavi v Group----------
            gender->setLayout(genderLay);
            genderLay->addWidget(gender2);
            hvb->addWidget(gender);
            vvb->addLayout(hvb);
            //---Komentar v Group--------
            comment->setLayout(commentLay);
            commentLay->addWidget(comment2);
            vvb->addWidget(comment);
            isExist = true;
        }
    }
    QPushButton* endCom = new QPushButton("Zavřít");
    connect(endCom,SIGNAL(clicked(bool)),comWindow,SLOT(close()));
    endCom->setFixedHeight(40);
    vvb->addWidget(endCom);
    if(!isExist){
        QMessageBox mb;
        mb.setWindowTitle("Upozornění");
        mb.setText("K tomuto filmu zatím není přidán žádný komentář!");
        mb.setWindowIcon(windowIcon());
        mb.setIcon(QMessageBox::Warning);
        mb.exec();
        return;
    }
    wdg->setLayout(vvb);
    comWindow->setCentralWidget(wdg);
    comWindow->show();
}

void MainWindow::aboutFilm(QStringList filmInfo)
{
    infoMW = new QMainWindow();
    vInfoLay = new QVBoxLayout();
    hInfoLay = new QHBoxLayout();
    infoWIDG = new QWidget();
    QPushButton* entryComment = new QPushButton("Zobrazit komentář");
    QPushButton* cancelAboutFilm = new QPushButton("Zavřít");
    QPushButton* deleteFilmBut = new QPushButton("Odstranit film");
    QHBoxLayout* hBut = new QHBoxLayout();
    QGroupBox* genre = new QGroupBox("Žánr");
    QGroupBox* film = new QGroupBox("Název filmu");
    QGroupBox* year = new QGroupBox("Rok filmu");
    QGroupBox* length = new QGroupBox("Délka filmu");
    QGroupBox* director = new QGroupBox("Režie");
    QGroupBox* country = new QGroupBox("Původ filmu");
    QGroupBox* note = new QGroupBox("Obsah filmu");
    QVBoxLayout* filmLay = new QVBoxLayout();
    QVBoxLayout* genreLay = new QVBoxLayout();
    QVBoxLayout* yearLay = new QVBoxLayout();
    QVBoxLayout* lenLay = new QVBoxLayout();
    QVBoxLayout* dirLay = new QVBoxLayout();
    QVBoxLayout* countLay = new QVBoxLayout();
    QVBoxLayout* noteLay = new QVBoxLayout();
    film2 = new QLabel();
    QLabel* genre2 = new QLabel();
    QLabel* length2 = new QLabel();
    QLabel* year2 = new QLabel();
    QLabel* director2 = new QLabel();
    QLabel* country2 = new QLabel();
    QLabel* note2 = new QLabel();
    noteLay->setAlignment(Qt::AlignTop);
    infoMW->setWindowTitle("Info o filmu");
    infoMW->setWindowIcon(windowIcon());
    infoMW->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    vInfoLay->setAlignment(Qt::AlignTop);
    note->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    film->setStyleSheet("font-weight:bold");
    film2->setStyleSheet("font-weight:normal");
    genre->setStyleSheet("font-weight:bold");
    genre2->setStyleSheet("font-weight:normal");
    length->setStyleSheet("font-weight:bold");
    length2->setStyleSheet("font-weight:normal");
    year->setStyleSheet("font-weight:bold");
    year2->setStyleSheet("font-weight:normal");
    director->setStyleSheet("font-weight:bold");
    director2->setStyleSheet("font-weight:normal");
    country->setStyleSheet("font-weight:bold");
    country2->setStyleSheet("font-weight:normal");
    note->setStyleSheet("font-weight:bold");
    note2->setStyleSheet("font-weight:normal");
    note2->setWordWrap(true);
    //-------Vypis nazvu filmu-----
    film2->setText(comboBox->currentText());
    //-------Vypis zanru---------
    QString genres;
    for(int i = 1;i<11;i++){
        if(filmInfo.at(i) == "1"){
            if(i == 1)
                genres +="Horor, ";
            if(i == 2)
                genres +="Komedie, ";
            if(i == 3)
                genres +="Sci-fi, ";
            if(i == 4)
                genres +="Drama, ";
            if(i == 5)
                genres +="Akční, ";
            if(i == 6)
                genres +="Kreslený, ";
            if(i == 7)
                genres +="Romatický, ";
            if(i == 8)
                genres +="Dobrodružný, ";
            if(i == 9)
                genres +="Thriller, ";
            if(i == 10)
                genres +="Rodinný, ";
        }
    }
    QString newGenres;
    for(int i = 0;i<genres.length()-2;i++){
        newGenres +=genres[i];
    }
    genre2->setText(newGenres);
    //------Rok,Delka,Rezie,Puvod,Obsah---
    year2->setText(filmInfo.at(11));
    length2->setText(filmInfo.at(12) + " min");
    director2->setText(filmInfo.at(13));
    country2->setText(filmInfo.at(14));
    note2->setText(filmInfo.at(15));

    film->setLayout(filmLay);
    filmLay->addWidget(film2);
    vInfoLay->addWidget(film);

    genre->setLayout(genreLay);
    genreLay->addWidget(genre2);
    vInfoLay->addWidget(genre);

    year->setLayout(yearLay);
    yearLay->addWidget(year2);
    hInfoLay->addWidget(year);

    length->setLayout(lenLay);
    lenLay->addWidget(length2);
    hInfoLay->addWidget(length);

    director->setLayout(dirLay);
    dirLay->addWidget(director2);
    hInfoLay->addWidget(director);

    country->setLayout(countLay);
    countLay->addWidget(country2);
    hInfoLay->addWidget(country);
    vInfoLay->addLayout(hInfoLay);

    note->setLayout(noteLay);
    noteLay->addWidget(note2);
    vInfoLay->addWidget(note);

    //--------------tlacitka-------------
    cancelAboutFilm->setFixedHeight(40);
    deleteFilmBut->setFixedHeight(40);
    entryComment->setFixedHeight(40);
    connect(cancelAboutFilm,SIGNAL(clicked(bool)),infoMW,SLOT(close()));
    connect(entryComment,SIGNAL(clicked(bool)),this,SLOT(LoadComment()));
    connect(deleteFilmBut,SIGNAL(clicked(bool)),this,SLOT(filmDelete()));
    hBut->addWidget(cancelAboutFilm);
    hBut->addWidget(deleteFilmBut);
    hBut->addWidget(entryComment);
    vInfoLay->addLayout(hBut);

    infoWIDG->setLayout(vInfoLay);
    infoMW->setCentralWidget(infoWIDG);
    infoMW->show();
}

void MainWindow::comboInsert()
{
    comboBox->clear();
    QFile comboFilm("Filmy.txt");
    if(!comboFilm.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QList<QStringList> filmy;
    while(!comboFilm.atEnd()){
        QString line = comboFilm.readLine();
        filmy.append(line.split("\t"));
    }
    comboFilm.close();

    for(int i = 0;i<filmy.size(); i++){
        comboBox->addItem(filmy.at(i).at(0));
        comboBox->model()->sort(0);
    }
    comboBox->model()->sort(0);
}

void MainWindow::comboInsert2()
{
    combobox2->clear();
    QFile comboFilm("Filmy.txt");
    if(!comboFilm.open(QFile::ReadOnly | QFile::Text)){
        return;
    }
    QList<QStringList> filmy;
    while(!comboFilm.atEnd()){
        QString line = comboFilm.readLine();
        filmy.append(line.split("\t"));
    }
    comboFilm.close();

    for(int i = 0;i<filmy.size(); i++){
        combobox2->addItem(filmy.at(i).at(0));
    }
}

MainWindow::~MainWindow()
{

}

bool MainWindow::isFilled()
{
    if(filmNameLE->text().length() == 0){
        showMSG("Nazev filmu");
        return false;
    }
    bool isChecked = false;
    for(int i = 0 ;i<genreCH->size();i++){

        if(genreCH->at(i)->checkState() == Qt::Checked){
            isChecked = true;
        }
    }
    if(!isChecked){
        showMSG("Žánr");
        return false;
    }
    if(filmLength->text().length() == 0){
        showMSG("Délka filmu");
        return false;
    }
    if(filmDirector->text().length() == 0){
        showMSG("Režie");
        return false;
    }
    if(filmCountry->text().length() == 0){
        showMSG("Původ");
        return false;
    }
    if(filmNote->document()->toPlainText().length() == 0){
        showMSG("Obsah filmu");
        return false;
    }

    return true;
}

void MainWindow::showMSG(QString msg)
{
    QMessageBox mb;
    mb.setText("Nevyplnil jsi pole '" + msg +"'");
    mb.setWindowIcon(windowIcon());
    mb.setIcon(QMessageBox::Warning);
    mb.exec();
}

bool MainWindow::isFilledComment()
{
    if(nickLE->text().length()==0){
        showComMSG("Název nicku");
        return false;
    }
    if(mailLE->text().length()==0){
        showComMSG("E-mail");
        return false;
    }
    bool ischecked = false;
    for(int i = 0;i<gRad->size();i++){
        if(gRad->at(i)->isChecked())
            ischecked = true;

    }
    if(!ischecked){
        showComMSG("Pohlavi");
        return false;
    }

    if(commentTE->document()->toPlainText() == 0){
        showComMSG("Komentář");
        return false;
    }

    return true;
}

void MainWindow::showComMSG(QString s)
{
    QMessageBox msgCom;
    msgCom.setText("Nevyplnil jsi pole '" + s +"'");
    msgCom.setWindowIcon(windowIcon());
    msgCom.setIcon(QMessageBox::Warning);
    msgCom.exec();
}

void MainWindow::LoadFilm()
{
    QFile films ("Filmy.txt");
    QString film = comboBox->currentText();
    listFIlms = new QList<QStringList>();
    if(!films.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox mb;
        mb.setWindowTitle("Upozornění");
        mb.setText("Nebyl zatím přidán žádný film!");
        mb.setWindowIcon(windowIcon());
        mb.setIcon(QMessageBox::Warning);
        mb.exec();
        return;
    }
    while(!films.atEnd()){
        QString line = films.readLine();
        QStringList st;
        st = line.split("\t");
        listFIlms->append(st);
    }
    films.close();
    bool isExistIHope = false;
    for(int i =0;i<listFIlms->size();i++){
        if(film == listFIlms->at(i).at(0)){
            aboutFilm(listFIlms->at(i));
            isExistIHope = true;
            break;
        }
    }
    if(!isExistIHope){
        QMessageBox mb;
        mb.setWindowTitle("Upozornění");
        mb.setText("K tomuto filmu zatím není přidán žádný komentář!");
        mb.setWindowIcon(windowIcon());
        mb.setIcon(QMessageBox::Warning);
        mb.exec();
    }
}

void MainWindow::filmDelete()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Upozorneni");
    msgBox.setText("Opravdu chcete smazat tento film?");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setWindowIcon(windowIcon());
    if(msgBox.exec() == QMessageBox::Yes){
        QFile file("FIlmy.txt");
        QFile comment("Komentare.txt");
        QTextStream comTS(&comment);
        QTextStream ts(&file);
        QList<QStringList>* st = new QList<QStringList>();
        QList<QStringList>* comSt = new QList<QStringList>();

        if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
            return;
        }
        if(!comment.open(QIODevice::ReadWrite | QIODevice::Text)){
            return;
        }
        while(!file.atEnd()){
            QString line = file.readLine();
            st->append(line.split("\t"));
        }
        while(!comment.atEnd()){
            QString line = comment.readLine();
            comSt->append(line.split("\t"));
        }

        file.resize(0);
        comment.resize(0);
        for(int i =0 ; i <st->size(); i++){
            if(film2->text() == st->at(i).at(0)){
                st->removeAt(i);
                break;
            }
        }
        for(int i =0 ; i <comSt->size(); i++){
            if(film2->text() == comSt->at(i).at(0)){
                comSt->removeAt(i);
                i--;
            }
        }
        ts.setCodec("UTF-8");
        for(int i = 0;i<st->size();i++){
            QString s;
            QStringList newSt = st->at(i);
            for(int j =0; j<newSt.size();j++){
                if(j<newSt.size()-1){
                    s+=newSt.at(j)+"\t";
                }
                else{
                    s+=newSt.at(j);
                }
            }
            ts<<s;
        }
        comTS.setCodec("UTF-8");
        for(int i = 0;i<comSt->size();i++){
            QString s;
            QStringList newComSt = comSt->at(i);
            for(int j =0; j<newComSt.size();j++){
                if(j<newComSt.size()-1){
                    s+=newComSt.at(j)+"\t";
                }
                else{
                    s+=newComSt.at(j);
                }
            }
            comTS<<s;
        }
        file.close();
        comment.close();
        comboInsert();
        infoMW->close();
    }
}
