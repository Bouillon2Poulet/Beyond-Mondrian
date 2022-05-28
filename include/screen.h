#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "background.h"

#define MAX_TEXTURE_COUNT 10

typedef struct Screen {
    GLuint textureTab[MAX_TEXTURE_COUNT];
    int type; //0 for start screen, 1 for end screen
    int nbTextures;
    BackgroundLine tabLines[5];
} Screen;

GLuint loadTextureScreen (int indexTexture, Screen screen);
SDL_Surface* IMG_Load(const char* filename);
GLuint drawCase(int w, int h);
Screen createScreen(int mode);
void drawScreen(Screen* screen);
void displayImage(int x, int y, GLuint texture);

#endif