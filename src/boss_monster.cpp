#include "boss_monster.h"

Boss_monster::Boss_monster(float x, float y, float z, float len, float sped_x, float sped_y) {

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    val = PI/180;
    spdx = sped_x;
    spdy = sped_y;
    lives = 3;

    GLfloat vertex_buffer_data[] = {

        // base cuboid

        -len,-len,-len + 2*len,
        -len,-len, len+ 2*len,
        -len, len, len+ 2*len,
        len, len,-len+ 2*len,
        -len,-len,-len+ 2*len,
        -len, len,-len+ 2*len,
        len,-len, len+ 2*len,
        -len,-len,-len+ 2*len,
        len,-len,-len+ 2*len,
        len, len,-len+ 2*len,
        len,-len,-len+ 2*len,
        -len,-len,-len+ 2*len,
        -len,-len,-len+ 2*len,
        -len, len, len+ 2*len,
        -len, len,-len+ 2*len,
        len,-len, len+ 2*len,
        -len,-len, len+ 2*len,
        -len,-len,-len+ 2*len,
        -len, len, len+ 2*len,
        -len,-len, len+ 2*len,
        len,-len, len+ 2*len,
        len, len, len+ 2*len,
        len,-len,-len+ 2*len,
        len, len,-len+ 2*len,
        len,-len,-len+ 2*len,
        len, len, len+ 2*len,
        len,-len, len+ 2*len,
        len, len, len+ 2*len,
        len, len,-len+ 2*len,
        -len, len,-len+ 2*len,
        len, len, len+ 2*len,
        -len, len,-len+ 2*len,
        -len, len, len+ 2*len,
        len, len, len+ 2*len,
        -len, len, len+ 2*len,
        len,-len, len+ 2*len,

    };

    GLfloat vertex_buffer_data1[] = {

        // 1st pyramid
        -len, -len, 3*len,
        -len, len, 3*len,
        0.0, 0.0, 4*len,

        -len, len, 3*len,
        len, len, 3*len,
        0.0, 0.0, 4*len,

        len, len, 3*len,
        len, -len, 3*len,
        0.0, 0.0, 4*len,

        len, -len, 3*len,
        -len, -len, 3*len,
        0.0, 0.0, 4*len,

        // 2nd pyramid
        -len, -len, len+ len,
        -len, -len, -len+ len,
        0.0, -2*len, 0.0+ len,

        -len, -len, len+ len,
        len, -len, len+ len,
        0.0, -2*len, 0.0+ len,

        len, -len, len+ len,
        len, -len, -len+ len,
        0.0, -2*len, 0.0+ len,

        len, -len, -len+ len,
        -len, -len, -len+ len,
        0.0, -2*len, 0.0+ len,

        //3rd pyramid
        -len, len, len+ len,
        -len, len, -len+ len,
        0.0, 2*len, 0.0+ len,

        -len, len, len+ len,
        len, len, len+ len,
        0.0, 2*len, 0.0+ len,

        len, len, len+ len,
        len, len, -len+ len,
        0.0, 2*len, 0.0+ len,

        len, len, -len+ len,
        -len, len, -len+ len,
        0.0, 2*len, 0.0+ len,

        // 4th pyramid
        len, -len, len+ len,
        len, -len, -len+ len,
        2*len, 0.0, 0.0+ len,

        len, -len, len+ len,
        len, len, len+ len,
        2*len, 0.0, 0.0+ len,

        len, len, len+ len,
        len, len, -len+ len,
        2*len, 0.0, 0.0+ len,

        len, len, -len+ len,
        len, -len, -len+ len,
        2*len, 0.0, 0.0+ len,

        //5th pyramid
        -len, -len, len+ len,
        -len, -len, -len+ len,
        -2*len, 0.0, 0.0+ len,

        -len, -len, len+ len,
        -len, len, len+ len,
        -2*len, 0.0, 0.0+ len,

        -len, len, len+ len,
        -len, len, -len+ len,
        -2*len, 0.0, 0.0+ len,

        -len, len, -len+ len,
        -len, -len, -len+ len,
        -2*len, 0.0, 0.0+ len,

    };

    object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BLUE, GL_FILL);
    object1 = create3DObject(GL_TRIANGLES, 20*3, vertex_buffer_data1, COLOR_BROWN, GL_FILL);

}

void Boss_monster::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Boss_monster::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss_monster::tick() {
    this->position.x += spdx;
    this->position.y += spdy;
    this->rotation += 2.0;
}
