#ifndef PLANET_H
#define PLANET_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"

class Planet : public AndromedaSystem
{
	GLfloat rotation = 0.0;
	string name;
	GLint type;
	GLfloat radius;
	public:
		Planet(GLfloat x, GLfloat y, GLfloat z, string name, GLfloat radius):AndromedaSystem(x,y,z)
		{
			this->name = name;
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
		
		void findType()
		{
			if (name == "Jupiter")
			{
				type = 0;
			}
			else if (name == "Mercury")
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
				type = 7;
			}
		}
		void Render()                            ////// need to add more control over the type of texture to render
		{
			findType();
			glTranslatef(position.x, position.y, position.z);
			glPushMatrix();
			glRotatef(0.0, 1.0, 0.0, 0.0);
			glRotatef(0.0, 0.0, 1.0, 0.0);
			glRotatef(rotation, 0.0, 0.0, 1.0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[type]);
			GLUquadricObj *quadricJupiter;
			quadricJupiter = gluNewQuadric();
			gluQuadricDrawStyle(quadricJupiter, GLU_FILL);
			gluQuadricNormals(quadricJupiter, GLU_SMOOTH);
			if (type == 4)
			{
				gluQuadricOrientation(quadricJupiter, GLU_INSIDE);
			}
			else
			{
				gluQuadricOrientation(quadricJupiter, GLU_OUTSIDE);
			}
			gluQuadricTexture(quadricJupiter, GL_TRUE);
			gluSphere(quadricJupiter, radius, 50, 35);
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		};

		void Update()
		{
			rotation += 0.1;
		}
};

#endif // !PLANET_H

