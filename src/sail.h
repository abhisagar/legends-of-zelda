#include "main.h"

#ifndef SAIL_H
#define SAIL_H
#define PI 3.14159265


class Sail
{
public:
    Sail() {}
    Sail (float x, float y, float z, float he, float len, color_t color);
    glm::vec3 position;
    float rotation, val;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object1;
};

#endif // SAIL_H
