/****************************************************

########## Project 1 Basis ##########

Graphics Processing - PG (if680)
Center of Informatics - CIn
Federal University of Pernambuco - UFPE

@authors
{
	Caio Lins (csnrl at cin.ufpe.br),
	Geovane Pereira (geeosp at cin.ufpe.br),
	Vinicius Emanuel (vems at cin.ufpe.br)
}

Reference for OpenGL commands: https://www.opengl.org/sdk/docs/man2/xhtml/

*****************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_

#include "objloader.h"

#define FPS			30
#define ESC			27
#define IDLE		-2
#define MODIFIED	-1

void myreshape(GLsizei w, GLsizei h);

void mydisplay();

void handleMotion(int x, int y);

void handleMouse(int btn, int state, int x, int y);

void hadleKeyboard(unsigned char key, int x, int y);

void hadleSpecialKeyboard(int key, int x, int y);

void translate(double t);

void rotate(double r);

void cameraTranslate(double t);

void initi();

#endif //_MAIN_H_
