#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>

void loadMusic(Mix_Music** music,int index) 
{
    const char* names[2] = {"menu.mp3","jump.mp3"};
    char fileName[150];
    sprintf(fileName,"assets/audio/%s",names[index]);

    *music = Mix_LoadMUS(fileName);

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    return;
}