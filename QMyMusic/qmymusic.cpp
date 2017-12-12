#include "qmymusic.h"


QMyMusic::QMyMusic(QWidget *parent) : QWidget(parent)
{
    this->setupUi();
    this->init_Player();
    this->connect_signals_slots();

    // 写入样式表
    QFile file(":/music.qss");
    file.open(QFile::ReadOnly);
    QString style = file.readAll();
    this->setStyleSheet(style);
}

/*** 初始化 ****/
/** 初始化 Ui
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-11
 */
void QMyMusic::setupUi()
{
    // 【1】 初始化其他控件
    this->init_Action();
    this->init_Button();
    this->init_Label();
    this->init_Slider();
    this->init_TabWidget();

    // 【2】 布局
    // layout_1 为 1 级布局， layout_2 为 2 级布局
    // layout_2_1 为 2 级布局的第一个布局 ......
    layout_vertical_1     = new QVBoxLayout();
    layout_horizontal_2_1 = new QHBoxLayout();
    layout_horizontal_2_2 = new QHBoxLayout();

    layout_vertical_1->addLayout(layout_horizontal_2_1);
    layout_vertical_1->addWidget(slider_music_duration);
    layout_vertical_1->addLayout(layout_horizontal_2_2);
    layout_vertical_1->addWidget(tabWidget_music);

    // 2级布局 第1个布局 水平布局
    layout_horizontal_2_1->addWidget(btn_music_pre);
    layout_horizontal_2_1->addWidget(btn_music_play_pause);
    layout_horizontal_2_1->addWidget(btn_music_next);
    layout_horizontal_2_1->addWidget(label_music_musicName);
    horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout_horizontal_2_1->addSpacerItem(horizontalSpacer);
    layout_horizontal_2_1->addWidget(label_music_duration1);
    layout_horizontal_2_1->addWidget(label_music_duration2);

    // 2级布局 第2个布局 水平布局
    layout_horizontal_2_2->addWidget(btn_music_playlist);
    layout_horizontal_2_2->addWidget(btn_music_lrc);
    layout_horizontal_2_2->addWidget(btn_music_loop_mode);
    layout_horizontal_2_2->addWidget(btn_music_stop);
    layout_horizontal_2_2->addWidget(btn_music_sound_no);
    layout_horizontal_2_2->addWidget(btn_music_sound);
    layout_horizontal_2_2->addWidget(btn_music_hide_tabWidget);

    this->setLayout(layout_vertical_1);
}

/** 初始化 Player
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::init_Player()
{
    playList = new QMediaPlaylist(this);
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    this->music_playlist_load();
    this->music_playlist_load_lrc();

    player = new QMediaPlayer(this);
    player->setVolume(100);
    player->setPlaylist(playList);
}

/** 连接信号槽
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::connect_signals_slots()
{
    // ''' [1} 播放器 播放事件 '''
    connect(btn_music_play_pause, &QAbstractButton::clicked, this, &QMyMusic::slots_music_btn_play_pause);
    connect(btn_music_pre,  &QAbstractButton::clicked, playList, &QMediaPlaylist::previous);
    connect(btn_music_next, &QAbstractButton::clicked, playList, &QMediaPlaylist::next);


    // """ [2] 播放列表 右键 Action """
    connect(action_music_play, &QAction::triggered, this, &QMyMusic::music_playlist_play);
    connect(action_music_save, &QAction::triggered, this, &QMyMusic::music_playlist_save);
    connect(action_music_add, &QAction::triggered, this, &QMyMusic::music_playlist_add);
    connect(action_music_del_row, &QAction::triggered, this, &QMyMusic::music_playlist_del_row);
    connect(action_music_clear, &QAction::triggered, this, &QMyMusic::music_playlist_clear);


    // """ [3] 播放器 状态更新 """
    connect(player, &QMediaPlayer::durationChanged,
            this, &QMyMusic::music_update_duration);
    connect(player, &QMediaPlayer::positionChanged,
            this, &QMyMusic::music_update_position);
    connect(slider_music_duration, &QSlider::valueChanged,
            this, &QMyMusic::music_update_position_set);
    connect(player, &QMediaObject::metaDataAvailableChanged,
            this, &QMyMusic::music_update_currentmusic);
    connect(player, &QMediaPlayer::stateChanged,
            this, &QMyMusic::music_update_statu);

    // """ [4] 小功能添加 ”“”
    connect(btn_music_playlist, &QAbstractButton::clicked,
            this, &QMyMusic::slots_music_btn_playlist);
    connect(btn_music_lrc, &QAbstractButton::clicked,
            this, &QMyMusic::slots_music_btn_lrc);
    connect(btn_music_stop, &QAbstractButton::clicked,
            this, &QMyMusic::slots_music_btn_stop);
    connect(btn_music_loop_mode, &QAbstractButton::clicked,
            this, &QMyMusic::slots_music_btn_loop);
    connect(btn_music_sound_no, &QAbstractButton::clicked,
            this, &QMyMusic::slots_music_btn_sound_no);
    connect(btn_music_sound, &QAbstractButton::clicked,
            this, &QMyMusic::slots_music_btn_sound);
    connect(btn_music_hide_tabWidget, &QAbstractButton::clicked,
            this, &QMyMusic::slots_music_btn_hide);
}



/*** Ui ****/
/** 初始化 Action
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-11
 */
