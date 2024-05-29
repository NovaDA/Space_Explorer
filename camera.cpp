#include "camera.h"
#include "math.h"
#include <iostream>
#include "windows.h"


Camera::Camera()
{
	M_position.setVectroXYZ(0.0, 0.0, 200.0);
	V_position.setVectroXYZ(0.0, 0.0, -1.0);

	ViewDirChanged = false;
	RotatedX = RotatedY = RotatedZ = 0.0;
}

void Camera::vector_vector_sum(vectorXYZ actualPos, vectorXYZ nextPos)
{

	M_position.x += nextPos.x;
	M_position.y += nextPos.y;
	M_position.z += nextPos.z;
}

void Camera::GetViewDir()
{
	
	vectorXYZ rotationY, rotationX;
	rotationY.x = cos((RotatedY + 90.0) * 3.14159 / 180);
	rotationY.z = -sin((RotatedY + 90.0) * 3.14159 / 180);


	double cosX = cos (RotatedX * 3.14159 / 180);
	rotationX.x = rotationY.x * cosX;
	rotationX.z = rotationY.z * cosX;

	rotationX.y = sin(RotatedX * 3.14159 / 180);
	V_position = rotationX;


}


void Camera::MovePlayer(vectorXYZ Direction)
{
	vector_vector_sum(M_position, Direction);                  
}

void Camera::RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	ViewDirChanged = true;
}

void Camera::RotateX (GLfloat Angle)
{
	RotatedX += Angle;
	ViewDirChanged = true;
}

void Camera::RotateZ(GLfloat Angle)
{
	RotatedZ += Angle;
	ViewDirChanged = true;
}

void Camera::Render( void )
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -M_position.x, -M_position.y, -M_position.z );
}

void Camera::MoveForwards( GLfloat Distance )
{


	if (ViewDirChanged) GetViewDir();
	vectorXYZ vector_Movement;
	vector_Movement.x = V_position.x * -Distance;
	vector_Movement.y = V_position.y * -Distance;
	vector_Movement.z = V_position.z * -Distance;
	vector_vector_sum(M_position, vector_Movement);

}

void Camera::StrafeRight ( GLfloat Distance )
{
	if (ViewDirChanged) GetViewDir();
	vectorXYZ vector_MovementS;
	vector_MovementS.z = -V_position.x * -Distance;
	vector_MovementS.y = 0.0;
	vector_MovementS.x = V_position.z * -Distance;
	vector_vector_sum(M_position, vector_MovementS);
}

vectorXYZ Camera::getPlayerLocation()
{
	return M_position;
}

