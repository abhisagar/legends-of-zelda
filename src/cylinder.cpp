#include "cylinder.h"
#include "boat.h"

Cylinder::Cylinder(float x, float y, float z, float he, color_t color, float radius) {

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->height = he;
    val = PI/180;

    GLfloat vertex_buffer_data[10000];

    int j=0;
    float angle = 1.0f;
    for (int i=0;i<360;i++) {

        // for triangle 1
        vertex_buffer_data[j] = radius*cos(val*angle);
        vertex_buffer_data[j+1] = -he;
        vertex_buffer_data[j+2] = radius*sin(val*angle);

        j+=3;
        vertex_buffer_data[j] = radius*cos(val*(angle+1.0));
        vertex_buffer_data[j+1] = -he;
        vertex_buffer_data[j+2] = radius*sin(val*(angle+1.0));

        j+=3;
        vertex_buffer_data[j] = radius*cos(val*(angle+1.0));
        vertex_buffer_data[j+1] = he;
        vertex_buffer_data[j+2] = radius*sin(val*(angle+1.0));

        // for triangle 2
        j+=3;
        vertex_buffer_data[j] = radius*cos(val*(angle+1.0));
        vertex_buffer_data[j+1] = he;
        vertex_buffer_data[j+2] = radius*sin(val*(angle+1.0));

        j+=3;
        vertex_buffer_data[j] = radius*cos(val*angle);
        vertex_buffer_data[j+1] = -he;
        vertex_buffer_data[j+2] = radius*sin(val*angle);

        j+=3;
        vertex_buffer_data[j] = radius*cos(val*angle);
        vertex_buffer_data[j+1] = he;
        vertex_buffer_data[j+2] = radius*sin(val*angle);
        j += 3;
        angle += 1.0f;

    }

    GLfloat vertex_buffer_data1[10000], m= radius, n=-he, o=0.0;

    angle = 1.0f;
    j=0;
    for (int i=0;i<360;i++) {

        vertex_buffer_data1[j] = 0.0;
        vertex_buffer_data1[j+1] = n;
        vertex_buffer_data1[j+2] = 0.0;

        j+=3;
        vertex_buffer_data1[j] = m;
        vertex_buffer_data1[j+1] = n;
        vertex_buffer_data1[j+2] = o;

        m = radius*cos(angle*val);
        o = radius*sin(angle*val);
        j+=3;
        vertex_buffer_data1[j] = m;
        vertex_buffer_data1[j+1]= n;
        vertex_buffer_data1[j+2] = o;

        angle+=1.0;
        j+=3;


    }

    GLfloat vertex_buffer_data2[10000];
    n = he, m=radius, o=0.0;

    angle = 1.0f;
    j=0;
    for (int i=0;i<360;i++) {

        vertex_buffer_data2[j] = 0.0;
        vertex_buffer_data2[j+1] = n;
        vertex_buffer_data2[j+2] = 0.0;

        j+=3;
        vertex_buffer_data2[j] = m;
        vertex_buffer_data2[j+1] = n;
        vertex_buffer_data2[j+2] = o;

        m = radius*cos(angle*val);
        o = radius*sin(angle*val);
        j+=3;
        vertex_buffer_data2[j] = m;
        vertex_buffer_data2[j+1]= n;
        vertex_buffer_data2[j+2] = o;

        angle+=1.0;
        j+=3;

    }

    this->object = create3DObject(GL_TRIANGLES, 360*2*3, vertex_buffer_data, color , GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data1, color , GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data2, color , GL_FILL);

}

void Cylinder::draw(glm::mat4 VP) {
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
    draw3DObject(this->object2);
}

void Cylinder::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cylinder::tick() {
    this->rotation -= 2;
}
