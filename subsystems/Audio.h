class Audio{
    public:
    Audio();
    ~Audio();
    void playSound(const std::string& soundPath);
    void playMusic(const std::string& musicPath);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void setVolume(int volume);
    void setMusicPosition(int position);
    void setSoundPosition(int position);

};

class SoundListner{ 
    public:
    SoundListner();
    ~SoundListner();
    void setPosition(const glm::vec3& position);
    void setVelocity(const glm::vec3& velocity);
    void setOrientation(const glm::vec3& orientation);
};