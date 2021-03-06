#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <functional>
#include <ostream>
#include <iostream>

#include <Utils.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define windowSize 250

int keyStatus[NUM_TECLAS_ASCII + 2 + 2 + 2];
glm::vec3 camera_position = {0.0f, 2.0f, 5.0f};
glm::vec3 camera_target = {0.0f, 0.0f, 0.0f};
glm::vec3 up_vector = {0.0f, 1.0f, 0.0f};

glm::vec3 eulerRotation = {0.0f, 0.0f, 0.0f};
glm::mat4 rotationMatrix = glm::mat4(0.0f);

// Calcula a matriz de rotação da cena
void calculateRotationMatrix(){
    
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
                        glm::radians(eulerRotation.x),
                        glm::vec3(1.0f, 0.0f, 0.0f));
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
                        glm::radians(eulerRotation.y),
                        glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
                        glm::radians(eulerRotation.z),
                        glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    rotationMatrix = transformY * transformX * transformZ;
}

void init( ) 
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    // glShadeModel (GL_SMOOTH);
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
    // glOrtho (-3, 3, -3*(GLfloat)windowSize/(GLfloat)windowSize, 3*(GLfloat)windowSize/(GLfloat)windowSize, 1.0, 15.0);   
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
    #if defined CUBE
        glutSolidCube(size);
    #elif defined SPHERE
        glutSolidSphere(size, 20, 10);
    #endif
}

void display(void)
{
    glClear (   GL_COLOR_BUFFER_BIT | 
                GL_DEPTH_BUFFER_BIT);
   
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(  camera_position.x, camera_position.y, camera_position.z, 
                camera_target.x, camera_target.y, camera_target.z,
                up_vector.x, up_vector.y, up_vector.z);
   
    GLfloat light_position[] = { 0.0f, 2.0f, 10.0, 1.0 };
    glPushMatrix();
        glTranslatef(keyStatus[MOUSE_X_COORD], keyStatus[MOUSE_Y_COORD], 0.0f); // Posiciona a luz de acordo com a posição do mouse
        glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();

    calculateRotationMatrix();
    glMultMatrixf(&rotationMatrix[0][0]); // Aplica a rotação da cena

    DrawAxes(1.5);  // Desenha os eixos

    DrawObj(1.0);   // Desenho os objetos
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void idle(void){

    // Move a câmera pra cima ou para baixo
    if(keyStatus[(int) 'w']) {
        camera_position.y += 0.01f;
        camera_target.y += 0.01f;
    }
    else if(keyStatus[(int) 's']) {
        camera_position.y -= 0.01f;
        camera_target.y -= 0.01f;
    }

    // Move a câmera pros lados
    if(keyStatus[(int) 'a']) {
        camera_position.x -= 0.01f;
        camera_target.x -= 0.01f;
    }
    else if(keyStatus[(int) 'd']) {
        camera_position.x += 0.01f;
        camera_target.x += 0.01f;
    }

    // Move a câmera para frente ou para trás
    if(keyStatus[(int) 'q']){
        camera_position.z += 0.01f;
        camera_target.z += 0.01f;
    } else if (keyStatus[(int) 'e']){
        camera_position.z -= 0.01f;
        camera_target.z -= 0.01f;
    }

    // Rotaciona a câmera em y
    if(keyStatus[(int) 'i']){
        eulerRotation.x += 0.2f;
    } else if (keyStatus[(int) 'k']){
        eulerRotation.x -= 0.2f;
    }

    // Rotaciona a câmera em x
    if(keyStatus[(int) 'j']){
        eulerRotation.y += 0.2f;
    } else if(keyStatus[(int) 'l']){
        eulerRotation.y -= 0.2f;
    }

    // Rotaciona a câmera em z
    if(keyStatus[(int) 'u']){
        eulerRotation.z += 0.2f;
    } else if (keyStatus[(int) 'o']){
        eulerRotation.z -= 0.2f;
    }
}

static void keyPress(unsigned char key, int, int){
    if( key == 27 )
        exit(0);

    keyStatus[(int) tolower(key)] = 1;
}

static void keyup(unsigned char key, int, int){
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
    #endif
}

static void mouseMove(int x, int y){
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
