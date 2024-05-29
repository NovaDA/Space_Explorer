#ifndef IMAGESLOADER_H
#define IMAGESLOADER_H

#include "shared\freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#include "AndromedaSystem.h"

#define JUPITER     0 /// Jupiter
#define MERCURY		1 /// Mercury
#define URANUS		2 /// Uranus
#define VENUS		3 /// Venus
#define NEPTUNE		4 /// Neptune
#define STARFIELD   5 /// textureForHoops
#define HUD         6 /// HUD texture
#define SPACE		7 /// OUTER_SPACE
#define TEXTURE_COUNT 8
GLuint  textures[TEXTURE_COUNT];
const char *textureFiles[TEXTURE_COUNT] = { "jupiter.tga", "mercury.tga","uranus.tga","venus.tga", "neptune.tga", "starField.tga","hud.tga", "Outer_Space.tga" };

GLuint texture;

#endif // !IMAGESLOADER_H

