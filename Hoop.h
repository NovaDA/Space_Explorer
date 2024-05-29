#ifndef HOOP_H
#define HOOP_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"


class Hoop : public AndromedaSystem
{
	GLfloat rotation = 0.0;
	GLint type;
	public:
		Hoop(GLfloat x, GLfloat y, GLfloat z, GLint type):AndromedaSystem(x, y, z)
		{
			this->type = type;
		
		}
		Hoop(vectorXYZ position, GLint type) :AndromedaSystem(position)
		{
			this->type = type;
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
			glRotatef(-rotation, 0.0, 1.0, 0.0);
			glRotatef(0.0, 0.0, 0.0, 1.0);
			glEnable(GL_BLEND);
			glColor4f(0.8, 0.8, 0.8, 0.5);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures[type]);
			glutSolidTorus(1.0, 5.0, 30, 30);
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
			glPopMatrix();
	
		};

		void Update()
		{
			rotation += 0.5;
		}

};






#endif // !SATELLITE_H



