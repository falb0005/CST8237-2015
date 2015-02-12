/**
* \class MathUtils.h
* \brief A class that is used to perform mathimatical calulation
* for the game
* \author Justin Wilkinson, Johnathan Falbo
* \date January 29, 2014
*/
#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

// A structure to hold two floats. Similar to SDL_Point (though it contains ints).
struct Vector2
{
	float x;
	float y;
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

struct Transform
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};

class MathUtils
{
public:
	/**
	* \fn static float MathUtils::ToRadians(float degrees)
	* \brief A static function that is used to convert degrees to radians
	* \param degrees  to convert to radians.
	* \return float radians representing the degree value
	*/
	static float ToRadians(float degrees);
	/**
	* \fn static float MathUtils::ToDegrees(float radians)
	* \brief A static function that is used to convert radians to degrees
	* \param radians to convert to degrees.
	* \return float degrees representing the radian value
	*/
	static float ToDegrees(float radians);
	/**
	* \fn static float MathUtils::CalculateShipSlope(int posX, int posY, int posXOffset, int posYOffset)
	* \brief A static function that is used to calculate the ships slope
	* \param posX value of ships x position.
	* \param posY value of ships y position.
	* \param posXOffset value of ships x end point position.
	* \param posYOffset value of ships y end point position.
	* \return float representing the slope of the ship
	*/
	static float CalculateShipSlope(int posX, int posY, int posXOffset, int posYOffset);
	/**
	* \fn static float MathUtils::CalculateShipXVector(int posX, int posXOffset)
	* \brief A static function that is used to calculate the ships x vector slope
	* \param posX value of ships x position.
	* \param posXOffset value of ships x end point position.
	* \return float representing the x vector of the ship
	*/
	static float CalculateShipXVector(int posX, int posXOffset);
	/**
	* \fn static float MathUtils::CalculateShipYVector(int posY, int posYOffset)
	* \brief A static function that is used to calculate the ships y vector slope
	* \param posY value of ships y position.
	* \param posYOffset value of ships y end point position.
	* \return float representing the y vector of the ship
	*/
	static float CalculateShipYVector(int posY, int posYOffset);
	/**
	* \fn static float MathUtils::CalculateDistance(float x1, float x2, float y1, float y2)
	* \brief A static function that is used to calculate the distance between two points
	* \param x1 x value of point 1.
	* \param x2 x value of point 2.
	* \param y1 y value of point 1.
	* \param y2 y value of point 2.
	* \return float representing the distance between the two points
	*/
	static float CalculateDistance(float x1, float x2, float y1, float y2);
};