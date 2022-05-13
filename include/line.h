#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
struct Scene;

typedef struct BackgroundLine {
    int width;
    int mode;
    int sens;
    int xStart;
    int yStart;
    int time;
    int endTime;
    float r;
    float g;
    float b;
} BackgroundLine;

#include "scene.h"

BackgroundLine createBackgroundLine(int width, int mode, int sens, int xStart,int yStart, int time, int endTime, float r, float g, float b);
void updateBackgroundLine(BackgroundLine* line, Uint32 deltatime);
void drawLine(BackgroundLine line);
BackgroundLine randomNewLine();
void fillSceneLineTab(Scene* scene);
#endif