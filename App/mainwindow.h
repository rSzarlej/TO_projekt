#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QSortFilterProxyModel>
#include "dlg/filedetailswidget.h"
#include "tablemodelfiles.h"

class MainSource;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void actionAddFileSlot(bool);
    void actionRemoveFileSlot(bool);
    void actionRemoveAllFileSlot(bool);
    void actionEditFileSlot(bool);
    void actionOpenFileSlot(bool);

    void customMenuTableView(QPoint pos);
    void trig_customMenuTableView(QAction* trigAct);

    void selectionChangedSlot(const QItemSelection &, const QItemSelection &);

    void on_actionAdd_file_triggered();



signals:
    void selectionChanged (const QItemSelection &selected);

private:
    void createToolbars();

    void updateDetails();

    void setupRecords();
    void addTableEntry(QString name, QString path, QString ftype);
    QString removeTableEntry();
    QString getSelectedTableEntry();


    Ui::MainWindow *ui;

    MainSource *mSource;

    QToolBar *generalToolBar;

    QAction addFile;
    QAction removeFile;
    QAction editFile;
    QAction openFile;

    TableModelFiles *table;
    QSortFilterProxyModel *proxyModel;

    FileDetailsWidget *fdw;
    QDockWidget *dock;
};

#endif // MAINWINDOW_H
