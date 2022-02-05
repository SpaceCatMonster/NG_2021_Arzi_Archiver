#include "arzi.h"
#include "ui_arzi.h"
#include <iostream>
#include <string.h>
#include <QDebug>
#include "zipreader.h"
#include "zipwriter.h"
#include "zlib.h"
#include <QList>
#include <QMessageBox>

arzi::arzi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::arzi)
{
    ui->setupUi(this);

    ui->e_g_showWhichFiles->setReadOnly(true);
    //style


    //green - archive
    connect (ui->b_green, &QPushButton::clicked, this, &arzi::gotopage);
    connect (ui->b_gback, &QPushButton::clicked, this, &arzi::back);
    connect (ui->b_g_find, &QPushButton::clicked, this, &arzi::addfiles);
    connect (ui->b_g_findpath, &QPushButton::clicked, this, &arzi::choosefolder);
    connect (ui->b_g_active_archive, &QPushButton::clicked, this, &arzi::start_arch);

    //blue - open/look
    connect (ui->b_blue, &QPushButton::clicked, this, &arzi::gotopage);
    connect (ui->b_bback, &QPushButton::clicked, this, &arzi::back);
    connect (ui->b_b_choosearc, &QPushButton::clicked, this, &arzi::choosearch);
    connect (ui->b_b_openarch, &QPushButton::clicked, this, &arzi::openarc);


    //yellow - disarchive
    connect (ui->b_yellow, &QPushButton::clicked, this, &arzi::gotopage);
    connect (ui->b_yback, &QPushButton::clicked, this, &arzi::back);
    connect (ui->b_y_choosearchive, &QPushButton::clicked, this, &arzi::findarch);
    connect (ui->b_y_choosedirectory, &QPushButton::clicked, this, &arzi::choosedir);
    connect (ui->b_y_unzip, &QPushButton::clicked, this, &arzi::start_unzip);

}

arzi::~arzi()
{
    delete ui;
}



//Global variables
QList <QString> files_list;
QString ZipFile;



//Functions/Slots

void arzi::gotopage()
{
    QPushButton *button = (QPushButton*)sender();

        if (button == ui->b_green) ui->stackedWidget->setCurrentIndex(1);
        if (button == ui->b_blue) ui->stackedWidget->setCurrentIndex(2);
        if (button == ui->b_yellow) ui->stackedWidget->setCurrentIndex(3);
}

void arzi::back()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->e_g_nameofarhive->clear();
    ui->e_g_savepath->clear();
    ui->e_g_showWhichFiles->clear();
    ui->e_y_archivepath->clear();
    ui->e_y_directorypath->clear();
    ui->e_b_choosearch->clear();
    ui->e_b_showFiles->clear();

}

//for archivate

void arzi::addfiles()
{
    QStringList path = QFileDialog::getOpenFileNames(this, tr("Select one or more files to archive"),
                                                    QDir::homePath(),
                                                    tr("All files (*.*)"));

    for(int i=0; i<path.size(); i++){
       ui->e_g_showWhichFiles->setText(ui->e_g_showWhichFiles->toPlainText() + QString(path.at(i)));

       ui->e_g_showWhichFiles->append("");
       files_list.append(path.at(i));

   }

    //qDebug()<<QString(ui->e_g_showWhichFiles->toPlainText());
}

void arzi::choosefolder()
{
    QString save_path = QFileDialog::getExistingDirectory(this, tr("Choose path to save archive"), QDir::homePath());
    ui->e_g_savepath->setText(save_path + "/" + ui->e_g_nameofarhive->text() + ".zip");
    ZipFile = ui->e_g_savepath->text();

    /*if(ui->e_g_nameofarhive->text()==0){
        ui->test->setText("0");             работает. когда нет имени значени = 0
    }else {ui->test->setText("1");}*/
}

