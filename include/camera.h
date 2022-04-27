#ifndef CAMERA_H
#define CAMERA_H

#include "player.h"

typedef struct Camera {
    float x;
    float y;
    float speed;
} Camera;

Camera createCamera(float x, float y);

void moveCamera(Camera* camera, Player player);

#endif