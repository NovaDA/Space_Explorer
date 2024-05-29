#include "Star.h"

VectorStarPos SVectorStarPos(GLfloat x, GLfloat y, GLfloat z)
{
	VectorStarPos tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

Star::Star()
{
	//position.setVectroXYZ(0.0, 0.0, 0.0);
	starPosition = SVectorStarPos(0.0, 0.0, 0.0);
	//glTranslatef(starPosition.x, starPosition.y, starPosition.z);
	
}

void Star::setPosition(float x, float y, float z)
{
	//position.setVectroXYZ(x, y, z);
	starPosition.x = x;   /// <- just Decide to use struct
	starPosition.y = y;
	starPosition.z = z;
}

void Star::Render()
{
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glRotatef(0.0, 0.0, 0.0, 1.0);
		glTranslatef(starPosition.x, starPosition.y, starPosition.z);
		glutSolidCone(1.0, 1.0, 10.0, 20.0);

	/*
		glPushMatrix();

	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glTranslatef(starPosition.x, starPosition.y, starPosition.z);
	glutSolidCone(1.0, 1.0, 10.0, 20.0);

	glPushMatrix();
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glutSolidSphere(0.3, 20.0, 10.0);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glTranslatef(-1.0, 0.0, 0.0);
	glutSolidSphere(0.3, 20.0, 10.0);
	glPopMatrix();

	glPopMatrix();
	
	
	
	*/
}

void Star::setCollision()
{
	this->collision = true;
}

vectorXYZ Star::getNewPoistion()
{
	return position;
}
bool Star::getCollision()
{
	return collision;
}

VectorStarPos Star::getPosition()
{
	return starPosition;
}


