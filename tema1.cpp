
#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <cstdlib>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "lab_m1/tema1/Obstacle.h"
#include "lab_m1/tema1/Enemy.h"
#include "lab_m1/tema1/Projectile.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{   

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height
    //harta si obstacole
    MapX = 0;
    MapY = 0;
    MapScaleX = 20;
    MapScaleY = 20;
    glm::vec3 corner = glm::vec3(0, 0, 0);
    length = 1;
    //Create obstacles
    obs.push_back(Obstacle(3, 2, 1, 1));
    obs.push_back(Obstacle(2, 3, 1, 1));
    obs.push_back(Obstacle(6, 7, 1.5, 2));
    obs.push_back(Obstacle(18, 18, 1, 1));
    obs.push_back(Obstacle(15, 16.5, 3, 1));
    obs.push_back(Obstacle(12, 2, 1.5, 3));
    obs.push_back(Obstacle(5, 6, 2, 3));
    obs.push_back(Obstacle(5, 7, 0.5, 1));
    obs.push_back(Obstacle(10, 4, 1, 2));
    obs.push_back(Obstacle(7, 8, 5, 2));
    obs.push_back(Obstacle(3, 14, 2, 2));
    obs.push_back(Obstacle(10, 10, 3, 2));
    obs.push_back(Obstacle(18, 2, 1.5, 2.5));
    obs.push_back(Obstacle(1, 18, 3, 0.5));
    obs.push_back(Obstacle(18, 10, 1, 2));
    obs.push_back(Obstacle(13, 10, 2, 1.5));
    obs.push_back(Obstacle(19, 8, 0.5, 2));
    obs.push_back(Obstacle(14, 15, 1.5, 1.5));
    obs.push_back(Obstacle(16, 12, 1.5, 3));
    obs.push_back(Obstacle(7, 13, 1, 2));
    obs.push_back(Obstacle(7, 3, 1, 3));
    obs.push_back(Obstacle(1.5, 5, 0.5, 4));
    obs.push_back(Obstacle(3.5, 3.5, 1, 1));
    obs.push_back(Obstacle(8.5, 16.5, 1.5, 2.5));
    obs.push_back(Obstacle(11.5, 19, 1, 0.5));
    //margine harta
    obs.push_back(Obstacle(0, 0, 20, 0.1));
    obs.push_back(Obstacle(0, 0, 0.1, 20));
    obs.push_back(Obstacle(19.7, 0, 0.1, 20));
    obs.push_back(Obstacle(0, 19.7, 20, 0.1));
   
    //create enemies
    enemies.push_back(Enemy(10, 1, 1));
    enemies.push_back(Enemy(15, 2, 1));
    enemies.push_back(Enemy(14, 4.5, 1));
    old.push_back(Enemy(10, 1, 1));
    old.push_back(Enemy(15, 2, 1));
    old.push_back(Enemy(14, 4.5, 1));
    time = 6;
    randX = rand() % 20;
    randY = rand() % 20;
    enemySpeed = rand() % 5;
    //create projectiles
    speedProjectile = 5;
    lengthProjectile = 0.1f;
    projectileCreate = false;
    projectileX = 0;
    projectileY = 0;
    projectileTime = 0.5f;
    projectileTime2 = 3;
    //creeare jucator
    radius = 0.08f;
    lenghtCerc = 0.2f;
    offsetPlayer = 0.11f;
    centerPlayerX = 0.0f;
    centerPlayerY = 0.0f;
    cercX = logicSpace.width / 2;
    cercY = logicSpace.height / 2;
    scalePlayerX = 0.2f;
    scalePlayerY = 0.2f;
    scaleHandX = 0.15f;
    scaleHandY = 0.15f;
    //creeare inamici
    lengthEnemyHand = 0.11f;
    lengthEnemy = 0.35f;
    offset = 0.07f;
    width = 1;

    angularMouse1 = 0;
    angularMouse = 0;

    //creeare healthBar si scoreBar
    nr_lives_left = 5;
    healthBarX = logicSpace.x + logicSpace.width - 1.5f;
    healthBarY = logicSpace.y + logicSpace.height - 0.5f;
    score = 0;
    lengthHealtBar = 1;

    //coliziuni
    X = 0;
    Y = 0;
    oldLogicX = 0;
    oldLogicY = 0;
    //adaugare in memorie a formelor
    Mesh* Projectile = object2D::CreateSquare("Projectile", corner, lengthProjectile , glm::vec3(255, 0, 0), true);
    AddMeshToList(Projectile);
    Mesh* Enemy = object2D::CreateSquare("Enemy", corner, lengthEnemy, glm::vec3(0, 0, 0), true);
    AddMeshToList(Enemy);
    Mesh* enemyHand = object2D::CreateSquare("enemyHand", corner, lengthEnemyHand, glm::vec3(0, 0, 0), true);
    AddMeshToList(enemyHand);
    Mesh* Player = object2D::CreateCircle("Player", lenghtCerc, 0.0f, 0.0f, glm::vec3(1, 1, 0), true);
    AddMeshToList(Player);
    Mesh* playerHand = object2D::CreateCircle("playerHand", radius, 0.0f, 0.0f, glm::vec3(1, 1, 1));
    AddMeshToList(playerHand);
    Mesh* squareMap = object2D::CreateSquare("squareMap", corner, length, glm::vec3(0.5f, 0.5f, 0.5f), true);
    AddMeshToList(squareMap);
    Mesh* rectangleObs = object2D::CreateRectangle("rectangleObs", corner, width, length, glm::vec3(0, 1, 0), true);
    AddMeshToList(rectangleObs);
    Mesh* healthBar = object2D::CreateRectangle("healthBar", corner, width, lengthHealtBar, glm::vec3(255, 0, 0), false);
    AddMeshToList(healthBar);
    Mesh* healthBar2 = object2D::CreateRectangle("healthBar2", corner, width, lengthHealtBar, glm::vec3(255, 0, 0), true);
    AddMeshToList(healthBar2);
}


glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//coliziune rectangle-rectangle si cerc-rectangle
int CheckCollision1(float r1X, float r1Y, float r1L, float r1W, float r2X, float r2Y, float r2L, float r2W) // AABB - AABB collision
{
    // collision x-axis?
    int okX = 0;
    int okY = 0;
    
    if ((r1X + r1L >= r2X) && (r2X + r2L >= r1X)) {
        okX = 1;
    }
  
    // collision y-axis?
    if ((r1Y + r1W >= r2Y) && (r2Y + r2W >= r1Y)) {
        okY = 1;
    }
    if (okX && okY) {
        return 1;
    }
    // collision only if on both axes
    return 0;
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    // The viewport is now the right half of the window
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    // Compute uniform 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    

    //healthBAr
    modelMatrix = visMatrix * transform2D::Translate(healthBarX, healthBarY) * transform2D::Scale(nr_lives_left * 0.1f, 0.05);
    RenderMesh2D(meshes["healthBar2"], shaders["VertexColor"], modelMatrix);
    modelMatrix = visMatrix * transform2D::Translate(healthBarX, healthBarY) * transform2D::Scale(0.5, 0.05);
    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], modelMatrix);

    //creeare 2 inamici la cate 5 secunde
    for (Enemy e : enemies) {
        if (e.is == 1) {
            modelMatrix = visMatrix * transform2D::Translate(e.x, e.y);
            RenderMesh2D(meshes["Enemy"], shaders["VertexColor"], modelMatrix);
            modelMatrix = visMatrix * transform2D::Translate(e.x + lengthEnemy - offset, e.y - offset);
            RenderMesh2D(meshes["enemyHand"], shaders["VertexColor"], modelMatrix);
            modelMatrix = visMatrix * transform2D::Translate(e.x + lengthEnemy - offset, e.y + lengthEnemy - offset);
            RenderMesh2D(meshes["enemyHand"], shaders["VertexColor"], modelMatrix);
        }
    }
    //creeare 2 inamici la cate 6 secunde
    if (time == 6) {
        enemies.push_back(Enemy(randX, randY, 1));
        old.push_back(Enemy(randX, randY, 1));
        randX = rand() % 20;
        randY = rand() % 20;
        enemies.push_back(Enemy(randX, randY, 1));
        old.push_back(Enemy(randX, randY, 1));
        randX = rand() % 20;
        randY = rand() % 20;
    }
    time = time - deltaTimeSeconds/2;
    if (time <= 0) {
        time = 6;
    }
    //Orientare inamici
    for ( int i = 0; i < enemies.size(); i++ ) {
        enemySpeed = (1 + rand()) % 4;
        if (enemies[i].x < cercX) {
            
            enemies[i].x += deltaTimeSeconds / 2 * enemySpeed;
        }
        else {
            
            enemies[i].x -= deltaTimeSeconds / 2 * enemySpeed;
        }
        if (enemies[i].y < cercY) {
            
            enemies[i].y += deltaTimeSeconds / 2 * enemySpeed;
        }
        else {
            
            enemies[i].y -= deltaTimeSeconds / 2 * enemySpeed;
        }
    }
    //creeare proiectil
    projectileTime -= deltaTimeSeconds;
    if (projectileCreate) {
        for (int j = 0; j < projectiles.size(); j++) {
            if (projectiles[j].is == 1) {
                projectiles[j].x += deltaTimeSeconds * glm::cos(projectiles[j].rad);
                projectiles[j].y += deltaTimeSeconds * glm::sin(projectiles[j].rad);
                modelMatrix = visMatrix * transform2D::Translate(projectiles[j].x, projectiles[j].y);
                RenderMesh2D(meshes["Projectile"], shaders["VertexColor"], modelMatrix);
            }
       }
    }

    if (projectileTime2 == 3) {
        for (int i = 0; i < projectiles.size(); i++) {
            projectiles[i].is = 0;
        }
    }

    projectileTime2 -= deltaTimeSeconds;
    if (projectileTime2 <= 0) {
        projectileTime2 = 3;
    }
    //coliziuni
   
    //inamic-harta
    for (int i = 0; i < enemies.size(); i++) {
            if (CheckCollision1(enemies[i].x, enemies[i].y, lengthEnemy, lengthEnemy, 0, 0 ,20 ,0.1)) {
                enemies[i].x = old[i].x;
                enemies[i].y = old[i].y;
            }

            if (CheckCollision1(enemies[i].x, enemies[i].y, lengthEnemy, lengthEnemy, 0, 0, 0.1, 20)) {
                enemies[i].x = old[i].x;
                enemies[i].y = old[i].y;
            }

            if (CheckCollision1(enemies[i].x, enemies[i].y, lengthEnemy, lengthEnemy, 19.7, 0, 0.1, 20)) {
                enemies[i].x = old[i].x;
                enemies[i].y = old[i].y;
            }

            if (CheckCollision1(enemies[i].x, enemies[i].y, lengthEnemy, lengthEnemy, 0, 19.7, 20, 0.1)) {
                enemies[i].x = old[i].x;
                enemies[i].y = old[i].y;
            }
    }

    //proiectil-harta/obstacole
    for (int i = 0; i < obs.size(); i++) {
        for (int j = 0; j < projectiles.size(); j++) {
            if (CheckCollision1(projectiles[j].x, projectiles[j].y, lengthProjectile, lengthProjectile, obs[i].x, obs[i].y, obs[i].scale_x, obs[i].scale_y)) {
                projectiles[j].is = 0;
                projectiles.erase(projectiles.begin() + j);
            }
        }
    }

    //proiectil-ianmic
    for (int i = 0; i < enemies.size(); i++) {
        for (int j = 0; j < projectiles.size(); j++) {
            if(CheckCollision1(enemies[i].x, enemies[i].y, lengthEnemy, lengthEnemy, projectiles[j].x, projectiles[j].y, lengthProjectile, lengthProjectile)) {
                projectiles[j].is = 0;
                projectiles.erase(projectiles.begin() + j);
                enemies[i].is = 0;
                enemies.erase(enemies.begin() + i);
                old[i].is = 0;
                old.erase(old.begin() + i);
                score++;
                printf("Scorul este: %d\n", score);
                if (score == 20) {
                    printf("-------------------\n");
                    printf("Congratulations.You Won\n");
                }
            }
        }
    }

    //jucator - inamic
    for (int i = 0; i < enemies.size(); i++) {
        if (CheckCollision1(cercX - lenghtCerc, cercY - lenghtCerc, 2 * lenghtCerc, 2 * lenghtCerc, enemies[i].x, enemies[i].y, lengthEnemy, lengthEnemy)) {
            enemies.erase(enemies.begin() + i);
            if (nr_lives_left == 0) {
                printf("-------------------\n");
                printf("Game Over. You Lost\n");
                exit(0);
            }
            nr_lives_left--;
        }
    }
     //Creeare scena de joc
    DrawScene(visMatrix);
}


