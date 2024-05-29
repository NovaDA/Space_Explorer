#ifndef VECTORXYZ_H
#define VECTORXYZ_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>

class vectorXYZ {

	private:
		

	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;

		vectorXYZ()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		vectorXYZ(GLfloat x, GLfloat y, GLfloat z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		void setVectroXYZ(GLfloat x, GLfloat y, GLfloat z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}


		/////////////// DELETE THIS PART AS IT IS USELESS

		GLfloat getX()
		{
			return x;
		}
		GLfloat getY()
		{
			return y;
		}
		GLfloat getZ()
		{
			return z;
		}
};
#endif // !VECTORXYZ_H

