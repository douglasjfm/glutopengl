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

#include "sos.h"
#include <math.h>

// ##### Params START #####

// Extrinsic matrix translation params (camera translation)
// Note: only set for the z axis
double tc = -1.5;

GLfloat mouse_x, mouse_y;

// Extrinsic matrix
GLfloat r[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
GLfloat t[3] = { 0, 0, -1.5 };

// Extrinsic matrix
GLfloat extrinsic[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, -1, 0,
	-0.5, 0, tc, 1
};

// Object rotation param for all axis
double ro = 0;

// Object translation param for the x axis
double to = 0;

// ##### Params END #####

// Screen params
GLfloat wWidth = 1280.0;
GLfloat wHeight = 720.0;

// Constants for object translation and rotation and camera translation
const double translateConstant = 0.01;
const double rotateConst = 1.5;
const double translateCameraConst = 0.005;

OBJETO **obj;

bool buffer[250];

void initialize() // Initialize opengl params
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void myreshape(GLsizei w, GLsizei h) // Called at startup and when you move the window
{
	glMatrixMode(GL_PROJECTION);
	double g_Width = wWidth;
	double g_Height = wHeight;
	glViewport(0, 0, g_Width, g_Height);
	glLoadIdentity();
	gluPerspective(45, g_Width / g_Height, 0.1f, 3000.0f);
}

void drawGrid() // Draws a grid...
{
	glPushMatrix();

		glTranslatef(-5, -.1, -5);

		glColor3f(.3, .3, .3);

		glBegin(GL_LINES);
			for (int i = 0; i <= 10; i++)
			{
				if (i == 0) { glColor3f(.6, .3, .3); }
				else { glColor3f(.25, .25, .25); };
				glVertex3f(i, 0, 0);
				glVertex3f(i, 0, 10);
				if (i == 0) { glColor3f(.3, .3, .6); }
				else { glColor3f(.25, .25, .25); };
				glVertex3f(0, 0, i);
				glVertex3f(10, 0, i);
			};
		glEnd();

	glPopMatrix();
}

void mydisplay()
{
	//cout << "Don't remove me, I am running." << endl;

	glMatrixMode(GL_MODELVIEW);
//
	glClearColor(0, 0, 0, 0);
//
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//	// Update camera translation on z axis (altered by keyboard input)
	extrinsic[14] = tc;
//
	glMatrixMode(GL_MODELVIEW);
//
	glLoadMatrixf(extrinsic);
//
	glRotatef(ro * 0.2, 0, 1, 0); // Comment this line to stop the world from spinning (less dizzy)
//
	drawGrid();
//
//	glColor3f(0.2, 0.0, 0.2);

	// Test without glPushMatrix() and glPopMatrix() to see what happens
    lfloat *draw = obj[0]->v;
    glPushMatrix();

	 glRotatef(ro, 1, 1, 1);
	 glTranslatef(to, 0, 0);

	glBegin(GL_TRIANGLES);//start drawing triangles

    glColor3f(0.2, 0.2, 0.0);
    while (draw)
    {
        glVertex3f(draw->f,draw->px->f,draw->px->px->f);
        draw = draw->px->px->px;
    }

	 glEnd();//end drawing of triangles
	 glPopMatrix();


//	glPushMatrix();
//
//		glTranslatef(to, 0, 0);
//		glRotatef(ro, 1, 1, 1);
//		glutWireSphere(0.3, 100, 100);
//
//	glPopMatrix();
//
//	glColor3f(0.2, 0.2, 0.0);
//
//	glPushMatrix();
//
//		glTranslatef(to + 0.8, 0, 0);
//		glRotatef(ro, 1, 1, 1);
//		glutWireTeapot(0.3);
//
//	glPopMatrix();
//
//	glColor3f(0.0, 0.2, 0.2);
//
//	glPushMatrix();
//
//		glTranslatef(to - 0.6, 0, 0);
//		glRotatef(ro, 1, 1, 1);
//		glutWireCube(0.3);
//
//	glPopMatrix();

	glFlush();

	glutPostRedisplay();
}

void handleKeyboardPressed(unsigned char key, int x, int y)
{
	buffer[(int)key] = true;
}

void handleKeyboardUp(unsigned char key, int x, int y)
{
	buffer[(int)key] = false;
}

void idleFunction() // Processes keyboard inputs
{
	// #### Resume ####

	// Move object: 1, 2
	// Rotate object: r
	// Move camera: w, s
	// Exit: ESC

	// #### Object commands ####

	if(buffer['1']==true) // Translate object on x negatively
		translate(-translateConstant);
	if(buffer['2']==true) // Translate object on x positively
		translate(translateConstant);
	if(buffer['r']==true)
		rotate(rotateConst);

	// #### Camera commands ####

	if(buffer['w']==true) // Move camera frontward
		cameraTranslate(translateCameraConst);
	if(buffer['s']==true) // Move camera backward
		cameraTranslate(-translateCameraConst);

	// #### Other commands ####

	if(buffer[27] == true) // ESC
		exit(0);
}

void translate(double t)
{
	to += t; // Translate object on x axis
}

void rotate(double r)
{
	ro += r; // Rotate object in all axis
}

void cameraTranslate(double t)
{
	tc += t; // Translate camera on z axis
}
void mouseMovement(int x, int y)
{

}

void cameraTranslateZ(double tr)
{
	t[2] += (GLfloat)tr; // Translate camera on z axis
}
void cameraTranslateX(double tr)
{
	t[0] += (GLfloat)tr; // Translate camera on x axis
}
void cameraRotateX(GLfloat tr)
{
	extrinsic[0] = (double)1;
	extrinsic[5] = (double)cos(r[4]+tr);
	extrinsic[6] = (double)-sin(r[5]+tr);
	extrinsic[9] = (double)sin(r[7]+tr);
	extrinsic[10] = (double)cos(r[8]+tr);
	extrinsic[15] = (double)1;
	glMatrixMode(GL_MODELVIEW);

	glLoadMatrixf(extrinsic);

}
void cameraRotateY(GLfloat tr)
{
	extrinsic[0] = (double)cos(r[0]+tr);
	extrinsic[2] = (double)sin(r[2]+tr);
	extrinsic[5] = (double)1;
	extrinsic[8] = (double)-sin(r[6]+tr);
	extrinsic[10] = (double)cos(r[8]+tr);
	extrinsic[15] = (double)1;
	glMatrixMode(GL_MODELVIEW);

	glLoadMatrixf(extrinsic);
}
void handleMotion(int x, int y)
{
	if ((float)x > mouse_x)
		cameraRotateY((GLfloat)(-mouse_x)*0.01);
	else
		cameraRotateY((GLfloat)mouse_x*0.01);
	if ((float)y > mouse_y)
		cameraRotateX((GLfloat)mouse_y*0.01);
	else
		cameraRotateX((GLfloat)(-mouse_y)*0.01);
	mouse_x = (float)x;
	mouse_y = (float)y;
}

void handleMouse(int btn, int state, int x, int y)
{
}


int main(int argc, char **argv)
{
    int c = 1;
    if (!argc)exit (2);
    obj = (OBJETO**) calloc(argc-1,sizeof(OBJETO*));

    for (c=1;c<argc;c++)
    {
        obj[c-1] = loader(argv[c]);
    }

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0,0);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutMouseFunc(handleMouse);
	glutPassiveMotionFunc(handleMotion);
	glutKeyboardUpFunc(handleKeyboardUp);
	glutKeyboardFunc(handleKeyboardPressed);
	glutIdleFunc(idleFunction);
	initialize();
	glutMainLoop();
	return 0;
}
