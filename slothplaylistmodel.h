/*#ifndef SLOTHPLAYLISTMODEL_H
#define SLOTHPLAYLISTMODEL_H

#include <QAbstractItemModel>

class QMediaPlayList;

class SlothPlayListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Column
    {
        Title = 0,
        ColumnCount
    };

    explicit SlothPlayListModel(QObject *parent = 0);

    //Возвращает кол-во элемантов списка
    int rowCount   (const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    //Возращает значение элемента
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QMediaPlayList *slothplaylist() const;
    void setPlaylist(QMediaPlayList *slothplaylist);

    //Сохраняет новое значение элемента
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);

//signals:
private:
    QMediaPlayList *Sloth_Playlist;
    QMap<QModelIndex, QVariant> sloth_data;

private slots:
    void beginInsertItems(int start, int end);
    void endInsertItems();
    void beginRemoveItems(int start, int end);
    void endRemoveItems();
    void changeItems(int start, int end);

};

#endif // SLOTHPLAYLISTMODEL_H*/
