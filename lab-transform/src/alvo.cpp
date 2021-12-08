#include "alvo.h"
#include <math.h>

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B); 	// aplica a cor dos pontos a partir das componentes RGB

	glBegin(GL_POLYGON);

	for(int i = 0; i < 360; i += 20){
		glVertex2f(radius*cos(i*M_PI/180), radius*sin(i*M_PI/180));           // Desenha o ponto
	}

	glEnd();
}

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y)
{
	glPushMatrix(); 		// Coloca uma nova matriz de transformações no sistema

	glTranslatef(x, y, 0);  // Muda a referencia de desenho para o ponto (x,y) do alvo
	GLfloat R = 0, G = 0, B = 0;

	switch(this->gColor){
	case 0:
		R = 1;
		break;
	case 1:
		G = 1;
		break;
	case 2:
		B = 1;
		break;
	}

	this->DesenhaCirc(radiusAlvo, R, G, B);

	glPopMatrix();			// Retira a matriz de transformações atual do sistema
}

void Alvo::Recria(GLfloat x, GLfloat y)
{

	this->gColor = this->gColor == 2 ? 0 : this->gColor + 1;
	this->gX = x;
	this->gY = y;

}

bool Alvo::Atingido(Tiro *tiro)
{
	GLfloat posx, posy;
	tiro->GetPos(posx, posy);
	GLfloat dist = sqrt(pow(posx - this->gX, 2) + pow(posy - this->gY, 2));
	return dist < radiusAlvo;
}
