#include "listmodel.h"
#include <QDebug>

ListModel::ListModel(QObject *parent):
    QAbstractListModel(parent)
{
    pUkuiMenuInterface=new UkuiMenuInterface;
}

ListModel::~ListModel()
{
    delete pUkuiMenuInterface;
}

void ListModel::setData(const QVector<QStringList> &data)
{
    m_data=data;
}

void ListModel::updateData(const QVector<QStringList> &data)
{
    QVector<QStringList> max = (m_data.size() > data.size())? m_data:data;
    int row=max.size();
    m_data.clear();
    m_data=data;
    emit dataChanged(createIndex(0,0), createIndex(row-1,0));
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

int ListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    for(int i=row+count-1;i>=row;i--)
    {
        m_data.removeAt(i);
    }
}

bool ListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    m_data.removeAt(row);
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
//    if(!index.isValid())
//        return QVariant();
//    switch (role){
//    case Qt::DisplayRole:
//    {
//        if(index.column()==0)
//        {
//            int row=index.row();
//            QStringList val=m_data.at(row);
//            if(val.at(1).toInt()==0)
//            {
//                return val.at(0);
//            }
//        }
//        if(index.column()==1)
//        {
//            int row=index.row();
//            QStringList val=m_data.at(row);
//            if(val.at(1).toInt()==0)
////                return val.at(0);
////                return val;
//                return QVariant();
//            else
//            {
//                QString appname=KylinStartMenuInterface::get_app_name(val.at(0));
//                return appname;
//            }

//        }
//    }
//    case Qt::DecorationRole:
//    {
//        if(index.column()==0)
//        {
//            int row=index.row();
//            QStringList val=m_data.at(row);
//            if(val.at(1).toInt()==0)
//                return QVariant();
//            else
//            {
//                QString iconstr=KylinStartMenuInterface::get_app_icon(val.at(0));
//                QIcon icon=QIcon::fromTheme(iconstr);
//                return icon;
//            }
//        }
//    }
//    default:
//        return QVariant();
//    }

    if(!index.isValid())
        return QVariant();
    switch (role){
    case Qt::DecorationRole:
    {
        int row=index.row();
        QStringList val=m_data.at(row);
        if(val.at(1).toInt()==0)
            return QVariant();
        else
        {
            QString iconstr=pUkuiMenuInterface->get_app_icon(val.at(0));
            QIcon icon=QIcon::fromTheme(iconstr);
            return icon;
        }
    }
    case Qt::DisplayRole:
    {
        int row=index.row();
        QStringList val=m_data.at(row);
//        if(val.at(1).toInt()==0)
//            return val.at(0);
//        else
//        {
//            QString appname=KylinStartMenuInterface::get_app_name(val.at(0));
//            return appname;
//        }

        return val;
    }
    case Qt::SizeHintRole:
    {
        return QSize(300,38);

    }
    default:
        return QVariant();
    }


     return QVariant();
}
