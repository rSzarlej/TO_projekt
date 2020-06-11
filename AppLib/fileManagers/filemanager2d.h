#ifndef FILEMANAGER2D_H
#define FILEMANAGER2D_H

#include <QtWidgets/QDialog>

namespace Ui {
class FileManager2d;
}

class FileManager2d : public QDialog
{
    Q_OBJECT

public:
    explicit FileManager2d(QWidget *parent = nullptr);
    ~FileManager2d();

    void addImage(QString path);

private:
    Ui::FileManager2d *ui;
};

#endif // FILEMANAGER2D_H
