#include "Render.h"


Render::Render(int width , int height)
{
	window_height = height;
	window_width = width;

	left = 0.0;
	right = 1.0;
	bottom = 1.0;
	top = 0.0;

	fps = 1;
	Counter = 0;
}


void Render::Init()
{
	game = new SerialGame("Data/input.txt");
	game->RandomInit();  //for test random..
	//game->Init();  //for initialization from file
}

void Render::Reshape(int w, int h)
{
	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void Render::Draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLfloat xSize = (right - left) / game->width;
	GLfloat ySize = (bottom - top) / game->height;

	glBegin(GL_QUADS);

	for (GLint x = 0; x < game->width; ++x) 
	{
		for (GLint y = 0; y < game->height; ++y) 
		{
			game->organismAt(x, y)?glColor3f(0,0,0):glColor3f(1,1,1);

			glVertex2f(x*xSize+left,      y*ySize+top);
			glVertex2f((x+1)*xSize+left,  y*ySize+top);
			glVertex2f((x+1)*xSize+left, (y+1)*ySize+top);
			glVertex2f(x*xSize+left,     (y+1)*ySize+top);
		}
	}
	glEnd();

	glFlush();
	glutSwapBuffers();

}


void Render::Update()
{
	if( Counter <= game->Num_of_generations)
	{
		game->iterate();
		++Counter;
	}
}

void Render::Exit()
{
	game->SaveFile();
}