#ifndef MAINSOURCE_H
#define MAINSOURCE_H
#include "NewFile/newfile.h"
#include "mysharedlib_global.h"

MYSHAREDLIB_EXPORT void foo();
class MYSHAREDLIB_EXPORT MainSource{

public:
    MainSource();

    bool addFileToList(QString name, QString path, QString comment, QString &retInfo);

    bool removeFileFromList(QString name);

    NewFilePtr getFile(QString name) const;

    const QList<NewFilePtr> getFileList() const;

    bool editFileOnList(QString oldName, QString name, QString path, QString comment, QString &retInfo);

private:
    FType determineFileType(const QString path) const;

    bool checkFileExistsOnList(QString name) const;


    bool checkFileBeforeAdd(QString name, QString path, FType &fType, QString &retInfo);
    bool addFileList(QString name, QString path, QString comment, FType fType);

    QList<NewFilePtr> files;
};

#endif // MAINSOURCE_H
