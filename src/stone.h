#include "main.h"

#ifndef STONE_H
#define STONE_H
#define PI 3.14159265

class Stone
{
public:
    Stone() {}
    Stone (float x, float y, float z, color_t color, float len, float he);
    glm::vec3 position;
    float rotation, val;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
};

#endif // STONE_H
