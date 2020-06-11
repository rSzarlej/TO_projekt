#ifndef DIALOGOPENFILE_H
#define DIALOGOPENFILE_H

#include <QDialog>

namespace Ui {
class DialogOpenFile;
}

class DialogOpenFile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOpenFile(QWidget *parent = nullptr);
    ~DialogOpenFile();

    QString getPath() const;
    QString getName() const;
    QString getComment() const;

    void setPath(QString path);
    void setName(QString name);
    void setComment(QString comment);

private slots:
    void on_btnSelectPath_clicked();

private:
    void done(int r);


    Ui::DialogOpenFile *ui;

    QString path, lastPath;
};

#endif // DIALOGOPENFILE_H
