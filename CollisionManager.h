#include "shared\freeglut.h"
#include <windows.h>
#include "vectorXYZ.h"

class CollisionManager {

	private:
		//vectorXYZ vectorPlayer;
		//vectorXYZ vectorOther;
	public:
		CollisionManager()
		{
			
		}
		bool collisionDetection(vectorXYZ vectorPlayer, vectorXYZ vectorOtherObject, GLfloat radiusPlayer, GLfloat radiusObject)
		{
			GLfloat diffX = vectorPlayer.getX() - vectorOtherObject.getX();
			GLfloat diffY = vectorPlayer.getY() - vectorOtherObject.getY();
			GLfloat diffZ = vectorPlayer.getZ() - vectorOtherObject.getZ();

			float vecDist = sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
			if (vecDist <= (radiusPlayer + radiusObject))
			{
				return true;
			}
			return false;
		}

};


