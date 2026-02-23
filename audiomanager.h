#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QMediaPlayer>

// 音频管理器（单例模式，Qt 5.12 兼容）
class AudioManager : public QObject
{
    Q_OBJECT

public:
    enum BgMusicType {
        START_MUSIC,
        GAME_MUSIC
    };

    enum SoundEffect {
        GET_SCORE,
        LOSE_LIFE
    };

    static AudioManager* instance();
    static void destroy();

    // 背景音乐控制
    void playBgMusic(BgMusicType type);
    void stopBgMusic();
    void pauseBgMusic();
    void setBgMusicVolume(int volume);

    // 音效控制
    void playSoundEffect(SoundEffect effect);
    void setSoundEffectVolume(int volume);

private slots:
    void onBgMusicEnded();  // 背景音乐结束时重新播放（Qt 5.12 循环播放）

private:
    explicit AudioManager(QObject* parent = nullptr);
    ~AudioManager();

    QMediaPlayer* m_bgPlayer;
    QMediaPlayer* m_effectPlayer;

    static AudioManager* s_instance;
};

#endif // AUDIOMANAGER_H
