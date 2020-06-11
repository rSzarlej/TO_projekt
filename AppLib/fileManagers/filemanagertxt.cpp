#include "filemanagertxt.h"
#include "ui_filemanagertxt.h"
#include <QFile>
#include <QTextStream>

FileManagerTxt::FileManagerTxt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerTxt)
{
    ui->setupUi(this);
}

FileManagerTxt::~FileManagerTxt()
{
    delete ui;
}

void FileManagerTxt::addTextFile(QString path)
{
    QFile fi(path);
    QString line;
    if (fi.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&fi);
        while (!stream.atEnd()){

            line.append(stream.readLine()+"\n");
        }
        ui->plainTextEdit->document()->setPlainText(line);
    }
    fi.close();
}