void QMyMusic::init_Action()
{
    action_music_play    = new QAction("Play");
    action_music_save    = new QAction("Save");
    action_music_add     = new QAction("Add");
    action_music_del_row = new QAction("Del");
    action_music_clear   = new QAction("Clear");
}

/** 初始化 Button
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-11
 */
void QMyMusic::init_Button()
{
    btn_music_pre = new QToolButton();
    btn_music_pre->setIcon(QIcon(":/music_image/music_pre.png"));

    btn_music_play_pause = new QToolButton();
    btn_music_play_pause->setIcon(QIcon(":/music_image/music_play.png"));

    btn_music_next = new QToolButton();
    btn_music_next->setIcon(QIcon(":/music_image/music_next.png"));

    btn_music_loop_mode = new QToolButton();
    btn_music_loop_mode->setIcon(QIcon(":/music_image/music_loop_list.png"));

    btn_music_stop = new QToolButton();
    btn_music_stop->setIcon(QIcon(":/music_image/music_stop.png"));

    btn_music_sound_no = new QToolButton();
    btn_music_sound_no->setIcon(QIcon(":/music_image/music_sound_no.png"));

    btn_music_sound = new QToolButton();
    btn_music_sound->setIcon(QIcon(":/music_image/music_sound.png"));

    btn_music_hide_tabWidget = new QToolButton();
    btn_music_hide_tabWidget->setIcon(QIcon(":/music_image/music_hide.png"));

    btn_music_playlist = new QToolButton();
    btn_music_playlist->setIcon(QIcon(":/music_image/music_playlist.png"));

    btn_music_lrc = new QToolButton();
    btn_music_lrc->setIcon(QIcon(":/music_image/music_lrc.png"));
}

/** 初始化 Label
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-11
 */
void QMyMusic::init_Label()
{
    label_music_musicName = new QLabel();
    label_music_musicName->setText(QStringLiteral("敌敌畏Demo系列"));
    label_music_musicName->setFont(QFont("Microsoft YaHei", 6, 50));
    label_music_musicName->setStyleSheet("color: green");

    label_music_duration1 = new QLabel("0:00");
    label_music_duration1->setFont(QFont("Microsoft YaHei", 6, 50));
    label_music_duration1->setStyleSheet("color: green");

    label_music_duration2 = new QLabel("/0:00");
    label_music_duration2->setFont(QFont("Microsoft YaHei", 6, 50));
    label_music_duration2->setStyleSheet("color: green");
}

/** 初始化 Slider
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-11
 */
void QMyMusic::init_Slider()
{
    slider_music_duration = new QSlider(Qt::Horizontal);
    slider_music_duration->setToolTip("Seek");
}

/** 初始化 TabWidget
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-11
 */
