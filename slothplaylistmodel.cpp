#include "slothplaylistmodel.h"

#include <QFileInfo>
#include <QUrl>
#include <QMediaPlaylist>

SlothPlayListModel::SlothPlayListModel(QObject *parent)
    : QAbstractItemModel(parent)
    , Sloth_Playlist(0)
{
}

int SlothPlayListModel::rowCount(const QModelIndex &parent) const
{
    return Sloth_Playlist && !parent.isValid() ? Sloth_Playlist->mediaCount() : 0;
}

int SlothPlayListModel::columnCount(const QModelIndex &parent) const
{
    return !parent.isValid() ? ColumnCount : 0;
}

QModelIndex SlothPlayListModel::index(int row, int column, const QModelIndex &parent) const
{
    return Sloth_Playlist && !parent.isValid()
            && row >= 0 && row < Sloth_Playlist->mediaCount()
            && column >= 0 && column < ColumnCount
            ? createIndex(row, column)
            : QModelIndex();
}

QModelIndex SlothPlayListModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

QVariant SlothPlayListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole){
        QVariant value = sloth_data[index];
        if (!value.isValid() && index.column() == Title){
            QUrl location = Sloth_Playlist->media(index.row()).canonicaUrl();
            return QFileInfo(location.path()).fileName();
        }
        return value;
    }
    return QVariant();
}

QMediaPlayList *SlothPlayListModel::slothplaylist() const
{
    return Sloth_Playlist;
}

void SlothPlayListModel::setPlaylist(QMediaPlayList *slothplaylist)
{
    if(Sloth_Playlist){
        disconnect(Sloth_Playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginInsertItems(int,int)));
        disconnect(Sloth_Playlist, SIGNAL(mediaInserted(int,int)), this, SLOT(endInsertItems()));
        disconnect(Sloth_Playlist, SIGNAL(mediaAboutToBeRemoved(int,int)), this, SLOT(beginRemoveItems(int,int)));
        disconnect(Sloth_Playlist, SIGNAL(mediaRemoved(int,int)), this, SLOT(endRemoveItems()));
        disconnect(Sloth_Playlist, SIGNAL(mediaChanged(int,int)), this, SLOT(changeItems(int,int)));
    }
    beginResetModel();
    Sloth_Playlist = slothplaylist;

    if(Sloth_Playlist){
        connect(Sloth_Playlist, SIGNAL(mediaAboutToBeInserted(int,int)), this, SLOT(beginInsertItems(int,int)));
        connect(Sloth_Playlist, SIGNAL(mediaInserted(int,int)), this, SLOT(endInsertItems()));
        connect(Sloth_Playlist, SIGNAL(mediaAboutToBeRemoved(int,int)), this, SLOT(beginRemoveItems(int,int)));
        connect(Sloth_Playlist, SIGNAL(mediaRemoved(int,int)), this, SLOT(endRemoveItems()));
        connect(Sloth_Playlist, SIGNAL(mediaChanged(int,int)), this, SLOT(changeItems(int,int)));
    }

    endResetModel();
}

bool SlothPlayListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    sloth_data[index] = value;
    emit dataChanged(index,index);
    return true;
}

void SlothPlayListModel::beginInsertItems(int start, int end)
{
    sloth_data.clear();
    beginInsertRows(QModelIndex(), start, end);
}

void SlothPlayListModel::endInsertItems()
{
    endInsertRows();
}

void SlothPlayListModel::beginRemoveItems(int start, int end)
{
    sloth_data.clear();
    beginRemoveRows(QModelIndex, start, end);
}

void SlothPlayListModel::endRemoveItems()
{
    endInsertRows();
}

void SlothPlayListModel::changeItems(int start, int end)
{
    sloth_data.clear();
    emit dataChanged(index(start,0), index(end,ColumnCount));
}

