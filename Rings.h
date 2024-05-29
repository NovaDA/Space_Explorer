#ifndef RINGS_H
#define RINGS_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"

class Rings : public AndromedaSystem
{
	GLfloat rotation = 0.0;
	GLfloat innerRadius = 0.0;
	GLfloat outerRadius = 0.0;
	GLint typeRotation = 0.0;
public:
	Rings(GLfloat x, GLfloat y, GLfloat z, GLfloat innerRadius, GLfloat outerRadius, GLint typeRotation):AndromedaSystem(x, y, z)
	{
		this->innerRadius = innerRadius;
		this->outerRadius = outerRadius;
		this->typeRotation = typeRotation;
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
		if(typeRotation == 1)
		{
			glRotatef(rotation, 1.0, 0.0, 0.0);
		}
		else if (typeRotation == 2)
		{
			glRotatef(rotation, 0.0, 1.0, 0.0);
		}
		else
		{
			glRotatef(rotation, 0.0, 0.0, 1.0);
		}
		
		glutWireTorus(innerRadius, outerRadius, 10.0, 15.0);
		glPopMatrix();
		
	};

	void Update()
	{
		rotation += 1.0;
	}


};

#endif
