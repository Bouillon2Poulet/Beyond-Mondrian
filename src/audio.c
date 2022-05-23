#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>

void loadMusic(Mix_Music** music) 
{
    *music = Mix_LoadMUS("./assets/audio/menu.mp3");

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    return;
}