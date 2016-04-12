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
    connect(infoFilmBut,SIGNAL(clicked(bool)),this,SLOT(aboutFilm()));
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
    //--------------Poznamka-------------------
    filmNote = new QTextEdit();
    noteLabel = new QLabel("Obsah filmu");
    noteLabel->setFont(QFont("",9));
    vboxlay2->addWidget(noteLabel);
    vboxlay2->addWidget(filmNote);
    widget2->setLayout(vboxlay2);
    //---------Tlacitka--------------
    filmButLay = new QHBoxLayout();
    filmCloseBut = new QPushButton("Zrušit");
    filmCLEAREBut = new QPushButton("Vymazat");
    filmADDBut = new QPushButton("Přidat");
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

    //closeMsg.setDefaultButton(QMessageBox::No);

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

    //    if(!file.open(QFile::Append | QFile::Text)){
    //        return;
    //    }
    //    file.write(str.toLatin1().data());
    //    file.close();

    QMessageBox added;
    added.setText("Film byl úspěšně přidán!");
    added.setIcon(QMessageBox::Information);
    added.setWindowIcon(windowIcon());
    added.exec();

}

void MainWindow::commentAdding()
{
    comMainWin = new QMainWindow();
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
    hGenderLay->setAlignment(Qt::AlignLeft);
    g->setAlignment(Qt::AlignLeft);


    vNoteLay->setAlignment(Qt::AlignTop);

    comMainWin->setWindowTitle("Přidat komentář");
    comMainWin->setWindowIcon(windowIcon());
    comMainWin->resize(300,300);
    vNoteLay->addWidget(nickLabel);
    vNoteLay->addWidget(nickLE);
    vNoteLay->addWidget(mailLabel);
    vNoteLay->addWidget(mailLE);
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
    hButLay = new QHBoxLayout();
    comCloseBut = new QPushButton("Zrušit");
    comCLearBut = new QPushButton("Vymazat");
    comAddBut = new QPushButton("Přidat");

    comCloseBut->setFixedHeight(30);
    comCLearBut->setFixedHeight(30);
    comAddBut->setFixedHeight(30);

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

void MainWindow::aboutFilm()
{
    infoMW = new QMainWindow();
    infoMW->setWindowTitle("Info o filmu");
    infoMW->setWindowIcon(windowIcon());
    infoMW->resize(300,300);

    //infoWIDG->setLayout(vInfoLay);
    //infoMW->setCentralWidget(infoWIDG);
    infoMW->show();


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
