#include "filemanager2d.h"
#include "ui_filemanager2d.h"
#include <QtGui/QPixmap>

FileManager2d::FileManager2d(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManager2d)
{
    ui->setupUi(this);



}

FileManager2d::~FileManager2d()
{
    delete ui;
}

void FileManager2d::addImage(QString path)
{
    QPixmap pm(path);
    ui->label->setPixmap(pm);
    ui->label->setScaledContents(true);
}
