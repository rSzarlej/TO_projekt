#ifndef NEWFILE_H
#define NEWFILE_H
#include <QString>
#include <QSharedPointer>
#include <QDebug>
#include "mysharedlib_global.h"


enum FType{
    fileTxt,
    file3d,
    file2d,
    fileUnknown
};

MYSHAREDLIB_EXPORT void foo();
class MYSHAREDLIB_EXPORT NewFile{
public:
    NewFile(QString name, QString path, QString comment);

    virtual void openFile() = 0;
    virtual FType getFType() const = 0;

    void setName(const QString name);
    QString getName() const;

    void setFPath(const QString fPath);
    QString getFPath() const;

    void setComment(const QString comment);
    QString getComment() const;

    QString getFTypeString() const;

private:
    QString name, fPath, comment;
};

typedef QSharedPointer<NewFile> NewFilePtr;

#endif // NEWFILE_H
