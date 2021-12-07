#include "robo.h"
#include <cmath>


/*
 * @brief Desenha um retangulo no ponto (0,0) do sistema
 * @param height Altura do rentagulo
 * @param width Largura do retangulo
 * @param R Componente vermelho
 * @param G Componente verde
 * @param B Componente azul
 */
void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B); 	// aplica a cor do retangulo a partir das componentes RGB
	glBegin(GL_POLYGON);	// Começa o desenho do retangulo

	glVertex2f(-width/2, 0); 		// Ponto inferior esquerdo
	glVertex2f(width/2, 0);	 		// Ponto inferior direito
	glVertex2f(width/2, height);	// Ponto superior direito
	glVertex2f(-width/2, height);	// Ponto superior esquerdo

	glEnd();				// Encerra o desenho
}

/*
 * @brief Desenha um circulo no ponto (0,0) do sistema
 * @param radius Raio do circulo
 * @param R Componente vermelho
 * @param G Componente verde
 * @param B Componente azul
 */
void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B); 	// aplica a cor dos pontos a partir das componentes RGB
	glPointSize(4);			// Altera o tamanho dos pontos

	glPushMatrix(); 		// Coloca uma nova matriz de transformações no sistema


	for(int i = 0; i < 360; i += 20){
		glRotatef(20, 0, 0, 1);     // Gira a referencia do desenho em torno do eixo z

		glBegin(GL_POINTS);
		glVertex2f(0, radius);           // Desenha o ponto
		glEnd();
	}

	glPopMatrix();			// Retira a matriz de transformações atual do sistema

}

/*
 * @brief Desenha uma roda do robô no ponto (x,y) do sistema
 * @param x Coordenada x da roda
 * @param y Coordenada y da roda
 * @param thetaWheel Angulo da roda
 * @param R Componente vermelho
 * @param G Componente verde
 * @param B Componente azul
 */
void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B)
{
	glPushMatrix();					// Coloca uma nova matriz de transformações no sistema

	glTranslatef(x, y, 0);      	// Muda a referencia de desenho para o ponto (x,y) da roda
	glRotatef(thetaWheel, 0, 0, 1); // Gira a referencia para o angulo atual da roda

	this->DesenhaCirc(radiusWheel, R, G, B); // Desenha a roda

	glPopMatrix();					// Retira a matriz de transformações atual do sistema

}

/*
 * @brief Desenha o braço do robô no ponto (x,y) do sistema
 * @param x Coordenada x do braço
 * @param y Coordenada y do braço
 * @param theta1 Angulo da haste 1
 * @param theta2 Angulo da haste 2
 * @param theta3 Angulo da haste 3
 */
void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
	glPushMatrix();				// Coloca uma nova matriz de transformações no sistema

	// Haste 1 (Roxa)
	glTranslatef(x, y, 0);		// Muda a referencia de desenho para o ponto (x,y) do braço
	glRotatef(theta1, 0, 0, 1);	// Gira a referencia do desenho em torno do eixo z
	this->DesenhaRect(paddleHeight, paddleWidth, 1, 0, 1); // Desenha a primeira haste

	// Haste 2 (Azul)
	glTranslatef(0, paddleHeight, 0); // Sobe a referencia para o final da haste anterior
	glRotatef(theta2, 0, 0, 1); // Gira a referencia do desenho em torno do eixo z
	this->DesenhaRect(paddleHeight, paddleWidth, 0, 0, 1); // Desenha a segunda haste

	// Haste 3 (Ciano)
	glTranslatef(0, paddleHeight, 0); // Sobe a referencia para o final da haste anterior
	glRotatef(theta3, 0, 0, 1); // Gira a referencia do desenho em torno do eixo z
	this->DesenhaRect(paddleHeight, paddleWidth, 0, 1, 1); // Desenha a terceira haste

	glPopMatrix();				// Retira a matriz de transformações atual do sistema
}

/*
 * @brief Desenha o robô no ponto (x,y) do sistema
 * @param x Coordenada x do robô
 * @param y Coordenada y do robô
 * @param thetaWheel Angulo da roda
 * @param theta1 Angulo da haste 1
 * @param theta2 Angulo da haste 2
 * @param theta3 Angulo da haste 3
 */
void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
	glPushMatrix();			// Coloca uma nova matriz de transformações no sistema
	glTranslatef(x,y,0);	// Muda a referencia de desenho para o ponto (x,y) do robô

	this->DesenhaRect(baseHeight, baseWidth, 1, 0, 0);			// Desenha a base do robô
	this->DesenhaBraco(0, baseHeight, theta1, theta2, theta3);	// Desenha o braço do robô
	this->DesenhaRoda(-baseWidth/2, 0, thetaWheel, 1, 1, 1);	// Desenha a roda esquerda
	this->DesenhaRoda(baseWidth/2, 0, thetaWheel, 1, 1, 1);		// Desenha a roda direita

	glPopMatrix();			// Retira a matriz de transformações atual do sistema
}

void Robo::RodaBraco1(GLfloat inc)
{
	this->gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc)
{
	this->gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc)
{
	this->gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx)
{
	this->gX += dx;
	this->gThetaWheel -= (180*dx)/(M_PI*radiusWheel);
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){

}

Tiro* Robo::Atira()
{

}
