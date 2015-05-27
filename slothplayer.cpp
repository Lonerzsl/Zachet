#include "slothplayer.h"
#include "ui_slothplayer.h"
//#include "slothplaylistmodel.h"

#include <QtWidgets>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QMediaService>

SlothPlayer::SlothPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SlothPlayer)
{
    ui->setupUi(this);


    SlothMediaPlayerClassic     =   new QMediaPlayer(this);
    SlothMediaPlayList          =   new QMediaPlaylist;
    SlothMediaPlayerClassic->setPlaylist(SlothMediaPlayList);

    connect(SlothMediaPlayerClassic, &QMediaPlayer::positionChanged, this, &SlothPlayer::on_positionChanged);
    connect(SlothMediaPlayerClassic, &QMediaPlayer::durationChanged, this, &SlothPlayer::on_durationChanged);








    //Плейлист не удался
   /* connect(SlothMediaPlayerClassic, SIGNAL(current)

    slothplaylistModel = new SlothPlayListModel(this);
    slothplaylistModel->setPlaylist(SlothMediaPlayList);

    slothplaylistView = QListView(this);
    slothplaylistView->setModel(slothplaylistModel);
    slothplaylistView->setCurrentIndex(slothplaylistModel->index(SlothMediaPlayList->currentIndex(), 0));

    connect(slothplaylistView, SIGNAL(activated(QModelIndex)), this, SLOT(jump(QModelIndex)));


    QStringList argument = qApp->arguments();
    argument.removeAt(0);
    addMusicPlayList(argument);*/
}

SlothPlayer::~SlothPlayer()
{
    delete ui;
}

void SlothPlayer::on_sliderProgress_sliderMoved(int position)
{
    SlothMediaPlayerClassic->setPosition(position);
}

void SlothPlayer::on_sliderVolume_sliderMoved(int position)
{
    SlothMediaPlayerClassic->setVolume(position);
}

void SlothPlayer::on_actionOpen_triggered()
{
    QString FilePlayList = QFileDialog::getOpenFileName(this, "Open File");
    if (!FilePlayList.isEmpty()) {
        SlothMediaPlayerClassic->setMedia(QUrl::fromLocalFile(FilePlayList));
        /*if (FilePlayList.count()>1)
            addMusicPlayList(FilePlayList);
        else
            addMusicMedia(FilePlayList.first());*/
    }
}
/*void SlothPlayer::addMusicMedia(QString FileName)
{
    SlothMediaPlayerClassic->setMedia(QUrl::fromLocalFile(FileName));
    SlothPlayer::setWindowTitle(FileName);

void SlothPlayer::addMusicPlayList(const QStringList &FilePlayList)
{
    foreach (QString const &argument, FilePlayList){
        QFileInfo fileInfo(argument);
        if (fileInfo.exists()){
            QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
            if (fileInfo.suffix().toLower() == QLatin1String("m3u")){
                SlothMediaPlayList->load(url);
            }   else
                SlothMediaPlayList->addMedia(url);
        }   else    {
            QUrl url(argument);
            if (url.isValid()){
                SlothMediaPlayList->addMedia(url);
            }
        }
    }
}}*/


void SlothPlayer::on_actionPlay_triggered()
{
    SlothMediaPlayerClassic->play();
}

void SlothPlayer::on_actionStop_triggered()
{
    SlothMediaPlayerClassic->pause();
}

void SlothPlayer::on_actionPause_triggered()
{
    SlothMediaPlayerClassic->stop();
}

void SlothPlayer::on_actionBackward_triggered()
{
    //
}

void SlothPlayer::on_actionForward_triggered()
{
   //
}


void SlothPlayer::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

void SlothPlayer::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
}

/*void SlothPlayer::jump(const QModelIndex &index)
{
    if(index.isValid()){
        SlothMediaPlayList->setCurrentIndex(index.row());
        SlothMediaPlayerClassic->play();
    }
}*/


