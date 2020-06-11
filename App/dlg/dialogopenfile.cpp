#include "dialogopenfile.h"
#include "ui_dialogopenfile.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

DialogOpenFile::DialogOpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOpenFile)
{
    ui->setupUi(this);


    lastPath = "C:";
    ui->lineEditPath->setReadOnly(true);
}

DialogOpenFile::~DialogOpenFile()
{
    delete ui;
}

QString DialogOpenFile::getPath() const
{
    return path;
}

QString DialogOpenFile::getName() const
{
    return ui->lineEditName->text();
}

QString DialogOpenFile::getComment() const
{
    return ui->plainTextComment->toPlainText();
}

void DialogOpenFile::setPath(QString path)
{
    this->path = path;
    QFileInfo fi(path);
    lastPath = fi.dir().absolutePath();
    ui->lineEditPath->setText(path);
}

void DialogOpenFile::setName(QString name)
{
    ui->lineEditName->setText(name);
}

void DialogOpenFile::setComment(QString comment)
{
    ui->plainTextComment->document()->setPlainText(comment);
}

void DialogOpenFile::on_btnSelectPath_clicked()
{
    QString fiTypes = "3D models (*.obj *.txt *.jpg *.png)";
    path = QFileDialog::getOpenFileName(this, tr("Open file"), lastPath, fiTypes);

    QFileInfo fi(path);
    lastPath = fi.dir().absolutePath();

    ui->lineEditPath->setText(path);

    if(ui->lineEditName->text() == "")
        ui->lineEditName->setText(fi.fileName());
}

void DialogOpenFile::done(int r)
{
    if(QDialog::Accepted == r)  //ok
    {
        if(!ui->lineEditName->text().isEmpty() &&
                !ui->lineEditPath->text().isEmpty())
        {
            //wszystko OK
            QDialog::done(r);
            return;
        }
        else
        {
            QMessageBox::information(this, "Problem", "Name and file are required.");
            return;
        }
    }
    else    //cancel
    {
        QDialog::done(r);
        return;
    }
}
