#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainsource.h"
#include "dlg/dialogopenfile.h"
#include <QMessageBox>
#include <QTableView>
#include <QDockWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mSource = new MainSource();

    table = new TableModelFiles(this);

    createToolbars();
    setupRecords();

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);//menu kontekstowe
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuTableView(QPoint)));
    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));

    fdw = new FileDetailsWidget(this);

    dock = new QDockWidget("Details", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(fdw);
    ui->menuWindow->addAction(dock->toggleViewAction());
    addDockWidget(Qt::RightDockWidgetArea, dock);
}

MainWindow::~MainWindow()
{ 
    delete fdw;
    delete dock;
    delete table;
    delete proxyModel;
    delete mSource;
    delete generalToolBar;
    delete ui;
}

void MainWindow::actionAddFileSlot(bool)
{
    DialogOpenFile dlg;

    QString path, name, comment;

    if(dlg.exec())
    {
        path = dlg.getPath();
        name = dlg.getName();
        comment = dlg.getComment();

        QString retInfo;
        if(!mSource->addFileToList(name, path, comment, retInfo))
        {
            QMessageBox::information(this, "Problem", "Unable to add file. "+retInfo);
            return;
        }

        this->addTableEntry(name, path, mSource->getFile(name)->getFTypeString());
    } 
}

void MainWindow::actionRemoveFileSlot(bool)
{
    QString name = this->removeTableEntry();

    if(name.isEmpty())
        return;

    bool retVal = mSource->removeFileFromList(name);

    if(!retVal)
        qDebug()<<"Unable to remove file:"<<name;

    fdw->clearDetails();
    this->updateDetails();
}

void MainWindow::actionRemoveAllFileSlot(bool)
{
    QModelIndex index;

    for(int i=table->getSize()-1; i>=0; i--)
    {
        index = table->index(i, 0, QModelIndex());
        mSource->removeFileFromList(table->dataName(index));
        table->removeRows(i, 1, QModelIndex());
    }

    fdw->clearDetails();
    this->updateDetails();
}

void MainWindow::actionEditFileSlot(bool)
{
    QString oldName = this->getSelectedTableEntry();

    if(oldName.isEmpty())
        return;

    NewFilePtr ob = mSource->getFile(oldName);

    if(ob == NULL)
    {
       qDebug()<<"Edit - no file found";
       return;
    }

    DialogOpenFile dlg;
    QString path, name, comment;

    dlg.setPath(ob->getFPath());
    dlg.setName(ob->getName());
    dlg.setComment(ob->getComment());

    if(dlg.exec())
    {
        path = dlg.getPath();
        name = dlg.getName();
        comment = dlg.getComment();

        QString retInfo;
        if(!mSource->editFileOnList(oldName, name, path, comment, retInfo))
        {
            QMessageBox::information(this, "Problem", "Unable to edit record. "+retInfo);
            return;
        }

        this->removeTableEntry();
        this->addTableEntry(name, path, mSource->getFile(name)->getFTypeString());
    }
}

void MainWindow::actionOpenFileSlot(bool)
{
    QString name = getSelectedTableEntry();

    if(name.isEmpty())
        return;

    NewFilePtr file = mSource->getFile(name);

    if(file.isNull())
        return;

    file->openFile();
}

void MainWindow::customMenuTableView(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    QAction *a0 = new QAction(tr("Open"), this);
    a0->setData(0);
    menu->addAction(a0);

    QAction *a1 = new QAction(tr("Add"), this);
    a1->setData(1);
    menu->addAction(a1);

    QAction *a2 = new QAction(tr("Remove"), this);
    a2->setData(2);
    menu->addAction(a2);

    QAction *a3 = new QAction(tr("Remove all"), this);
    a3->setData(3);
    menu->addAction(a3);

    QAction *a4 = new QAction(tr("Edit"), this);
    a4->setData(4);
    menu->addAction(a4);

    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(trig_customMenuTableView(QAction*)));
}