void QMyMusic::init_TabWidget()
{
    // [1] 初始化Tab
    tabWidget_music = new QTabWidget();

    // [2] 初始化Tab1 播放列表
    widget_music_playlist = new QWidget();

    listWidget_music_playlist_content = new QListWidget();
    listWidget_music_playlist_content->setStyleSheet("background-color: rgba(255,255,255,8%); color: green;");
    listWidget_music_playlist_content->setFont(QFont("Microsoft YaHei", 7, 50));
    listWidget_music_playlist_content->setContextMenuPolicy(Qt::ActionsContextMenu);

    listWidget_music_playlist_content->addAction(action_music_play);
    listWidget_music_playlist_content->addAction(action_music_add);
    listWidget_music_playlist_content->addAction(action_music_del_row);
    listWidget_music_playlist_content->addAction(action_music_clear);
    listWidget_music_playlist_content->addAction(action_music_save);

    QVBoxLayout *layout_tab1 = new QVBoxLayout(widget_music_playlist);
    layout_tab1->addWidget(listWidget_music_playlist_content);

    // [3] 初始化Tab2 歌词
    widget_music_lrc = new QWidget();
    listWidget_music_lrc_content = new QListWidget();
    listWidget_music_lrc_content->setStyleSheet("background-color: rgba(255,255,255,8%); color: green;");
    listWidget_music_lrc_content->setFont(QFont("Microsoft YaHei", 7, 50));
    listWidget_music_lrc_content->setContextMenuPolicy(Qt::ActionsContextMenu);

    QVBoxLayout *layout_tab2 = new QVBoxLayout(widget_music_lrc);
    layout_tab2->addWidget(listWidget_music_lrc_content);

    // [4] 添加到TabWidget
    tabWidget_music->addTab(widget_music_playlist, QStringLiteral("歌曲列表"));
    tabWidget_music->addTab(widget_music_lrc, QStringLiteral("歌词"));
    tabWidget_music->setCurrentIndex(0);
}



/*** PlayList ***/
/** palylist 载入
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_playlist_load()
{
    QFile file("D:/EntranceDate/playlist.m3u");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    playList->load(&file, "m3u");
    file.close();

    // QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QFile file2("D:/EntranceDate/playlist.m3u");
    file2.open(QIODevice::ReadWrite | QIODevice::Text);
    QByteArray line;
    QString m_musicName;
    while(!(file2.atEnd()))
    {
        line = file2.readLine();
        m_musicName = codec->toUnicode(line);
        m_musicName = m_musicName.split("/").last();
        m_musicName = m_musicName.split(".").first();
        listWidget_music_playlist_content->addItem(m_musicName);
    }
    file2.close();
}

/** palylist 载入歌词
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_playlist_load_lrc()
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QFile file("D:/EntranceDate/123.lrc");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QByteArray line;
    QString m_musicName;
    while(!(file.atEnd()))
    {
        line = file.readLine();
        m_musicName = codec->toUnicode(line);
        m_musicName.remove("\n");
        m_musicName = m_musicName.split("]").last();
        listWidget_music_lrc_content->addItem(m_musicName);
    }
    file.close();
}

/** palylist 槽函数 添加
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_playlist_add()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    filePath = QFileDialog::getOpenFileName(NULL, QStringLiteral("Open File"),
                            musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                            QStringLiteral("MP3 files (*.mp3) ;; All files (*.*)"));

    if(!filePath.isEmpty())
    {
        playList->addMedia(QUrl::fromLocalFile(filePath));
        musicName = QFileInfo(filePath).fileName().split(".").first();
        listWidget_music_playlist_content->addItem(musicName);
    }
    else
    {
        return;
    }
}

/** palylist 槽函数 删除
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_playlist_del_row()
{
   int row = listWidget_music_playlist_content->currentRow();

   // 删除歌曲列表中的数据
   playList->removeMedia(row);

   // 删除表单中的数据
   listWidget_music_playlist_content->takeItem(row);
}

/** palylist 槽函数 清空
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_playlist_clear()
{
    playList->clear();  // 歌曲列表清空

    listWidget_music_playlist_content->clear();     // 表单控件清空
}

/** palylist 槽函数 播放
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_playlist_play()
{
    int row = listWidget_music_playlist_content->currentRow();

    playList->setCurrentIndex(row);
    player->play();
}

/** palylist 槽函数 保存
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_playlist_save()
{
    QFile file("D:/EntranceDate/playlist.m3u");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    this->playList->save(&file, "m3u");
    file.close();
}



/*** Player ***/
/** palyer 槽函数 更新播放状态
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_update_statu(QMediaPlayer::State state)
{
    if(state == QMediaPlayer::PlayingState)
    {
        btn_music_play_pause->setIcon(QIcon(":/music_image/music_pause.png"));
    }
    else
    {
        btn_music_play_pause->setIcon(QIcon(":/music_image/music_play.png"));
    }
}

/** palyer 槽函数 更新播放进度
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_update_duration(qint64 duration)
{
    duration = player->metaData("Duration").toInt();
    slider_music_duration->setRange(0, duration);
    slider_music_duration->setPageStep(duration/10);

    // 更新 Label 歌曲总时间
    QTime m_duration(0, duration/60000, qRound((duration % 60000) / 1000.0));
    label_music_duration2->setText(m_duration.toString("/ m:ss"));
}

/** palyer 槽函数 更新slider进度
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_update_position(qint64 position)
{
    slider_music_duration->setValue(position);
    QTime m_duration(0, position / 60000, qRound((position % 60000) / 1000.0));

    // 更新Label
    label_music_duration1->setText(m_duration.toString(QStringLiteral("m:ss")));
}

/** palyer 槽函数 设置播放进度
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_update_position_set(int position)
{
    if (qAbs(player->position()-position) > 99)
    {
        player->setPosition(position);
    }
}

/** palyer 槽函数 更新歌曲信息
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-12
 */
