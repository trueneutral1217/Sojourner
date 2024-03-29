#include "audio.h"

audio::audio()
{
    music = NULL;
    sound = NULL;
    voice = NULL;
    musicToggle = true;
    voiceToggle = true;
}
audio::~audio()
{
    //
    Mix_FreeMusic( music );
    Mix_FreeChunk( sound );
    Mix_FreeChunk( voice );
    sound=NULL;
    music=NULL;
    voice=NULL;
}

void audio::loadMusic()
{
    std::cout<<"\n running audio::loadMusic()";
    //music = Mix_LoadMUS( "music/koi/Koi-discovery - Blitz-Nevrosis.mp3" );

    switch( rand() % 7 )
    {
        case 0:
            music = Mix_LoadMUS( "music/koi/Koi-discovery - Blitz-Nevrosis.mp3" );
            std::cout<<"\n\n loaded blitz-nevrosis.mp3";
        break;
        case 1:
            music = Mix_LoadMUS( "music/koi/Koi-discovery - Empsykoun.mp3" );
            std::cout<<"\n\n loaded empsykoun.mp3";
            break;
        case 2:
            music = Mix_LoadMUS( "music/koi/Koi-discovery - Polylove.mp3" );
            std::cout<<"\n\n loaded polylove.mp3";
            break;
        case 3:
            music = Mix_LoadMUS( "music/koi/Koi-discovery - Rouge-haine-les-9-ames.mp3" );
            std::cout<<"\n\n loaded rouge-haine-les-9-ames.mp3";
            break;
        case 4:
            music = Mix_LoadMUS( "music/koi/Koi-discovery - The lost cyborg.mp3" );
            std::cout<<"\n\n loaded the lost cyborg.mp3";
            break;
        case 5:
            music = Mix_LoadMUS( "music/koi/Koi-discovery - There-is-someone.mp3" );
            std::cout<<"\n\n loaded there-is-someone.mp3";
            break;
        case 6:
            music = Mix_LoadMUS( "music/koi/Koi-discovery - Vortex-temporalis.mp3" );
            std::cout<<"\n\n loaded vortex-temporalis.mp3";
            break;

    }
}

void audio::loadChapter1Music()
{
    //this is an artifact
    std::cout<<"\n running audio::loadChapter1Music()";
    music = Mix_LoadMUS("music/Meadow March.mp3");
}

void audio::loadChapter2Music()
{
    //this is an artifact
    std::cout<<"\n running audio::loadChapter2Music()";
    music = Mix_LoadMUS("music/Tiki Jungle.mp3");
}

void audio::loadChapter3Music()
{
    //this is an artifact
    std::cout<<"\n running audio::loadChapter3Music()";
    music = Mix_LoadMUS("music/Radioactive Rain.mp3");
}

void audio::loadSound(int soundNum)
{
    std::cout<<"\n running audio::loadSound(int soundNum)";
    switch(soundNum)
    {
        case 0:
            sound = Mix_LoadWAV( "sounds/voice0.mp3" );
        break;
        case 1:
            sound = Mix_LoadWAV( "sounds/gem.mp3" );
        break;
        case 2:
            sound = Mix_LoadWAV( "sounds/shovel.mp3" );
        break;
        case 3:
            sound = Mix_LoadWAV( "sounds/titleitemselect4.wav" );
        break;
        case 4:
            sound = Mix_LoadWAV( "sounds/beam.mp3");
        break;
        case 5:
            sound = Mix_LoadWAV( "sounds/3beeps.mp3");
        break;
    }
}

void audio::loadVoice(int chapter,int page,int line)
{
    //this is an artifact
    std::cout<<"\n running audio::loadVoice(int chapter,int page,int line)";
    std::string voiceString = "sounds/voice acting/chapter"+std::to_string(chapter + 1)+"/c"+std::to_string(chapter+1)+"p"+std::to_string(page+1)+"l"+std::to_string(line+1)+".mp3";
    voice = Mix_LoadWAV( voiceString.c_str() );
}

void audio::stopVoice()
{
    std::cout<<"\n running audio::stopVoice()";
    //Mix_PlayChannel(-1,voice,0);
    Mix_HaltChannel(-1);
}

void audio::freeAudio()
{
    std::cout<<"\n running audio::freeAudio()";
    Mix_FreeChunk( sound );
    sound = NULL;
    Mix_FreeChunk( voice );
    voice = NULL;
    Mix_FreeMusic( music );
	music = NULL;
}

void audio::playSound()
{
    std::cout<<"\n running audio::playSound()";
    Mix_PlayChannel( -1, sound, 0 );
}

void audio::playVoice()
{
    std::cout<<"\n running audio::playVoice()";
    if(voiceToggle)
    {
        Mix_PlayChannel(-1,voice,0);
    }
}

void audio::playMusic()
{
    std::cout<<"\n running audio::playMusic()";
    if(musicToggle)
    {
        if( Mix_PlayingMusic() == 0 )
        {
            //Play the music
            Mix_PlayMusic( music, -1 );
        }
        //If music is being played
        else
        {
            //If the music is paused
            if( Mix_PausedMusic() == 1 )
            {
                //Resume the music
                Mix_ResumeMusic();
            }
            //If the music is playing
            else
            {
                //Pause the music
                Mix_PauseMusic();
            }
        }
    }

}

void audio::pauseMusic()
{
    std::cout<<"\n running audio::pauseMusic()";
    Mix_PauseMusic();
}

void audio::resumeMusic()
{
    std::cout<<"\n running audio::resumeMusic()";
    if(musicToggle)
    {
        Mix_ResumeMusic();
    }
}

void audio::stopMusic()
{
    std::cout<<"\n running audio::stopMusic()";
    Mix_HaltMusic();
    loadMusic();
}

void audio::resetMusic()
{
    std::cout<<"\n running audio::resetMusic()";
    stopMusic();
    loadMusic();
    playMusic();
}

bool audio::isPlaying()
{
   // std::cout<<"\n running audio::isPlaying()";
    return Mix_PlayingMusic();
}




