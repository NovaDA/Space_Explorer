#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"

class Atmosphere : public AndromedaSystem
{
	GLfloat rotation = 0.0;
	GLfloat radius = 0.0;
	string name;
	GLint type;
	GLfloat R, G, B, A;
	bool rotationActive = false;
public:
	Atmosphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, string name, GLfloat R, 
		GLfloat G, GLfloat B, GLfloat A ,bool rotationActive) :AndromedaSystem(x, y, z)
	{
		this->name = name;
		this->radius = radius;
		this->R = R;
		this->G = G;
		this->B = B;
		this->A = A;
		this->rotationActive = rotationActive;
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

	void findType()
	{
		if (name == "Jupiter")
		{
			type = 0;
		}
		else if(name == "Mercury")
		{
			type = 1;
		}
		else if (name == "Uranus")
		{
			type = 2;
		}
		else if (name == "Venus")
		{
			type = 3;
		}
		else if (name == "Neptune")
		{
			type = 4;
		}
		else
		{
			type = -1;
		}
	}
	
	void Render()
	{
		findType();
		if (type == -1)
		{
			glPushMatrix();
			glEnable(GL_BLEND);
			glColor4f(R, G, B, A);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRotatef(0.0, 1.0, 0.0, 0.0);
			glRotatef(0.0, 0.0, 1.0, 0.0);
			glRotatef(rotation, 0.0, 0.0, 1.0);
			glTranslatef(position.x, position.y, position.z);
			if (type == 3)
			{
				glMateriali(GL_FRONT, GL_SHININESS, 128);
			}
			glutSolidSphere(radius, 15.0, 15.0);
			glDisable(GL_BLEND);
			//glMateriali(GL_FRONT, GL_SHININESS, 128);
			glPopMatrix();
		}
		else
		{
			glTranslatef(position.x, position.y, position.z);
			glPushMatrix();
			glEnable(GL_BLEND);
			glColor4f(0.8, 0.8, 0.8, A);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glRotatef(0.0, 1.0, 0.0, 0.0);
			glRotatef(0.0, 0.0, 1.0, 0.0);
			glRotatef(rotation, 0.0, 0.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[type]);
			GLUquadricObj *quadricAtmosphere;
			quadricAtmosphere = gluNewQuadric();
			gluQuadricDrawStyle(quadricAtmosphere, GLU_FILL);
			gluQuadricNormals(quadricAtmosphere, GLU_SMOOTH);
			gluQuadricOrientation(quadricAtmosphere, GLU_OUTSIDE);
			gluQuadricTexture(quadricAtmosphere, GL_TRUE);
			gluSphere(quadricAtmosphere, radius, 50, 35);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glPopMatrix();
		}
		
	};

	void Update()
	{
		if (rotationActive == true)
		{
			rotation += 0.1;
		}
	}

};

#endif


