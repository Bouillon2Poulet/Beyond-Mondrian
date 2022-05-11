#include "levels.h"

void createLevel1(Scene* scene)
{
    //Joueurs
    Player player = createPlayer(0, 0, 1, 1, 1, 1, 0, 0);
    // create player : Posx, Posy, largeur, hauteur, fill?, R,G,B
    Player player2 = createPlayer(-2, 0, 0.5, 2, 1, 0, 1, 0);
    Player player3 = createPlayer(2, 0, 2, 0.5, 1, 0.5, 0, 0.5);
    addPlayerToScene(scene, player, 34, -2);
    addPlayerToScene(scene, player2, 10, -7.5);
    addPlayerToScene(scene, player3, 21, 7.5);

    //Cubes

    //Cadre dessus/dessous
    Cube cube = createCube(12, -10, 30, 3, 1, 1, 1, 1);
    Cube cube1 = createCube(12, 10, 30, 3, 1, 0, 0, 1);

    //Cadre Coté Gauche (jaune)
    Cube cube2 = createCube(-1, -10, 5, 3, 1, 1, 1, 0);
    Cube cube3 = createCube(-1, 10, 5, 3, 1, 1, 1, 0);
    Cube cube4 = createCube(-3.4, 0, 0.2, 20, 1, 1, 1, 0);

    //Cadre Coté Droit (rouge)
    Cube cube5 = createCube(30, -7, 7, 9, 1, 1, 0, 0);
    Cube cube6 = createCube(30, 6, 7, 11, 1, 1, 0, 0);
    Cube cube7 = createCube(34, -2.6, 1.4, 0.2, 1, 1, 0, 0);
    Cube cube8 = createCube(34.7, -1, 0.2, 3.4, 1, 1, 0, 0);
    Cube cube9 = createCube(34, 0.6, 1.4, 0.2, 1, 1, 0, 0);

    //Elements du jeu
    Cube cube10 = createCube(8, -7.5, 2, 2, 1, 1, 1, 1);
    Cube cube11 = createCube(10.5, -5, 2, 2, 1, 1, 1, 1);
    Cube cube12 = createCube(11.5, -7.5, 2, 3, 1, 1, 1, 1);

    Cube cube13 = createCube(13, 2, 2, 0.2, 1, 1, 1, 1);
    Cube cube14 = createCube(15, 3, 2, 0.2, 1, 1, 1, 1);
    Cube cube15 = createCube(21, 7, 2, 0.2, 1, 1, 1, 1);



    


    addCubeToScene(scene, cube);
    addCubeToScene(scene, cube1);
    addCubeToScene(scene, cube2);
    addCubeToScene(scene, cube3);
    addCubeToScene(scene, cube4);
    addCubeToScene(scene, cube5);
    addCubeToScene(scene, cube6);
    addCubeToScene(scene, cube7);
    addCubeToScene(scene, cube8);
    addCubeToScene(scene, cube9);
    addCubeToScene(scene, cube10);
    addCubeToScene(scene, cube11);
    addCubeToScene(scene, cube12);
    addCubeToScene(scene, cube13);
    addCubeToScene(scene, cube14);
    addCubeToScene(scene, cube15);


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