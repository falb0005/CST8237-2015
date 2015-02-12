#include "MathUtils.h"
#include <math.h>

float MathUtils::ToDegrees(float radians)
{
	float radiansToDegrees = 180.0f / 3.1415926535f;
	return radians * radiansToDegrees;
}

float MathUtils::ToRadians(float degrees)
{
	float degreesToRadians = 3.1415926535f / 180.0f;
	return degrees * degreesToRadians;
}

float MathUtils::CalculateShipSlope(int posX, int posY, int posXOffset, int posYOffset)
{
	return (float)(posYOffset - posY) / (float)(posXOffset - posX);
}

float MathUtils::CalculateShipXVector(int posX, int posXOffset)
{
	return (float)(posXOffset - posX);
}

float MathUtils::CalculateShipYVector(int posY, int posYOffset)
{
	return (float)(posYOffset - posY);
}

float MathUtils::CalculateDistance(float x1, float x2, float y1, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}