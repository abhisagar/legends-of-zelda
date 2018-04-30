#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H
#define PI 3.14159265


class Cylinder
{
public:
    Cylinder () {}
    Cylinder(float x, float y, float z, float he, color_t color, float radius);
    glm::vec3 position;
    float rotation, val, speed_z, height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // CYLINDER_H
