#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H
#define PI 3.14159265


class Enemy
{
public:
    Enemy() {}
    Enemy (float x, float y, float z, float len, float speed_x, float speed_y);
    glm::vec3 position;
    float rotation, val, spdx, spdy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object1;
};

#endif // ENEMY_H
