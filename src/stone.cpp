#include "stone.h"

Stone::Stone(float x, float y, float z, color_t color, float len, float he) {

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    val = PI/180;

    GLfloat vertex_buffer_data[] = {

        // for base square
        len, len, 0.0,
        -len, len, 0.0,
        -len, -len, 0.0,

        len, len, 0.0,
        -len, -len, 0.0,
        len, -len, 0.0,

        // triangles (point being 0,0,he)
        len, len, 0.0,
        -len, len, 0.0,
        0.0,0.0,he,

        -len, len, 0.0,
        -len, -len, 0.0,
        0.0,0.0,he,
        0.0,0.0,he,

        -len, -len, 0.0,
        len, -len, 0.0,
        0.0,0.0,he,

        len, -len, 0.0,
        len, len, 0.0,
        0.0,0.0,he,
    };

    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color, GL_FILL);
}

void Stone::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Stone::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Stone::tick() {
//    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


