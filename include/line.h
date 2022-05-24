#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
#include <GL/glu.h>
struct Scene;

typedef struct BackgroundLine {
    int width;
    int mode;
    int sens;
    int xStart;
    int yStart;
    int speedFactor;
    Uint32 time;
    Uint32 endTime;
    float r;
    float g;
    float b;
} BackgroundLine;

#include "scene.h"

BackgroundLine createBackgroundLine(int width, int mode, int sens, int xStart,int yStart, int time, int endTime, float r, float g, float b);
void updateBackgroundLine(BackgroundLine* line);
void drawLine(BackgroundLine line);
BackgroundLine randomNewLine();
void fillSceneLineTab(Scene* scene);
void addRandomLineToScene (Scene* scene);
void displayLineInfo (BackgroundLine line);
#endif