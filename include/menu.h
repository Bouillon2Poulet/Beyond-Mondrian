#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_TEXTURE_COUNT 10

typedef struct StartMenu {
    Uint32 deltaTime;
    GLuint textureTab[MAX_TEXTURE_COUNT];
    int nbTextures;
} StartMenu;

GLuint loadTextureStartMenu (int indexTexture, StartMenu menu);
SDL_Surface* IMG_Load(const char* filename);
GLuint drawCase(int w, int h);
StartMenu createStartMenu();
void updateMenu(StartMenu* menu, Uint32 deltaTime);
void drawMenu(StartMenu menu);

#endif