#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z, color_t color, float len, float wid) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.002;

    GLfloat vertex_buffer_data[] = {

        -len, -wid, 0.0f,
        -len, wid, 0.0,
        len, wid, 0.0,

        len, wid, 0.0,
        len, -wid, 0.0,
        -len, -wid, 0.0

    };

    GLfloat vertex_buffer_data1[100000];
    int m=0;

    for (int i=-200;i<200;i+=8) {

        for (int j=-200;j<200;j+=8) {

            vertex_buffer_data1[m] = i;
            vertex_buffer_data1[m+1] = j;
            vertex_buffer_data1[m+2] = 0.001;

            m+=3;
            vertex_buffer_data1[m] = i+8.0;
            vertex_buffer_data1[m+1] = j;
            vertex_buffer_data1[m+2] = 0.001;

            m+=3;
            vertex_buffer_data1[m] = i;
            vertex_buffer_data1[m+1] = j+8.0;
            vertex_buffer_data1[m+2] = 0.001;

            m+=3;

        }

    }

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 25*100*3, vertex_buffer_data1, COLOR_DARKBLUE, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
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

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Water::tick() {

    this->position.z += speed;
    if (this->position.z >= 0.1 || this->position.z <= 0.001)
        speed = -speed;

}
