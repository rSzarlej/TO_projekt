#ifndef FILEMANAGER3D_H
#define FILEMANAGER3D_H
#include <QObject>
#include <QtWidgets/QDialog>
#include <Qt3DCore/QEntity>

namespace Ui {
class FileManager3d;
}

class FileManager3d : public QDialog
{
    Q_OBJECT

public:
    explicit FileManager3d(QWidget *parent = nullptr);
    ~FileManager3d();

    void addMesh(QString path);

private:
    Ui::FileManager3d *ui;

    QWidget *container;

    Qt3DCore::QEntity *mainEntity;

protected:
    void resizeEvent ( QResizeEvent * event );

public slots:
    void resizeView(QSize size);
};

#endif // FILEMANAGER3D_H
