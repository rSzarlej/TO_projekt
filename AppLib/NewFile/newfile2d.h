#ifndef NEWFILE2D_H
#define NEWFILE2D_H
#include "NewFile/newfile.h"

class NewFile2d : public NewFile
{
public:
    NewFile2d(const QString name, const QString fPath, const QString comment);
    void openFile();
    FType getFType() const;
};


#endif // NEWFILE2D_H