void QMyMusic::music_update_currentmusic()
{
    QString title;
    title = player->metaData("Title").toString();
    label_music_musicName->setText(title);
}



/*** BTN ***/
/** palyer 槽函数 播放/暂停
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_play_pause()
{
    if (player->mediaStatus() == QMediaPlayer::NoMedia)
    {
        music_playlist_add();
    }
    else if (player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
        btn_music_play_pause->setIcon(QIcon(":/music_image/music_play.png"));
    }
    else
    {
        player->play();
        btn_music_play_pause->setIcon(QIcon(":/music_image/music_pause.png"));
    }
}

/** palyer 槽函数 歌曲列表
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_playlist()
{
    tabWidget_music->show();
    tabWidget_music->setCurrentIndex(0);
}

/** palyer 槽函数 歌词
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_lrc()
{
    tabWidget_music->show();
    tabWidget_music->setCurrentIndex(1);
}

/** palyer 槽函数 停止
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_stop()
{
    if (!(player->mediaStatus() == QMediaPlayer::NoMedia))
    {
        player->stop();
    }
}

/** palyer 槽函数 循环模式
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_loop()
{
    if(playList->playbackMode() == QMediaPlaylist::Loop)
    {
        playList->setPlaybackMode(QMediaPlaylist::Random);
        btn_music_loop_mode->setIcon(QIcon(":/music_image/music_loop_random .png"));
    }
    else if(playList->playbackMode() == QMediaPlaylist::Random)
    {
        playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        btn_music_loop_mode->setIcon(QIcon(":/music_image/music_loop_single.png"));
    }
    else
    {
        playList->setPlaybackMode(QMediaPlaylist::Loop);
        btn_music_loop_mode->setIcon(QIcon(":/music_image/music_loop_list.png"));
    }
}

/** palyer 槽函数 静音
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_sound_no()
{
    player->setVolume(0);
}

/** palyer 槽函数 音量
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_sound()
{
    int value = player->volume();
    value += 1;
    player->setVolume(value);
}

/** palyer 槽函数 隐藏/显示tabWidget
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-13
 */
void QMyMusic::slots_music_btn_hide()
{
    if (!tabWidget_music->isHidden())
    {
        tabWidget_music->hide();
        btn_music_hide_tabWidget->setIcon(QIcon(":/music_image/music_show.png"));
    }
    else
    {
        tabWidget_music->show();
        btn_music_hide_tabWidget->setIcon(QIcon(":/music_image/music_hide.png"));
    }
}



