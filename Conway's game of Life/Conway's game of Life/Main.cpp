#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include "Render.h"

Render *render = new Render(500, 500);

void reshape(int x,int y)
{
	render->Reshape(x,y);
}

void Update(int val)
{
	render->Update();

	glutPostRedisplay();
}


void draw()
{
	render->Draw();

	glutTimerFunc(1000 / render->fps,Update, 0);
}


void processNormalKeys(unsigned char key, int x, int y) 
{

	if (key == 27)
	{
		//save before terminate
		render->Exit();
		exit(0);
	}
}



int main(int argc, char **argv) 
{


	glutInit(&argc, argv);


	glutInitWindowSize(render->window_width, render->window_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game of Life");
	glClearColor(0.5, 0.5, 0.5, 1);



	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutKeyboardFunc(processNormalKeys);

	render->Init();

	render->Update();
	glutMainLoop();

	return 0;
}