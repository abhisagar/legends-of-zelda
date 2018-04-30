#include "main.h"

#ifndef BOSS_MONSTER_H
#define BOSS_MONSTER_H
#define PI 3.14159265


class Boss_monster
{
public:
    Boss_monster() {}
    Boss_monster (float x, float y, float z, float len, float sped_x, float sped_y);
    glm::vec3 position;
    float rotation, val, spdx, spdy;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    int lives;
    void tick();
private:
    VAO *object;
    VAO *object1;
};

#endif // BOSS_MONSTER_H
