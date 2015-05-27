#ifndef SLOTHPLAYER_H
#define SLOTHPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDialog>
#include <QWidget>


class QAbstractItemView;
class QLabel;
class QMediaPlayer;

class SlothPlayListModel;

namespace Ui {
class SlothPlayer;
}

class SlothPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit SlothPlayer(QWidget *parent = 0);
    ~SlothPlayer();

private:
    Ui::SlothPlayer *ui;

    QMediaPlayer *SlothMediaPlayerClassic;
    QMediaPlaylist *SlothMediaPlayList;


    //Playlist
    //void addMusicPlayList(const QStringList &FilePlayList);
    //void addMusicMedia(QString FileName);
    //SlothPlayListModel *slothplaylistModel;
    //QAbstractItemView *slothplaylistView;

private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionStop_triggered();

    void on_actionPause_triggered();

    void on_actionBackward_triggered();

    void on_actionForward_triggered();

    //Slider Volume and Progress Moved
    void on_sliderProgress_sliderMoved(int position);
    void on_sliderVolume_sliderMoved(int position);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);

    //void jump(const QModelIndex &index);

};

#endif // SLOTHPLAYER_H
