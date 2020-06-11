#include "tablemodelfiles.h"

TableModelFiles::TableModelFiles(QObject *parent)
     : QAbstractTableModel(parent)
{
}

int TableModelFiles::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfRecords.size();
}

int TableModelFiles::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;//only 3 columns;
}

QVariant TableModelFiles::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfRecords.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        QPair<QString, QPair<QString, QString>> record = listOfRecords.at(index.row());
        if (index.column() == 0)
            return record.first;//name
        else if (index.column() == 1)
            return record.second.first;//path
        else if (index.column() == 2)
            return record.second.second;//typ
    }
    return QVariant();
}

QString TableModelFiles::dataName(const QModelIndex &index) const
{
    QPair<QString, QPair<QString, QString>> record = listOfRecords.at(index.row());
    if (index.column() == 0)
        return record.first;
}

QVariant TableModelFiles::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");

            case 1:
                return tr("Path");

            case 2:
                return tr("Type");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool TableModelFiles::insertRows(int position, int rows, const QModelIndex &index)//called before new data is added
{//otherwise the data will not be displayed
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; row++) {
        QPair<QString, QString> pair2(" ", " ");
        QString name = "";
        QPair<QString, QPair<QString, QString>> pair(name, pair2);
        listOfRecords.insert(position, pair);
    }

    endInsertRows();
    return true;
}

bool TableModelFiles::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        listOfRecords.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool TableModelFiles::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        QPair<QString, QPair<QString, QString>> p = listOfRecords.value(row);

        if (index.column() == 0)
            p.first = value.toString();
        else if (index.column() == 1)
            p.second.first = value.toString();
        else if (index.column() == 2)
            p.second.second = value.toString();
        else
            return false;

        listOfRecords.replace(row, p);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

Qt::ItemFlags TableModelFiles::flags(const QModelIndex &index) const//returns the item flags for the given index
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList< QPair<QString, QPair<QString, QString>> > TableModelFiles::getList()
{
    return listOfRecords;
}

int TableModelFiles::getSize()
{
    return listOfRecords.size();
}