void arzi::start_arch()
{
    QMessageBox msgBox;
    if(ui->e_g_nameofarhive->text()==0||ui->e_g_savepath->text()==0||ui->e_g_showWhichFiles==0){
        //qDebug()<<"STOP IT";
        msgBox.warning(this, "Warning!", "You need to fill all fields");

        ui->e_g_savepath->clear();
    }else{
        //qDebug()<<"You free to go";
        arzi::compress(ZipFile);
    }

}

void arzi::compress(QString ZipFile)
{
    ZipWriter cZip(ZipFile);
    QFile file("");

    for(int i=0;i<files_list.length();i++){
        QString SingleFile = files_list.at(i);

        QFile file(SingleFile);
        file.open(QIODevice::ReadOnly);
        qDebug()<<file.fileName();
        cZip.addFile(SingleFile.remove(0, SingleFile.lastIndexOf("/") + 1), file.readAll());

    }
    file.close();
    cZip.close();
    QMessageBox msgBox;
    msgBox.about(this, "Done!", "Archiving completed");

    ui->e_g_nameofarhive->clear();
    ui->e_g_savepath->clear();
    ui->e_g_showWhichFiles->clear();

    files_list.clear();
    ZipFile.clear();


    ui->stackedWidget->setCurrentIndex(0);

}

//-------------------------------------------------------------------------------------------------------------------

//for dearchivate

QString ExtractDirectory;

void arzi::findarch()
{
    QString arcPath = QFileDialog::getOpenFileName(this, tr("Choose archive"),
                                                    QDir::homePath(),
                                                    tr("Archives (*.zip)"));
    ui->e_y_archivepath->setText(arcPath);
    ZipFile = ui->e_y_archivepath->text();
}

void arzi::choosedir()
{
    QString save_path = QFileDialog::getExistingDirectory(this, tr("Choose directory to unzip archive"), QDir::homePath());
    ui->e_y_directorypath->setText(save_path);
    ExtractDirectory = save_path;
}

void arzi::start_unzip()
{
    QMessageBox msgBox;
    if(ui->e_y_archivepath->text()==0||ui->e_y_directorypath->text()==0){
        msgBox.warning(this, "Warning!", "You need to fill all fields");
        ui->e_y_archivepath->clear();
        ui->e_y_directorypath->clear();
    }else{

        arzi::decompress(ZipFile);
    }
}

void arzi::decompress(QString ZipFile)
{
    ZipReader cZip(ZipFile);
    foreach(ZipReader::FileInfo item, cZip.fileInfoList()){
        qDebug()<<item.filePath;
    }

    cZip.extractAll(ExtractDirectory);
    cZip.close();

    QMessageBox msgBox;
    msgBox.about(this, "Done!", "Unziping completed");

    ui->e_y_archivepath->clear();
    ui->e_y_directorypath->clear();

    ZipFile.clear();

    ui->stackedWidget->setCurrentIndex(0);

}

//-------------------------------------------------------------------------------------------------------------------

//for open archive(look through)

void arzi::choosearch()
{
    QString arcPath = QFileDialog::getOpenFileName(this, tr("Choose archive"),
                                                    QDir::homePath(),
                                                    tr("Archives (*.zip)"));
    ui->e_b_choosearch->setText(arcPath);
    ZipFile = ui->e_b_choosearch->text();
}

void arzi::openarc()
{
    QMessageBox msgBox;
    if(ui->e_b_choosearch->text()==0){
        msgBox.warning(this, "Warning!", "You need to fill field");
        ui->e_b_choosearch->clear();
    }else{

        arzi::open(ZipFile);
    }
}

void arzi::open(QString ZipFile)
{
    ZipReader cZip(ZipFile);
    foreach(ZipReader::FileInfo item, cZip.fileInfoList()){
        qDebug()<<item.filePath;
        // ui->e_g_showWhichFiles->setText(ui->e_g_showWhichFiles->toPlainText() + QString(path.at(i)));
        ui->e_b_showFiles->setText(ui->e_b_showFiles->toPlainText() + item.filePath + "\n");
    }

    cZip.close();

    ZipFile.clear();

}







