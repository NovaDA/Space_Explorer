#ifndef IMAGESLOADER_H
#define IMAGESLOADER_H

#include "shared/freeglut.h"
#include "windows.h"
#include "math.h"
#include <iostream>
#define BALL 0 //football map
#define IMAGE1      1 //pingu
#define IMAGE2      2 //a horse
#define IMAGE3      3 //wooden floor
#define IMAGE4      4 //stone texture
#define MERCURY		5 /// MERCURY 
#define MERCURY2	6 /// MERCURY
#define STARFIELD   7 /// textureForHoops
#define HUD         8 /// HUD texture
#define SPACE		9 ////  OUTER_SPACE
#define TEXTURE_COUNT 10
GLuint  textures[TEXTURE_COUNT];
const char *textureFiles[TEXTURE_COUNT] = { "Football.tga", "pingu.tga", "horse.tga","floor.tga","stone.tga","mercury.tga","mercury2.tga","starField.tga","hud.tga", "Outer_Space.tga" };



#endif // !IMAGESLOADER_H


