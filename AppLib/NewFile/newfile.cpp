#include "newfile.h"

NewFile::NewFile(QString name, QString fPath, QString comment)
{
    this->name = name;
    this->fPath = fPath;
    this->comment = comment;
}

void NewFile::setName(const QString name)
{
    this->name = name;
}

QString NewFile::getName() const
{
    return this->name;
}

void NewFile::setFPath(QString fPath)
{
    this->fPath = fPath;
}

QString NewFile::getFPath() const
{
    return this->fPath;
}

void NewFile::setComment(const QString comment)
{
    this->comment = comment;
}

QString NewFile::getComment() const
{
    return comment;
}

QString NewFile::getFTypeString() const
{
    if(this->getFType() == file3d)
        return "3D File";

    if(this->getFType() == fileTxt)
        return "Txt file";

    if(this->getFType() == file2d)
        return "Image file";

    if(this->getFType() == fileUnknown)
        return "Unknown file";
}
