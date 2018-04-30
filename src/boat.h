#include "main.h"

#ifndef BOAT_H
#define BOAT_H
#define PI 3.14159265


class Boat
{
public:
    Boat () {}
    Boat(float x, float y, float z, float radius, float he);
    glm::vec3 position;
    float rotation, val, speed_z, jump;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
};

#endif // BOAT_H
