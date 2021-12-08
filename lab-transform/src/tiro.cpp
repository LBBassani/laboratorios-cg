#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B); 	// aplica a cor dos pontos a partir das componentes RGB

	glBegin(GL_POLYGON);

	for(int i = 0; i < 360; i += 20){
		glVertex2f(radius*cos(i*M_PI/180), radius*sin(i*M_PI/180));           // Desenha o ponto
	}

	glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
	glPushMatrix(); 		// Coloca uma nova matriz de transformações no sistema

	glTranslatef(x, y, 0);  // Muda a referencia de desenho para o ponto (x,y) do tiro
	this->DesenhaCirc(radiusTiro, 1, 1, 1);

	glPopMatrix();			// Retira a matriz de transformações atual do sistema
}

void Tiro::Move()
{
	this->gX += this->gVel * sin(-gDirectionAng*M_PI/180);

	this->gY += this->gVel * cos(-gDirectionAng*M_PI/180);
}

bool Tiro::Valido()
{
	return sqrt(pow(this->gX, 2) + pow(this->gY, 2)) < DISTANCIA_MAX;
}
