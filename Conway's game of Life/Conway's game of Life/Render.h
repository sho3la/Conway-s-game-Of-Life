#pragma once
#include "SerialGame.h"
#include <glut.h>

class Render
{

	SerialGame *game;

public:
	Render(int width , int height);
	~Render();

	void Init();
	void Update();
	void Reshape(int w, int h);
	void Draw();
	void Exit();

	int window_width;
	int window_height;


	GLint fps;
	GLfloat left;
	GLfloat right;
	GLfloat bottom;
	GLfloat top;

	int Counter;

};