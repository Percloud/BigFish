#include "audiomanager.h"
#include <QMediaContent>
#include <QUrl>
#include <config.h>

AudioManager* AudioManager::s_instance = nullptr;

AudioManager* AudioManager::instance()
{
    if (!s_instance) {
        s_instance = new AudioManager();
    }
    return s_instance;
}

void AudioManager::destroy()
{
    if (s_instance) {
        delete s_instance;
        s_instance = nullptr;
    }
}

AudioManager::AudioManager(QObject* parent)
    : QObject(parent)
{
    // Qt 5.12 音频播放器
    m_bgPlayer = new QMediaPlayer(this);
    m_effectPlayer = new QMediaPlayer(this);

    // 设置默认音量 (0-100)
    m_bgPlayer->setVolume(70);
    m_effectPlayer->setVolume(80);

    // 连接信号实现循环播放（Qt 5.12 不支持 setLoops）
    connect(m_bgPlayer, &QMediaPlayer::mediaStatusChanged,
            this, &AudioManager::onBgMusicEnded);
}

AudioManager::~AudioManager()
{
    m_bgPlayer->stop();
    m_effectPlayer->stop();
}

void AudioManager::onBgMusicEnded()
{
    // 当背景音乐播放结束时，重新播放实现循环
    if (m_bgPlayer->mediaStatus() == QMediaPlayer::EndOfMedia) {
        m_bgPlayer->play();
    }
}

void AudioManager::playBgMusic(BgMusicType type)
{
    QString path;
    switch (type) {
        case START_MUSIC:
            path = bg_music1;
            break;
        case GAME_MUSIC:
            path = bg_music2;
            break;
    }

    m_bgPlayer->setMedia(QMediaContent(QUrl(path)));
    m_bgPlayer->play();
}

void AudioManager::stopBgMusic()
{
    m_bgPlayer->stop();
}

void AudioManager::pauseBgMusic()
{
    m_bgPlayer->pause();
}

void AudioManager::setBgMusicVolume(int volume)
{
    m_bgPlayer->setVolume(qBound(0, volume, 100));
}

void AudioManager::playSoundEffect(SoundEffect effect)
{
    QString path;
    switch (effect) {
        case GET_SCORE:
            path = player_getscore;
            break;
        case LOSE_LIFE:
            path = player_loselife;
            break;
    }

    m_effectPlayer->setMedia(QMediaContent(QUrl(path)));
    m_effectPlayer->play();
}

void AudioManager::setSoundEffectVolume(int volume)
{
    m_effectPlayer->setVolume(qBound(0, volume, 100));
}
