#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water
{
public:
    Water() {}
    Water(float x, float y, float z, color_t color, float len, float wid);
    glm::vec3 position;
    float rotation, speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
    VAO *object1;
};

#endif // WATER_H
