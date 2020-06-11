#include "newfiletxt.h"
#include "fileManagers/filemanagertxt.h"

NewFileTxt::NewFileTxt(const QString name, const QString fPath, const QString comment) : NewFile(name, fPath, comment)
{

}

void NewFileTxt::openFile()
{
    FileManagerTxt tmp;
    tmp.setWindowTitle(this->getName());
    tmp.addTextFile(this->getFPath());
    tmp.exec();
}

FType NewFileTxt::getFType() const
{
    return fileTxt;
}
