#include "filedetailswidget.h"
#include "ui_filedetailswidget.h"
#include <QFileInfo>
#include <QDateTime>

FileDetailsWidget::FileDetailsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileDetailsWidget)
{
    ui->setupUi(this);
}

FileDetailsWidget::~FileDetailsWidget()
{
    delete ui;
}

void FileDetailsWidget::setName(QString name)
{
    if(name.isEmpty())
        ui->lineEditName->setText("-");
    else
        ui->lineEditName->setText(name);
}

void FileDetailsWidget::setPath(QString path)
{
    if(path.isEmpty())
    {
        ui->lineEditPath->setText("-");
        ui->lineEditModified->setText("-");
        ui->lineEditCreated->setText("-");
    }else
    {
        ui->lineEditPath->setText(path);

        QFileInfo fi(path);

        QString format = "dd.MM.yyyy hh:mm:ss";
        QString created = fi.created().toString(format);
        QString modified = fi.lastModified().toString(format);

        ui->lineEditModified->setText(modified);
        ui->lineEditCreated->setText(created);
    }
}

void FileDetailsWidget::setComment(QString comment)
{
    if(comment.isEmpty())
        ui->plainTextEditComment->document()->clear();
    else
        ui->plainTextEditComment->document()->setPlainText(comment);
}

void FileDetailsWidget::clearDetails()
{
    ui->lineEditCreated->clear();
    ui->lineEditModified->clear();
    ui->lineEditName->clear();
    ui->lineEditPath->clear();
    ui->plainTextEditComment->document()->clear();
}
