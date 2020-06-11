#ifndef NEWFILETXT_H
#define NEWFILETXT_H
#include "NewFile/newfile.h"

class NewFileTxt : public NewFile
{
public:
    NewFileTxt(const QString name, const QString fPath, const QString comment);
    void openFile();
    FType getFType() const;
};

#endif // NEWFILETXT_H
