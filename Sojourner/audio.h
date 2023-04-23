#ifndef AUDIO_H
#define AUDIO_H

#include "texture.h"
#include <SDL_mixer.h>

const int TOTAL_SOUNDS = 6;

class audio
{
    public:

        Mix_Music *music;
        Mix_Chunk *sound;
        Mix_Chunk *voice;
        audio();
        ~audio();


        //if musicToggle or voiceToggle == false, no voice or music will be played.
        bool voiceToggle;
        bool musicToggle;

        //music
        void loadMusic();
        void loadChapter1Music();
        void loadChapter2Music();
        void loadChapter3Music();
        //sounds
        void loadSound(int soundNum);

        void loadVoice(int chapter, int page,int line);

        void playMusic();
        void pauseMusic();
        void resumeMusic();
        void stopMusic();
        bool isPlaying();
        void playSound();
        void playVoice();
        void stopVoice();
        void freeAudio();
        //resets pregame music
        void resetMusic();
        //resets music for the individual chapters
        /*void resetChapter1Music();
        void resetChapter2Music();
        void resetChapter3Music();*/

    private:

};
#endif // AUDIO_H
