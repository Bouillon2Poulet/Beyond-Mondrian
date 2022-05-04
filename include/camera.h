#ifndef CAMERA_H
#define CAMERA_H

#include "player.h"

#define ZOOM_ON_PLAYER 100

typedef struct Camera {
    float x;
    float y;
    float speed;
} Camera;

Camera createCamera(float x, float y);

void moveCamera(Camera* camera, Player player);

#endif