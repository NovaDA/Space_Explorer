#ifndef BARRIER_H
#define BARRIER_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"

class Barrier : public AndromedaSystem
{
	GLfloat rotation = 0.0;
	GLfloat radius = 0.0;
public:
	Barrier(GLfloat x, GLfloat y, GLfloat z, GLfloat radius):AndromedaSystem(x, y, z)
	{
		this->radius = radius;
	}
	void setPosition(GLfloat x, GLfloat y, GLfloat z)
	{
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
	}

	void setPosition(vectorXYZ newPosition)
	{
		this->position = newPosition;
	}

	void Render()
	{
		glTranslatef(position.x, position.y, position.z);
		glPushMatrix();
		glRotatef(0.0, 1.0, 0.0, 0.0);
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glRotatef(rotation, 0.0, 0.0, 1.0);
		glutWireSphere(radius, 20.0, 20.0);
		glPopMatrix();
		
	};

	void Update()
	{
		rotation += 20.0;
	}



};

#endif

