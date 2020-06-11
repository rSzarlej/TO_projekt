#ifndef FILEDETAILSWIDGET_H
#define FILEDETAILSWIDGET_H

#include <QWidget>

namespace Ui {
class FileDetailsWidget;
}

class FileDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileDetailsWidget(QWidget *parent = nullptr);
    ~FileDetailsWidget();

    void setName(QString name);
    void setPath(QString path);
    void setComment(QString comment);
    void clearDetails();


private:
    Ui::FileDetailsWidget *ui;
};

#endif // FILEDETAILSWIDGET_H