void Tema1::FrameEnd()
{
}

void Tema1::DrawScene(glm::mat3 visMatrix)
{   

    //mainile jucatorului
    modelMatrix = visMatrix * transform2D::Translate(cercX, cercY);
    modelMatrix *= transform2D::Rotate(angularMouse + M_PI / 2);
    modelMatrix *= transform2D::Translate(radius * glm::cos(5 * M_PI / 4) - offsetPlayer, radius * glm::sin(5 * M_PI / 4) - offsetPlayer);
    RenderMesh2D(meshes["playerHand"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(cercX, cercY);
    modelMatrix *= transform2D::Rotate(angularMouse + M_PI / 2);
    modelMatrix *= transform2D::Translate(radius * glm::cos(7 * M_PI / 4) + offsetPlayer, radius * glm::sin(7 * M_PI / 4) - offsetPlayer);
    RenderMesh2D(meshes["playerHand"], shaders["VertexColor"], modelMatrix);
    //jucator
    modelMatrix = visMatrix * transform2D::Translate(cercX, cercY);
    modelMatrix *= transform2D::Rotate(angularMouse + M_PI / 2);
    RenderMesh2D(meshes["Player"], shaders["VertexColor"], modelMatrix);

    //obstacole harta
    for (Obstacle o : obs) {
        modelMatrix = visMatrix * transform2D::Translate(o.x, o.y) *
            transform2D::Scale(o.scale_x, o.scale_y);
        RenderMesh2D(meshes["rectangleObs"], shaders["VertexColor"], modelMatrix);
    }
    //harta
    modelMatrix = visMatrix * transform2D::Translate(MapX, MapY);
    modelMatrix *= transform2D::Scale(MapScaleX, MapScaleY);
    RenderMesh2D(meshes["squareMap"], shaders["VertexColor"], modelMatrix);
}



void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    int speed = 2;
    X = cercX;
    Y = cercY;
    oldLogicX = logicSpace.x;
    oldLogicY = logicSpace.y;

    if (window->KeyHold(GLFW_KEY_W)) {
        logicSpace.y += speed * deltaTime;
        cercY += speed * deltaTime;
        healthBarY += speed * deltaTime;
    }
    else if (window->KeyHold(GLFW_KEY_S)) {
        logicSpace.y -= speed * deltaTime;
        cercY -= speed * deltaTime;
        healthBarY -= speed * deltaTime;
    }
    else if (window->KeyHold(GLFW_KEY_D)) {
        logicSpace.x += speed * deltaTime;
        cercX += speed * deltaTime;
        healthBarX += speed * deltaTime;
    }
    else if (window->KeyHold(GLFW_KEY_A)) {
        logicSpace.x -= speed * deltaTime;
        cercX -= speed * deltaTime;
        healthBarX -= speed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_Z)) {
        logicSpace.width -= speed * deltaTime;
        logicSpace.height -= speed * deltaTime;
        cercX -= speed * deltaTime;
        cercY -= speed * deltaTime;
        healthBarX -= speed * deltaTime;
        healthBarY -= speed * deltaTime;
    }
    else if (window->KeyHold(GLFW_KEY_X)) {
        logicSpace.width += speed * deltaTime;
        logicSpace.height += speed * deltaTime;
        cercX += speed * deltaTime;
        cercY += speed * deltaTime;
        healthBarX += speed * deltaTime;
        healthBarY += speed * deltaTime;
    }
    //coliziuni
    //player- obstacole/harta
    for (int i = 0; i < obs.size(); i++) {
        if (CheckCollision1(cercX - lenghtCerc, cercY - lenghtCerc, 2 * lenghtCerc, 2 * lenghtCerc, obs[i].x, obs[i].y, obs[i].scale_x, obs[i].scale_y)) {
            cercX = X;
            cercY = Y;
            logicSpace.x = oldLogicX;
            logicSpace.y = oldLogicY;
        }
    }

}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    
    float radiusMouse = -atan2(mouseY - viewSpace.height / 2, mouseX - viewSpace.width / 2);
    angularMouse = radiusMouse;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    float radiusMouse1 = -atan2(mouseY - viewSpace.height / 2, mouseX - viewSpace.width / 2);
    angularMouse1 = radiusMouse1;
    projectileX = cercX + lenghtCerc * glm::cos(angularMouse1);
    projectileY = cercY + lenghtCerc * glm::sin(angularMouse1);
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (projectileTime <= 0) {
            projectiles.push_back(Projectile(projectileX, projectileY, angularMouse1, 1));
            projectileTime = 0.5f;
            projectileCreate = true;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
