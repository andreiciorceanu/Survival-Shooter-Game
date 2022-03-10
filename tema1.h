#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/Obstacle.h"
#include "lab_m1/tema1/Enemy.h"
#include "lab_m1/tema1/Projectile.h"
#include <vector>

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
         struct ViewportSpace
         {
             ViewportSpace() : x(0), y(0), width(1), height(1) {}
             ViewportSpace(int x, int y, int width, int height)
                 : x(x), y(y), width(width), height(height) {}
             int x;
             int y;
             int width;
             int height;
         };

         struct LogicSpace
         {
             LogicSpace() : x(0), y(0), width(1), height(1) {}
             LogicSpace(float x, float y, float width, float height)
                 : x(x), y(y), width(width), height(height) {}
             float x;
             float y;
             float width;
             float height;
         };

        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

     protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        float radius;
        float scalePlayerX, scalePlayerY;
        float scaleHandX, scaleHandY;
        float MapX, MapY;
        float centerPlayerX, centerPlayerY;
        float width;
        float angularMouse;
        float lengthEnemyHand;
        float lengthEnemy, offset;
        std::vector<Obstacle> obs;
        std::vector<Enemy> enemies;
        std::vector<Projectile> projectiles;
        float time;
        float randX, randY;
        float speedEnemy;
        float speedProjectile;
        float cercX, cercY;
        float lenghtCerc;
        float offsetPlayer;
        float enemySpeed;
        float lengthProjectile;
        float projectileX, projectileY;
        float angularMouse1;
        bool projectileCreate;
        float lengthHealtBar;
        float nr_lives_left;
        float healthBarX, healthBarY;
        float projectileTime;
        float X, Y;
        float oldLogicX, oldLogicY;
        float MapScaleX, MapScaleY;
        std::vector<Enemy> old;
        float projectileTime2;
        int score;
    };
}   // namespace m1
