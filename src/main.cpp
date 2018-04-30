#include "main.h"
#include "timer.h"
#include "ball.h"
#include "boat.h"
#include "water.h"
#include "stone.h"
#include "sail.h"
#include "cylinder.h"
#include "enemy.h"
#include "boss_monster.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

//Ball ball1;
Ball fireball;
Boat boat;
Water sea;
Stone stone[100];
Sail sail;
//Cylinder cannon;
Enemy rivals[100];
Cylinder barrels[10];
Boss_monster boss;
//Cylinder temp;
//Enemy temp1;
//Stone temp;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float val = PI/180, helicopter_angle, helicopter_he = 10.0;
int cnt=0, wind_flag = 0, wind_angle = 0, cnt2=0, score=0, level=1, life=2, view_cam = 4;
int powerup = 1, cntp=0;
float cursor_x = -10000, cursor_y=-100000, x_final, y_final;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */


void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );

    glm::vec3 eye, target, up;

    // boat view
    if (view_cam == 1) {

        eye     = glm::vec3(boat.position.x, boat.position.y, 1 + boat.position.z);
        target  = glm::vec3(boat.position.x + 10*sin(boat.rotation*val) ,boat.position.y  + 10*cos(boat.rotation*val), 1 + boat.position.z);
        up      = glm::vec3(0, 0, 1);

    }

    // top view
    if (view_cam == 2) {

        eye     = glm::vec3(boat.position.x, boat.position.y, 25);
        target  = glm::vec3(boat.position.x, boat.position.y, 0);
        up      = glm::vec3(0,1,0);

    }

    // tower view
    if (view_cam == 3) {

        eye     = glm::vec3(10, 0, 10);
        target  = glm::vec3(boat.position.x, boat.position.y, 0);
        up      = glm::vec3(0, 0, 1);

    }

    // follow cam
    if (view_cam == 4) {

        eye     = glm::vec3(boat.position.x-(4*sin(boat.rotation*M_PI/180)),boat.position.y-(4*cos(boat.rotation*M_PI/180)),2);
        // Target - Where is the camera looking at.  Don't change unless you are sure!!
//    glm::vec3 target (0,0,0);
        target  = glm::vec3 (boat.position.x,boat.position.y,boat.position.z);
        // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
        up      = glm::vec3 (0, 0, 1);

    }

    // heli view
    if (view_cam == 5) {

        eye     = glm::vec3 ((boat.position.x-x_final - 4), (boat.position.y - 4-y_final), 10);
        target  = glm::vec3 (boat.position.x, boat.position.y, boat.position.z);
        up      = glm::vec3 (0, 0, 1);


    }

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
//    ball1.draw(VP);
//    temp.draw(VP);
    for (int i=0; i< 100; i++){
        stone[i].draw(VP);
    }

    for (int i=0;i<20;i++)
        rivals[i].draw(VP);

    for (int i=0;i<8;i++)
        barrels[i].draw(VP);

    sea.draw(VP);
    boat.draw(VP);
    sail.draw(VP);
//    temp.draw(VP);
    if (fireball.flag == 1)
        fireball.draw(VP);
