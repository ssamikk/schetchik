#include "tablemodel.h"

TableModel::TableModel(QVector<int> *vector, QObject *parent)
    : QAbstractTableModel(parent)
{
    v = vector;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return "Item";
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return v->size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole && index.row() < v->size()){
        return v->at(index.row());
    } else if (role==Qt::TextAlignmentRole){
        return Qt::AlignCenter;
    }
    return QVariant();
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    if ( row >= v->size() ){
        for(int i =0; i < count; i++){
            v->push_back(0);
        }
    } else {
        v->insert(row, count, 0);
    }
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    bool flag = false;
    if (row < v->size()){
        if ( row == (v->size() - count)){
            v->resize(row);
        } else {
            v->remove(row, count);
        }
        flag = true;
    }
    endRemoveRows();
    return flag;
}

void TableModel::beginReset()
{
    beginResetModel();
}

void TableModel::endReset()
{
    endResetModel();
}
