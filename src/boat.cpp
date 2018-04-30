#include "boat.h"

Boat::Boat(float x, float y, float z, float radius, float he)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    val = PI/180;
    speed_z = 0;
    jump = 0;

    // for the base
    static const GLfloat vertex_buffer_data[] = {

        0.5f, 1.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,

        -0.5f, 1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        0.5f, -1.0f, 0.0f

    };

    // above pentagon
    static const GLfloat vertex_buffer_data1[] = {

        // for left triangle
        (-0.5f - cos(val*60)), (1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),
        -0.5f, 1.0f, 0.0f,
        0.0f, (1.0f + 2*sin(60*val))*cos(60*val), 0.3*(1.0f + 2*sin(60*val))*sin(60*val),

        // for middle triangle
        -0.5f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        0.0f, (1.0f + 2*sin(60*val))*cos(60*val), 0.3*(1.0f + 2*sin(60*val))*sin(60*val),

        // for right triangle
        0.5f, 1.0f, 0.0f,
        0.5f + cos(val*60), (1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),
        0.0f, (1.0f + 2*sin(60*val))*cos(60*val), 0.3*(1.0f + 2*sin(60*val))*sin(60*val),

    };

    // below pentagon
    static const GLfloat vertex_buffer_data2[] = {

        // for left triangle
        -(0.5f + cos(val*60)), -(1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),
        -0.5f, -1.0f, 0.0f,
        0.0f, -(1.0f + 2*sin(60*val))*cos(60*val), 0.3*(1.0f + 2*sin(60*val))*sin(60*val),

        // for middle triangle
        -0.5f, -1.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        0.0f, -(1.0f + 2*sin(60*val))*cos(60*val), 0.3*(1.0f + 2*sin(60*val))*sin(60*val),

        // for right triangle
        0.5f, -1.0f, 0.0f,
        0.5f + cos(val*60), -(1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),
        0.0f, -(1.0f + 2*sin(60*val))*cos(60*val), 0.3*(1.0f + 2*sin(60*val))*sin(60*val),

    };

    // for left ractangle
    static const GLfloat vertex_buffer_data3[] = {

        // for below triangle
        -0.5f, 1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -(0.5f + cos(val*60)), (1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),

        // for above triangle
        -0.5f, -1.0f, 0.0f,
        -(0.5f + cos(val*60)), (1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),
        -(0.5f + cos(val*60)), -(1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),


    };

    // for right triangle
    static const GLfloat vertex_buffer_data4[] = {

        // for below triangle
        0.5f, 1.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        (0.5f + cos(val*60)), (1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),

        // for above triangle
        0.5f, -1.0f, 0.0f,
        (0.5f + cos(val*60)), (1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),
        (0.5f + cos(val*60)), -(1.0f + sin(60*val))*cos(60*val), 0.3*(sin(60*val))*(1.0+sin(60*val)),

    };

    GLfloat vertex_buffer_data5[10000];

    int j=0;
    float angle = 0;
    for (int i=0;i<360;i++) {

        // for triangle 1
        vertex_buffer_data5[j] = radius*cos(val*angle);
        vertex_buffer_data5[j+1] = (1.0f + 2*sin(60*val))*cos(60*val);
        vertex_buffer_data5[j+2] = 0.3*(1.0f + 2*sin(60*val))*sin(60*val) + radius*sin(val*angle);

        j+=3;
        vertex_buffer_data5[j] = radius*cos(val*(angle+1));
        vertex_buffer_data5[j+1] = (1.0f + 2*sin(60*val))*cos(60*val);
        vertex_buffer_data5[j+2] = 0.3*(1.0f + 2*sin(60*val))*sin(60*val) + radius*sin(val*(angle+1));

        j+=3;
        vertex_buffer_data5[j] = radius*cos(val*(angle+1));
        vertex_buffer_data5[j+1] = (1.0f + 2*sin(60*val))*cos(60*val)+ he;
        vertex_buffer_data5[j+2] = 0.3*(1.0f + 2*sin(60*val))*sin(60*val) + radius*sin(val*(angle+1));

        // for triangle 2
        j+=3;
        vertex_buffer_data5[j] = radius*cos(val*(angle+1));
        vertex_buffer_data5[j+1] = (1.0f + 2*sin(60*val))*cos(60*val)+ he;
        vertex_buffer_data5[j+2] = 0.3*(1.0f + 2*sin(60*val))*sin(60*val) + radius*sin(val*(angle+1));

        j+=3;
        vertex_buffer_data5[j] = radius*cos(val*angle);
        vertex_buffer_data5[j+1] = (1.0f + 2*sin(60*val))*cos(60*val);
        vertex_buffer_data5[j+2] = 0.3*(1.0f + 2*sin(60*val))*sin(60*val) + radius*sin(val*angle);

        j+=3;
        vertex_buffer_data5[j] = radius*cos(val*angle);
        vertex_buffer_data5[j+1] = (1.0f + 2*sin(60*val))*cos(60*val) + he;
        vertex_buffer_data5[j+2] = 0.3*(1.0f + 2*sin(60*val))*sin(60*val) + radius*sin(val*angle);
        j += 3;
        angle += 1.0f;

    }

    GLfloat g_vertex_buffer_data[10000], n=(1.0f + 2*sin(60*val))*cos(60*val), o = 0.0f, m=radius, z_temp = 0.3*(1.0f + 2*sin(60*val))*sin(60*val);
    angle = 1.0;
    j=0;

    for (int i=0;i<360;i++) {
        g_vertex_buffer_data[j] = 0.0f;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = z_temp;
        j+=3;
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o + z_temp;
        j+=3;
        float val = PI/180;
        m = radius*cos(angle*val);
        o = radius*sin(angle*val);
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o + z_temp;
        angle += 1;
        j+=3;
    }

    this->object6 = create3DObject(GL_TRIANGLES, 360*3, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);

    this->object5 = create3DObject(GL_TRIANGLES, 360*2*3, vertex_buffer_data5, COLOR_BLACK , GL_FILL);



    // red for base
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    // green for pentagons
    this->object1 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data1, COLOR_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    // yellow for ractangles
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, COLOR_YELLOW, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
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
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
//    if (this->position.z > 0.05 && speed_z != 0.005) {
//        speed_z -= 0.005;
//    }
//    else{
//        speed_z = 0.005;
//        jump = 0;
//    }
//    if (this->position.z < -0.05)
//        speed_z = 0.005;
    this->position.z += speed_z;

    if (this->position.z <= 0.0)
        jump = 0;
    if (jump == 1)
        speed_z -= 0.005;
    if (jump == 0 && this->position.z <= 0.0)
        speed_z = 0.005;
    if (jump == 0 && this->position.z >= 0.1)
        speed_z = -0.005;

//    this->rotation += speed;
}