//    temp1.draw(VP);
    if (level == 3)
        boss.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left    = glfwGetKey(window, GLFW_KEY_LEFT);
    int right   = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up      = glfwGetKey(window, GLFW_KEY_UP);
    int down    = glfwGetKey(window, GLFW_KEY_DOWN);
    int jump    = glfwGetKey(window, GLFW_KEY_SPACE);
    int fire    = glfwGetKey(window, GLFW_KEY_F);
    int boatv   = glfwGetKey(window, GLFW_KEY_1);
    int topv    = glfwGetKey(window, GLFW_KEY_2);
    int towerv  = glfwGetKey(window, GLFW_KEY_3);
    int followv = glfwGetKey(window, GLFW_KEY_4);
    int heliv   = glfwGetKey(window, GLFW_KEY_5);
    int a       = glfwGetKey(window, GLFW_KEY_A);
    int d       = glfwGetKey(window, GLFW_KEY_D);
    int w       = glfwGetKey(window, GLFW_KEY_W);
    int s       = glfwGetKey(window, GLFW_KEY_S);

    if (boatv)
        view_cam = 1;
    if (topv)
        view_cam = 2;
    if (towerv)
        view_cam = 3;
    if (followv)
        view_cam = 4;
    if (heliv && view_cam != 5) {
        view_cam = 5;
        helicopter_angle = boat.rotation;
    }

    if (a && view_cam == 5)
        helicopter_angle -= 1;
    if (d && view_cam == 5)
        helicopter_angle += 1;
    if (w && view_cam == 5)
        helicopter_he += 0.1;
    if (s && view_cam == 5)
        helicopter_he -= 0.1;

    if (left) {
        // Do something
        boat.rotation -= 1;
    }
    if (right) {
        boat.rotation += 1;
    }
    if (up) {
        boat.position.y += powerup*0.05*(cos(boat.rotation*val));
        boat.position.x += powerup*0.05*(sin(boat.rotation*val));
    }
    if (down) {
        boat.position.y -= powerup*0.05*(cos(boat.rotation*val));
        boat.position.x -= powerup*0.05*(sin(boat.rotation*val));
    }
    if (jump && boat.jump == 0) {
        boat.speed_z += 0.1;
        boat.jump = 1;
    }
    if (fire && fireball.flag == 0){
        fireball.flag = 1;
        float val = PI/180;
        fireball.position.x = boat.position.x + (1.0f + 2*sin(60*val))*cos(60*val)*sin(val*boat.rotation);
        fireball.position.y = boat.position.y + (1.0f + 2*sin(60*val))*cos(60*val)*cos(val*boat.rotation);
        fireball.position.z = boat.position.z + 0.3*(1.0f + 2*sin(60*val))*sin(60*val);
        fireball.speed_z = 0.05;
        fireball.speed_x = powerup*0.08*(sin(boat.rotation*val));
        fireball.speed_y = powerup*0.08*(cos(boat.rotation*val));
    }
}

