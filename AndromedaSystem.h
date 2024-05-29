#ifndef ANDROMEDASYSTEM_H
#define ANDROMEDASYSTEM_H
#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include <string>
#include "vectorXYZ.h"
#include "ImagesLoader.h"
using namespace std;

class AndromedaSystem {

	protected:
	vectorXYZ position;
	public:
		AndromedaSystem(GLfloat x, GLfloat y, GLfloat z)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
		}
		AndromedaSystem(vectorXYZ newPosition)
		{
			this->position = newPosition;
		}

		vectorXYZ getPosition()
		{
			return position;
		}

};




#endif