void MainWindow::trig_customMenuTableView(QAction *trigAct)
{
    int value = trigAct->data().toInt();
    if(value == 0)
        actionOpenFileSlot(true);
    if(value == 1)
        actionAddFileSlot(true);
    if(value == 2)
        actionRemoveFileSlot(true);
    if(value == 3)
        actionRemoveAllFileSlot(true);
    if(value == 4)
        actionEditFileSlot(true);
    return;
}

void MainWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
{
    this->updateDetails();
}

void MainWindow::createToolbars()
{
    generalToolBar = addToolBar("Toolbar");
    generalToolBar->setObjectName("Toolbar");
    ui->menuWindow->addAction(generalToolBar->toggleViewAction());

    QAction *act = &addFile;
    act->setToolTip("Add file to list");
    connect(act, SIGNAL(triggered(bool)), this, SLOT(actionAddFileSlot(bool)));
    act->setIcon(QIcon(":/doc/add_plus.png"));
    generalToolBar->addAction(act);

    act = &removeFile;
    act->setToolTip("Remove file from list");
    connect(act, SIGNAL(triggered(bool)), this, SLOT(actionRemoveFileSlot(bool)));
    act->setIcon(QIcon(":/doc/remove_minus.png"));
    generalToolBar->addAction(act);

    act = &editFile;
    act->setToolTip("Edit file info");
    connect(act, SIGNAL(triggered(bool)), this, SLOT(actionEditFileSlot(bool)));
    act->setIcon(QIcon(":/doc/edit_olowek.png"));
    generalToolBar->addAction(act);

    act = &openFile;
    act->setToolTip("Open file");
    connect(act, SIGNAL(triggered(bool)), this, SLOT(actionOpenFileSlot(bool)));
    act->setIcon(QIcon(":/doc/open.png"));
    generalToolBar->addAction(act);
}

void MainWindow::updateDetails()
{
    QString name = this->getSelectedTableEntry();

    if(name.isEmpty())
        return;

    NewFilePtr ob = mSource->getFile(name);

    fdw->setName(name);
    fdw->setComment(ob->getComment());
    fdw->setPath(ob->getFPath());
}

void MainWindow::setupRecords()
{
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(table);
    proxyModel->setDynamicSortFilter(true);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    connect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this, SIGNAL(selectionChanged(QItemSelection)));
}

void MainWindow::addTableEntry(QString name, QString path, QString ftype)
{
    if(!name.isEmpty())
    {
        table->insertRows(0, 1, QModelIndex());

        QModelIndex index = table->index(0, 0, QModelIndex());
        QModelIndex tmp = index;
        table->setData(index, name, Qt::EditRole);
        index = table->index(0, 1, QModelIndex());
        table->setData(index, path, Qt::EditRole);
        index = table->index(0, 2, QModelIndex());
        table->setData(index, ftype, Qt::EditRole);
    }
}

QString MainWindow::removeTableEntry()
{
    QTableView *temp = ui->tableView;
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();
    if(!selectionModel->hasSelection()) return "";

    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index, i;

    QString name("");

    foreach (index, indexes) {
        int row = proxy->mapToSource(index).row();
        i = table->index(row, 0, QModelIndex());
        name = table->dataName(i);
        table->removeRows(row, 1, QModelIndex());
    }

    return name;
}

QString MainWindow::getSelectedTableEntry()
{
    QTableView *temp = ui->tableView;
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QItemSelectionModel *selectionModel = temp->selectionModel();
    if(!selectionModel->hasSelection()) return "";

    QModelIndexList indexes = selectionModel->selectedRows();
    QModelIndex index, i;

    QString name("");

    foreach (index, indexes) {
        int row = proxy->mapToSource(index).row();
        i = table->index(row, 0, QModelIndex());
        name = table->dataName(i);
    }

    return name;
}

void MainWindow::on_actionAdd_file_triggered()
{
    this->actionAddFileSlot(true);
}