void tick_elements() {

    char title[100010];
    cnt++;
    cnt=cnt%1000;
    cnt2++;
    if (powerup!=1)
        cntp++;
    if (cntp>500)
        powerup=1;
    if (score < 0)
        score = 0;

    if ((cnt2>3000 && level < 3) || (cnt2 > 5000 && level == 3) || life <= 0){
        sprintf(title, "Gameover");
        glfwSetWindowTitle(window, title);

        for (int i=0;i<1000000000;i++);

        quit(window);
    }

    int yo, total=3000;
    if(level==1)
        yo = 10;
    if (level == 2)
        yo = 10;
    if (level == 3) {
        yo = 25;
        total = 5000;
    }

    if (score >= yo) {

        cnt2 = 0;
        score = 0;
        level++;
        boat.position.x = 0.0;
        boat.position.y = -2.0;

        sprintf(title, "Level Change");
        glfwSetWindowTitle(window, title);

        for (int i=0;i<1000000000;i++);

    }

    if (wind_flag == 1)
        sprintf(title, "Level: %d; Score : %d; Get %d score for level up; You have %d seconds;Wind is blowing;Life = %d", level, score, yo, (total-cnt2)/100, life);
    else
        sprintf(title, "Level: %d; Score : %d; Get %d score for level up; You have %d seconds; No Wind; Life = %d", level, score, yo, (total-cnt2)/100, life);

    boat.tick();
    sea.tick();
    fireball.tick();
    if (level == 3) {
        boss.tick();
        if (abs(boss.position.x) > 60 || abs(boss.position.y) > 60) {
            boss.spdx = -boss.spdx;
            boss.spdy = -boss.spdy;
        }
    }

    for (int i=0;i<5;i++)
        barrels[i].tick();

    for(int i=0;i<20;i++) {
        rivals[i].tick();
        if (abs(rivals[i].position.x) > 100 || abs(rivals[i].position.y) > 100) {
            rivals[i].spdx = -rivals[i].spdx;
            rivals[i].spdy = -rivals[i].spdy;
        }
    }

    // detect collision with the rocks
    for(int i=0;i<100;i++) {
        float dist_x    = abs(stone[i].position.x - boat.position.x);
        float dist_y    = abs(stone[i].position.y - boat.position.y);
        float dist      = sqrt((dist_x*dist_x) + (dist_y*dist_y));
        float alpha     = atan(dist_y/dist_x);
        float theta     = boat.rotation - alpha;
        if (abs(dist*cos(theta*val)) < 1.6 && abs(dist*sin(theta*val)) < 1.1) {
//            printf("collision\n");
            stone[i].position.x = ((float(rand())/float(RAND_MAX))*(200)-100);
            stone[i].position.y = ((float(rand())/float(RAND_MAX))*(200)-100);
            if (i%19 == 0)
                life--;
            else
                score -= 1;
        }
    }

    // detect collision with the enemy
    for (int i=0;i<20;i++) {

        float dist_x    = abs(rivals[i].position.x - boat.position.x);
        float dist_y    = abs(rivals[i].position.y - boat.position.y);
        float dist      = sqrt((dist_x*dist_x) + (dist_y*dist_y));
        float theta     = boat.rotation;
        if (abs(dist*cos(theta*val)) < 1.6 && abs(dist*sin(theta*val)) < 1.1) {
//            printf("collision\n");
            rivals[i].position.x = ((float(rand())/float(RAND_MAX))*(200)-100);
            rivals[i].position.y = ((float(rand())/float(RAND_MAX))*(200)-100);
            life--;
        }

    }

    // detect collision of fireball with rocks
    for(int i=0;i<100;i++) {
        float dist_x    = abs(stone[i].position.x - fireball.position.x);
        float dist_y    = abs(stone[i].position.y - fireball.position.y);
        float dist_z    = abs(stone[i].position.z - fireball.position.z);
        float dist      = sqrt((dist_x*dist_x) + (dist_y*dist_y));
        if (dist < 0.65 && dist_z < 0.4) {
//            printf("collision\n");
            stone[i].position.x = ((float(rand())/float(RAND_MAX))*(200)-100);
            stone[i].position.y = ((float(rand())/float(RAND_MAX))*(200)-100);
            if (i%19 == 0)
                life++;
            else
                score += 2;
        }
    }

    // detect collision of enemy with fireball
    for (int i=0;i<20;i++) {

        float dist_x = abs(rivals[i].position.x - fireball.position.x);
        float dist_y = abs(rivals[i].position.y - fireball.position.y);
        float dist_z = abs(fireball.position.z);
        float dist      = sqrt((dist_x*dist_x) + (dist_y*dist_y));
        if (dist < 0.8 && dist_z < 0.6) {
            rivals[i].position.x = ((float(rand())/float(RAND_MAX))*(200)-100);
            rivals[i].position.y = ((float(rand())/float(RAND_MAX))*(200)-100);
            score += 5;
        }

    }

    sail.position = boat.position;


    if (fireball.position.z < 0.0)
        fireball.flag = 0;

    if (cnt==500 && level !=1) {

        wind_angle = rand()%360;

        wind_flag = 1;

    }
    if(cnt == 0)
        wind_flag = 0;

    if (wind_flag == 1) {

        sail.rotation = (float)((wind_angle - 90)%360);
        boat.position.y += 0.03*(cos(wind_angle*val));
        boat.position.x += 0.03*(sin(wind_angle*val));

    }

    // detecting collision of barrels with the boat
    for (int i=0;i<8;i++) {

        float dist_x    = abs(barrels[i].position.x - boat.position.x);
        float dist_y    = abs(barrels[i].position.y - boat.position.y);
        float dist      = sqrt((dist_x*dist_x) + (dist_y*dist_y));
        float theta     = boat.rotation;
        if (abs(dist*cos(theta*val)) < 2.0 && abs(dist*sin(theta*val)) < 1.5) {
//            printf("collision\n");
            barrels[i].position.x = ((float(rand())/float(RAND_MAX))*(150)-75);
            barrels[i].position.y = ((float(rand())/float(RAND_MAX))*(150)-75);
            powerup *= 2;
            cntp = 0;
        }

    }

    // detect collision of fireball with boss
    if (level == 3) {

        float dist_x    = abs(boss.position.x - fireball.position.x);
        float dist_y    = abs(boss.position.y - fireball.position.y);
        float dist_z    = abs(fireball.position.z);
        float dist      = sqrt((dist_x*dist_x) + (dist_y*dist_y));
        if (dist < 0.5 && dist_z < 1.4){
            boss.lives--;
            fireball.position.x = 5000;
            fireball.position.y = 5000;
        }
        if (boss.lives == 0 || score >= 25) {
            sprintf(title, "You Won");
            glfwSetWindowTitle(window, title);

            for (int i=0;i<1000000000;i++);
            quit(window);
        }

        // collision of boat with boss
        float dist_x1    = abs(boss.position.x - boat.position.x);
        float dist_y1    = abs(boss.position.y - boat.position.y);
        float dist1      = sqrt((dist_x1*dist_x1) + (dist_y1*dist_y1));
        float theta1     = boat.rotation;
        if (abs(dist1*cos(theta1*val)) < 1.6 && abs(dist1*sin(theta1*val)) < 1.1) {
//            printf("collision\n");
            boss.set_position(1.0, 2.0, 0.0);
            boat.set_position(0.0, -2.0, 0.0);
            sail.position = boat.position;
            life--;
        }

    }


    glfwSetWindowTitle(window, title);

}

