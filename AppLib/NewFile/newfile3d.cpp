#include "newfile3d.h"
#include "fileManagers/filemanager3d.h"

NewFile3d::NewFile3d(const QString name, const QString fPath, const QString comment) : NewFile(name, fPath, comment)
{

}

void NewFile3d::openFile()
{
    FileManager3d tmp;
    tmp.setWindowTitle(this->getName());
    tmp.addMesh(this->getFPath());
    tmp.exec();
}

FType NewFile3d::getFType() const
{
    return file3d;
}
