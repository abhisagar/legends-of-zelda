#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed_z = 1;
    flag=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {


        -0.1f,-0.1f,-0.1f, // triangle 1 : begin
        -0.1f,-0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f, // triangle 1 : end
        0.1f, 0.1f,-0.1f, // triangle 2 : begin
        -0.1f,-0.1f,-0.1f,
        -0.1f, 0.1f,-0.1f, // triangle 2 : end
        0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,
        -0.1f,-0.1f,-0.1f,
        -0.1f,-0.1f,-0.1f,
        -0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f,-0.1f,
        0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f, 0.1f,
        -0.1f,-0.1f,-0.1f,
        -0.1f, 0.1f, 0.1f,
        -0.1f,-0.1f, 0.1f,
        0.1f,-0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f,-0.1f,
        -0.1f, 0.1f,-0.1f,
        0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f,-0.1f,
        -0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f,
        0.1f,-0.1f, 0.1f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.1f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
//    this->rotation += speed;
    if (this->flag == 1) {
        this->position.z += speed_z;
        speed_z -= 0.001;
        this->position.x += speed_x;
        this->position.y += speed_y;
    }
}
