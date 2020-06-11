#ifndef NEWFILE3D_H
#define NEWFILE3D_H
#include "NewFile/newfile.h"

class NewFile3d : public NewFile
{
public:
    NewFile3d(const QString name, const QString fPath, const QString comment);
    void openFile();
    FType getFType() const;
};

#endif // NEWFILE3D_H
