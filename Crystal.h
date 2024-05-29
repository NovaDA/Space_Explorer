#ifndef CRYSTAL_H
#define CRYSTAL_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"

class Crystal : public AndromedaSystem
{
	GLfloat rotation = 0.0;
public:
	Crystal(GLfloat x, GLfloat y, GLfloat z):AndromedaSystem(x,y,z)
	{
		
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
		//glMateriali(GL_FRONT, GL_SHININESS, 5);   /// <=== when i changed this parameter the color of the outside object changed
		glRotatef(0.0, 0.0, 0.0, 0.0);
		glRotatef(rotation, 0.0, 1.0, 0.0);
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glScalef(0.5, 0.5, 0.5);
		glutSolidIcosahedron();
		glPopMatrix();
	};

	void Update()
	{
		rotation += 1.0;
	}

};

#endif // !CRYSTAL_H

