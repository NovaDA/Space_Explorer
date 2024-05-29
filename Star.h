#include "include\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "vectorXYZ.h"

struct VectorStarPos 
{
	GLfloat x, y, z;
};
class Star
{
	int typeStar = 0.0;                         /// <=== useless for now
	VectorStarPos starPosition;					///// <==== useless
	bool collision = false;						 /// <=== useless for now
	vectorXYZ position;
	public:
		Star();
		void setPosition(float x, float y, float z);
		VectorStarPos getPosition();
		vectorXYZ getNewPoistion();
		void Render();						
		void Update();									/// <=== useless for now
		bool getCollision();                            /// <=== useless for now
		void setCollision();							/// <=== useless for now
		
};

VectorStarPos SVectorStarPos(GLfloat x, GLfloat y, GLfloat z);



