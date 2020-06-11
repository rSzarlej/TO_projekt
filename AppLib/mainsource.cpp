#include "mainsource.h"
#include <QFileInfo>
#include "NewFile/newfile.h"
#include "NewFile/newfile3d.h"
#include "NewFile/newfile2d.h"
#include "NewFile/newfiletxt.h"

MainSource::MainSource()
{

}

bool MainSource::addFileToList(QString name, QString path, QString comment, QString &retInfo)
{
    FType fType;

    if(!this->checkFileBeforeAdd(name, path, fType, retInfo))
        return false;

    return this->addFileList(name, path, comment, fType);
}

bool MainSource::removeFileFromList(QString name)
{
    for(int i=0; i<files.size(); i++)
    {
        if(files.at(i)->getName() == name)
        {
            files[i].clear();
            files.removeAt(i);
            return true;
        }
    }

    return false;
}

NewFilePtr MainSource::getFile(QString name) const
{
    foreach (NewFilePtr fi, files)
    {
        if(fi->getName() == name)
            return fi;
    }

    return NULL;
}

const QList<NewFilePtr> MainSource::getFileList() const
{
    return files;
}

bool MainSource::editFileOnList(QString oldName, QString name, QString path, QString comment, QString &retInfo)
{
    FType fType = this->determineFileType(path);;


    if(oldName != name)
    {
        if(this->checkFileExistsOnList(name))
        {
            retInfo = "Name already in use";
            return false;
        }
    }

    this->removeFileFromList(oldName);

    return this->addFileList(name, path, comment, fType);
}

FType MainSource::determineFileType(const QString path) const
{
    QFileInfo fi(path);
    QString ext = fi.suffix();

    if(ext.toLower() == "txt")
        return fileTxt;

    if(ext.toLower() == "obj")
        return file3d;

    if(ext.toLower() == "jpg" || ext.toLower() == "png")
        return file2d;


    return fileUnknown;
}

bool MainSource::checkFileExistsOnList(QString name) const
{
    foreach(NewFilePtr fi, files)
        if(fi->getName() == name)
            return true;
    return false;
}

bool MainSource::checkFileBeforeAdd(QString name, QString path, FType &fType, QString &retInfo)
{
    QFileInfo fi(path);

    if(!fi.exists())
    {
        retInfo = "File not exists: "+path;
        return false;
    }

    if(this->checkFileExistsOnList(name))
    {
        retInfo = "Name already on list.";
        return false;
    }

    fType = this->determineFileType(path);


    if(fType == fileUnknown)
    {
        retInfo = "Unknown file";
        return false;
    }

    return true;
}

bool MainSource::addFileList(QString name, QString path, QString comment, FType fType)
{
    NewFilePtr nFile;
    if(fType == file3d)
        nFile = NewFilePtr(new NewFile3d(name, path, comment));

    if(fType == file2d)
        nFile = NewFilePtr(new NewFile2d(name, path, comment));

    if(fType == fileTxt)
        nFile = NewFilePtr(new NewFileTxt(name, path, comment));

    files.append(nFile);

    return true;
}
