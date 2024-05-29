#ifndef SATELLITE_H
#define SATELLITE_H

#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"

class Satellite : public AndromedaSystem
{
	GLfloat rotation = 0.0;
	vectorXYZ originalPosition;
	GLfloat radius;
public:
	Satellite(float x, float y, float z, GLfloat radius):AndromedaSystem(x,y,z)
	{
		originalPosition.x = x;
		originalPosition.y = y;
		originalPosition.z = z;
		this->radius = radius;
	}
	Satellite(vectorXYZ position, GLfloat radius) :AndromedaSystem(position)
	{
		this->radius = radius;
		originalPosition.x = position.x;
		originalPosition.y = position.y;
		originalPosition.z = position.z;
	}
	void setPosition(float x, float y, float z)
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
		glRotatef(0.0, 1.0, 0.0, 0.0);
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glTranslatef(position.x, position.y, position.z);
		glColor3f(1.0, 0.0, 0.0);
		glMateriali(GL_FRONT, GL_SHININESS, 5);
		glutSolidSphere(2.5, 15, 15);
		glMateriali(GL_FRONT, GL_SHININESS, 128);

	};

	void Update()
	{
		rotation += 5.0;
	}

	vectorXYZ UpdatePosition()
	{
		GLfloat newX, newY, newZ = 0.0;

		newX = originalPosition.x + cos(rotation * 3.14159 / 180) * radius;
		newY = originalPosition.y + sin(rotation * 3.14159/ 180) * radius;
		newZ = originalPosition.z;
		vectorXYZ newPosition;
		newPosition.x = newX;
		newPosition.y = newY;
		newPosition.z = newZ;
		return newPosition;

	}

};

















#endif // ! METEOR_H

