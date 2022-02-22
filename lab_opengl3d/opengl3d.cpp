#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <functional>
#include <ostream>
#include <iostream>

#include <Utils.hpp>
#include <glm/glm.hpp>

#define windowSize 250

int keyStatus[NUM_TECLAS_ASCII + 2 + 2 + 2];
float x_luz, y_luz;
glm::vec3 camera_position = {0.0f, 2.0f, 5.0f};
glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};

void init( ) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
//    glShadeModel (GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glViewport (0, 0, (GLsizei) windowSize, 
            (GLsizei) windowSize);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (50, 
            (GLfloat)windowSize/(GLfloat)windowSize, 
                    1, 15);
//    glOrtho (-3, 3, -3*(GLfloat)windowSize/(GLfloat)windowSize,
//       3*(GLfloat)windowSize/(GLfloat)windowSize, 1.0, 15.0);   
}
void DrawAxes(double size)
{
    GLfloat mat_ambient_r[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient_g[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat mat_ambient_b[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, 
            no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);

    //x axis red
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, 
                mat_ambient_r);
        glColor3fv(mat_ambient_r);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();

    //y axis green
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, 
                mat_ambient_g);
        glColor3fv(mat_ambient_g);
        glRotatef(90,0,0,1);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();

    //z axis blue
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);
        glColor3fv(mat_ambient_b);
        glRotatef(-90,0,1,0);
        glScalef(size, size*0.1, size*0.1);
        glTranslatef(0.5, 0, 0); // put in one end
        glutSolidCube(1.0);
    glPopMatrix();   
}

void DrawObj(double size)
{
   GLfloat materialEmission[] = { 0.00, 0.00, 0.00, 1.0};
   GLfloat materialColor[] = { 1.0, 0.0, 1.0, 0.5};
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = { 128 };
   glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
   glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glColor3f(1,0,0);
   glRotatef(45, 0.5,0.5,0);
   //glutSolidCube(size);
   glutSolidSphere(size, 20, 10);
}

void display(void)
{
    glClear (   GL_COLOR_BUFFER_BIT | 
                GL_DEPTH_BUFFER_BIT);
   
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(  camera_position.x, camera_position.y, camera_position.z, 
                camera_target.x, camera_target.y, camera_target.z,
                0,1,0);
   
    GLfloat light_position[] = { 0.0f, 2.0f, 10.0, 1.0 };
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(x_luz, y_luz, 0.0f);
    // std::cout << "Luz em (" << x_luz << ", " << y_luz << ")" << std::endl;
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();

    DrawAxes(1.5);

    DrawObj(1.0);
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void idle(void){
    x_luz = keyStatus[MOUSE_X_COORD];
    y_luz = keyStatus[MOUSE_Y_COORD];

    if(keyStatus[(int) 'w']) {
        camera_position.y += 0.01f;
        camera_target.y += 0.01f;
    }
    else if(keyStatus[(int) 's']) {
        camera_position.y -= 0.01f;
        camera_target.y -= 0.01f;
    }

    if(keyStatus[(int) 'a']) {
        camera_position.x -= 0.01f;
        camera_target.x -= 0.01f;
    }
    else if(keyStatus[(int) 'd']) {
        camera_position.x += 0.01f;
        camera_target.x += 0.01f;
    }

    if(keyStatus[(int) 'q']){
        camera_position.z += 0.01f;
        camera_target.z += 0.01f;
    } else if (keyStatus[(int) 'e']){
        camera_position.z -= 0.01f;
        camera_target.z -= 0.01f;
    }
}

static void keyPress(unsigned char key, int, int){
    if( key == 27 )
        exit(0);

    keyStatus[(int) tolower(key)] = 1;
}

static void keyup(unsigned char key, int x, int y){
    keyStatus[(int)(tolower(key))] = 0;
}

static void mouseEvent(int button, int state, int, int){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN) keyStatus[MOUSE_LEFT_CLICK] = 1; // On press
        else keyStatus[MOUSE_LEFT_CLICK] = 0;                   // On release
    } else if(button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN) keyStatus[MOUSE_RIGHT_CLICK] = 1;  // On press
        else keyStatus[MOUSE_RIGHT_CLICK] = 0;                  // On release
    }

    if(button == BUTTON_SCROLL_UP){
        if(state == GLUT_DOWN) {
            camera_position.z -= 0.2f;
            camera_target.z -= 0.2f;
        }
    } else if(button == BUTTON_SCROLL_DOWN){
        if(state == GLUT_DOWN) {
            camera_position.z += 0.2f;
            camera_target.z += 0.2f;
        }
    }
    #if defined TEST
        // std::cout << button << ", " << state << std::endl;
        // if(keyStatus[MOUSE_SCROLL_UP]) std::cout << "scroll pra cima!!" << std::endl;
    #endif
}

static void mouseMove(int x, int y){
    #if defined TEST
        // std::cout << "Mouse em (" << instance->keyStatus[MOUSE_X_COORD] << ", " << instance->keyStatus[MOUSE_Y_COORD] << ")" << std::endl;
    #endif

    keyStatus[MOUSE_X_COORD] = x - windowSize/2;
    keyStatus[MOUSE_Y_COORD] = - y + windowSize/2;
    #if defined TEST
        // std::cout << "Mouse em (" << keyStatus[MOUSE_X_COORD] << ", " << keyStatus[MOUSE_Y_COORD] << ")" << std::endl;
    #endif
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | 
                        GLUT_RGB | 
                        GLUT_DEPTH);
    glutInitWindowSize (windowSize, windowSize); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyup);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseEvent);
    glutMainLoop();
    return 0;
}
