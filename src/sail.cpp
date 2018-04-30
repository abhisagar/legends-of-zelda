#include "sail.h"

Sail::Sail(float x, float y, float z, float he, float len, color_t color) {

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    val = PI/180;

    GLfloat vertex_buffer_data[] = {

        // front ractange
        len, len, 0.0,
        -len, len, 0.0,
        len, len, he,

        len, len, he,
        -len, len, he,
        -len, len, 0.0,

        // right ractangle
        len, len, 0.0,
        len, -len, 0.0,
        len, len, he,

        len, len, he,
        len, -len, 0.0,
        len, -len, he,

        // left
        -len, len, 0.0,
        -len, -len, 0.0,
        -len, len, he,

        -len, -len, 0.0,
        -len, -len, he,
        -len, len, he,

        // back
        len, -len, 0.0,
        -len, -len, 0.0,
        len, -len, he,

        len, -len, he,
        -len, -len, he,
        -len, -len, 0.0,

        // top square
        len, len, he,
        len, -len, he,
        -len, len, he,

        -len, len, he,
        -len, -len, he,
        len, -len, he,

    };

    GLfloat vertex_buffer_data1[] = {

        0.0, 0.0, he,
        0.0, 0.0, he/2,
        (he/2)*sin(60*val), 0.0, 3*he/4,

    };

    this->object = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_YELLOW, GL_FILL);
}

void Sail::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object);
}

void Sail::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sail::tick() {

}
