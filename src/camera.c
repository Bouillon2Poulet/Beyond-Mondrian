#include <GL/gl.h>
#include "camera.h"

Camera createCamera(float x, float y)
{
    Camera camera;
    camera.x = x;
    camera.y = y;
    camera.speed = 0.1;
    return camera;
}

void moveCamera(Camera* camera, Player player)
{
    camera->x += (-player.cube.x - camera->x) * camera->speed;
    camera->y += (-player.cube.y - camera->y) * camera->speed;
    glTranslatef(camera->x, camera->y, 0);
}