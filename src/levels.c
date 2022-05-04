#include "levels.h"

void createLevel1(Scene* scene)
{
    //Joueurs
    Player player = createPlayer(0, 0, 1, 1, 1, 1, 0, 0);
    Player player2 = createPlayer(-2, 0, 0.5, 2, 1, 0, 1, 0);
    Player player3 = createPlayer(2, 0, 2, 0.5, 1, 0.5, 0, 0.5);
    addPlayerToScene(scene, player, -4, -3);
    addPlayerToScene(scene, player2, 4, -0.5);
    addPlayerToScene(scene, player3, 3, -4.25);

    //Cubes
    Cube cube = createCube(3, -5, 10, 1, 1, 0, 0, 1);
    Cube cube1 = createCube(4, -2, 1, 1, 1, 0, 0, 1);
    Cube cube2 = createCube(-4, -4, 1, 1, 1, 0, 0, 1);
    Cube cube3 = createCube(5, -0.5, 1, 1, 1, 0, 0, 1);
    Cube cube4 = createCube(-5, 0, 1, 1, 1, 0, 0, 1);
    addCubeToScene(scene, cube);
    addCubeToScene(scene, cube1);
    addCubeToScene(scene, cube2);
    addCubeToScene(scene, cube3);
    addCubeToScene(scene, cube4);
    
    //Génération du QuadTree
    generateQuadTree(&scene->quadTree);
}

void createLevel2(Scene* scene)
{
    Scene newScene = createScene();
    
    QuadTree quadTree = createQuadTree(0, 0, 1920,  1080);
    addQuadTreeToScene(&newScene, quadTree);

    //Joueurs
    Player player = createPlayer(0, 0, 1, 1, 1, 1, 0, 0);
    Player player2 = createPlayer(-2, 0, 0.5, 2, 1, 0, 1, 0);
    addPlayerToScene(&newScene, player, -4, -3);
    addPlayerToScene(&newScene, player2, 4, -0.5);

    //Cubes
    Cube cube = createCube(3, -5, 10, 1, 1, 0, 0, 1);
    Cube cube1 = createCube(3, -2, 1, 1, 1, 0, 0, 1);
    Cube cube2 = createCube(-4, -6, 1, 1, 1, 0, 0, 1);
    Cube cube3 = createCube(5, 4, 1, 1, 1, 0, 0, 1);
    Cube cube4 = createCube(5, 3, 3, 1, 1, 0, 0, 1);
    addCubeToScene(&newScene, cube);
    addCubeToScene(&newScene, cube1);
    addCubeToScene(&newScene, cube2);
    addCubeToScene(&newScene, cube3);
    addCubeToScene(&newScene, cube4);
    
    //Génération du QuadTree
    generateQuadTree(&newScene.quadTree);

    *scene = newScene;
}