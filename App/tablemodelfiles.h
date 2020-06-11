#ifndef TABLEMODELFILES_H
#define TABLEMODELFILES_H
#include <QAbstractTableModel>
#include <QShortcut>

class TableModelFiles : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModelFiles(QObject *parent=0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QString dataName(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    QList<QPair<QString, QPair<QString, QString> > > getList();
    int getSize();

private:
    QList< QPair<QString, QPair<QString, QString>> > listOfRecords;
};

#endif // TABLEMODELFILES_H
