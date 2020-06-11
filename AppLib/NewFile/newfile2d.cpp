#include "newfile2d.h"
#include "fileManagers/filemanager2d.h"

NewFile2d::NewFile2d(const QString name, const QString fPath, const QString comment) : NewFile(name, fPath, comment)
{

}

void NewFile2d::openFile()
{
    FileManager2d tmp;
    tmp.setWindowTitle(this->getName());
    tmp.addImage(this->getFPath());
    tmp.exec();
}

FType NewFile2d::getFType() const
{
    return file2d;
}
