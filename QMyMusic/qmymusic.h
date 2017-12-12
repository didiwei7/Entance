#ifndef QMYMUSIC_H
#define QMYMUSIC_H

#include "qmymusic_global.h"


#include <QtWidgets>
#include <QWidget>

#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include <QIODevice>
#include <Windows.h>
#include <QDesktopServices>

#include <QFileDialog>
#include <QTime>
#include <QTextCodec>
#include <QEvent>
#include <QCloseEvent>

class QMYMUSICSHARED_EXPORT QMyMusic : public QWidget
{
    Q_OBJECT
public:
    explicit QMyMusic(QWidget *parent = 0);

private:
    void setupUi();
    void init_Action();
    void init_Button();
    void init_Label();
    void init_Slider();
    void init_TabWidget();

private:
    void init_Player();
    void music_playlist_load();
    void music_playlist_load_lrc();

private:
    void connect_signals_slots();

private slots:
    void music_playlist_add();
    void music_playlist_del_row();
    void music_playlist_clear();
    void music_playlist_save();
    void music_playlist_play();

private slots:
    void music_update_statu   (QMediaPlayer::State state);
    void music_update_duration(qint64 position);
    void music_update_position(qint64 duration);
    void music_update_position_set(int position);
    void music_update_currentmusic();

private slots:
    void slots_music_btn_play_pause();
    void slots_music_btn_playlist();
    void slots_music_btn_lrc();
    void slots_music_btn_stop();
    void slots_music_btn_loop();
    void slots_music_btn_sound_no();
    void slots_music_btn_sound();
    void slots_music_btn_hide();

private:
    // BTN
    QToolButton *btn_music_play_pause;
    QToolButton *btn_music_pre;
    QToolButton *btn_music_next;

    QToolButton *btn_music_playlist;
    QToolButton *btn_music_lrc;
    QToolButton *btn_music_stop;
    QToolButton *btn_music_loop_mode;
    QToolButton *btn_music_sound_no;
    QToolButton *btn_music_sound;
    QToolButton *btn_music_hide_tabWidget;

    // Label
    QLabel *label_music_musicName;
    QLabel *label_music_duration1;
    QLabel *label_music_duration2;

    // Slider
    QSlider *slider_music_duration;

    // TabWidget
    QTabWidget *tabWidget_music;

    QWidget *widget_music_playlist;                  // Tab1 Widget playlist
    QListWidget *listWidget_music_playlist_content;  // Tab1 Widget ListWidget playlist content

    QWidget *widget_music_lrc;                       // Tab2 Widget lrc
    QListWidget *listWidget_music_lrc_content;       // Tab2 Widget ListWidget lrc content

    QAction *action_music_separetor;
    QAction *action_music_play;
    QAction *action_music_add;
    QAction *action_music_del_row;
    QAction *action_music_clear;
    QAction *action_music_save;

    QVBoxLayout *layout_vertical_1;                  // 1级布局 垂直布局
    QHBoxLayout *layout_horizontal_2_1;              // 2级布局 第1个布局是 水平布局
    QHBoxLayout *layout_horizontal_2_2;              // 2级布局 第2个布局是 水平布局

    QSpacerItem *horizontalSpacer;

private:
    QMediaPlayer   *player;                 // 播放设备
    QMediaPlaylist *playList;               // 播放列表

private:
    QString  filePath;
    QString  musicName;                     // 音乐名
};

#endif // QMYMUSIC_H
