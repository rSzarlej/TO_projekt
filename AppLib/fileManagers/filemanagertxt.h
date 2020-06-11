#ifndef FILEMANAGERTXT_H
#define FILEMANAGERTXT_H

#include <QtWidgets/QDialog>

namespace Ui {
class FileManagerTxt;
}

class FileManagerTxt : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerTxt(QWidget *parent = nullptr);
    ~FileManagerTxt();

    void addTextFile(QString path);

private:
    Ui::FileManagerTxt *ui;
};

#endif // FILEMANAGERTXT_H
