#include "shared/freeglut.h"	
#include "vectorXYZ.h"

class Camera
{
private:
	vectorXYZ M_position; ////  position
	vectorXYZ V_position; //// viewposition
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;	
	void GetViewDir ( void );
public:
	Camera();			
	void Render ( void );	
	void MovePlayer(vectorXYZ Direction);
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );
	void MoveForwards ( GLfloat Distance );
	void StrafeRight ( GLfloat Distance );
	vectorXYZ getPlayerLocation();
	void vector_vector_sum(vectorXYZ actualPos, vectorXYZ nextPos);
};