void mouse_drag (GLFWwindow* window, double x_position, double y_position) {
    double x_new,y_new;
    x_new = x_position;
    y_new = y_position;
    if (cursor_x != -10000 && cursor_y != -10000) {
        x_final += x_new - cursor_x;
        y_final += y_new - cursor_y;
    }
    cursor_x = x_new;
    cursor_y = y_new;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    boat        = Boat(0.0, -2.0, 0.0, 0.12, 0.5);
    sea         = Water(0.0,-2.0,-0.001, COLOR_SKYBLUE, 200.0, 200.0);

    sail        = Sail(0.0, -2.0, 0.0, 2.0, 0.05, COLOR_BROWN);
//    cannon      = Cylinder(boat.position.x, boat.position.y+(1.0f + 2*sin(60*val))*cos(60*val), boat.position.z + 0.3*(1.0f + 2*sin(60*val))*sin(60*val), 0.5, COLOR_BLACK, 0.12, boat.position.x, boat.position.y);
    fireball    = Ball(0.0, 0.0, 0.0, COLOR_RED);

    float bspdx = ((float(rand())/float(RAND_MAX))*(0.02)+0.01);
    float bspdy = ((float(rand())/float(RAND_MAX))*(0.02)+0.01);
    boss        = Boss_monster(1.0, 2.0, 0.0, 0.4, bspdx, bspdy);
//    temp        = Cylinder(1.0, 2.0, 0.0, 1.0, COLOR_BLACK, 0.5);

    for (int i=0;i<8;i++) {

        float pos_x = ((float(rand())/float(RAND_MAX))*(150)-75);
        float pos_y = ((float(rand())/float(RAND_MAX))*(150)-75);

        if (pos_x < 1.0 && pos_x > -1.0 && pos_y < 1.5 && pos_y > -1.5) {
            i--;
            continue;
        }
        barrels[i] = Cylinder(pos_x, pos_y, 0.0, 1.0, COLOR_BLACK, 0.5);

    }

    // creating the rivals
    for (int i=0;i<20;i++) {

        float pos_x = ((float(rand())/float(RAND_MAX))*(150)-75);
        float pos_y = ((float(rand())/float(RAND_MAX))*(150)-75);
        if (pos_x < 1.0 && pos_x > -1.0 && pos_y < 1.5 && pos_y > -1.5) {
            i--;
            continue;
        }
        float spdx = ((float(rand())/float(RAND_MAX))*(0.02)+0.01);
        float spdy = ((float(rand())/float(RAND_MAX))*(0.02)+0.01);
        rivals[i] = Enemy(pos_x, pos_y, 0.0, 0.4, spdx, spdy);
    }

    // creating the rocks
    for (int i=0; i<100;i++) {
        float pos_x = ((float(rand())/float(RAND_MAX))*(150)-75);
        float pos_y = ((float(rand())/float(RAND_MAX))*(150)-75);
        if (pos_x < 1.0 && pos_x > -1.0 && pos_y < 1.5 && pos_y > -1.5) {
            i--;
            continue;
        }
        if (i%19 == 0)
            stone[i] = Stone(pos_x, pos_y, 0.0, COLOR_YELLOW, 0.5, 0.5);
        else
            stone[i] = Stone(pos_x, pos_y, 0.0, COLOR_GREY, 0.5, 0.5);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 700;
    int height = 700;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);

            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
                glfwSetCursorPosCallback(window, mouse_drag);

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
//    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(1.0f,1.0f,1.0f,300.0f);

}
