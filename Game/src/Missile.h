/**
* \class Missile.h
* \brief A class that represents a fired missiles in the game
* \author  Johnathan Falbo
* \date February 24, 2015
*/

#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows
#include <SDL.h>
#include "../../Engine/src/GameObject.h"

#define MAX_BOUNCES 1

struct SDL_Surface;
struct SDL_Window;
struct SDL_Texture;
struct SDL_Rect;

class Missile : public GameObject
{
public:
	/**
	* \fn void Missile::Missile()
	* \brief Missile Default Constructor
	*/
	Missile();
	/**
	* \fn void Missile::~Missile()
	* \brief Missile Deconstructor
	*/
	~Missile();

	/**
	* \fn void Missile::Initialize()
	* \brief A function that is used to initialize the missile to default values
	*/
	void Initialize(SDL_Renderer * renderer, int angle);

	/**
	* \fn void Missile::Update(float)
	* \brief A function that is used to update the missiles position
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Update(float dt, float rotationDegrees);
	/**
	* \fn void Missile::Draw(SDL_Renderer *renderer, float dt)
	* \brief A function that is used to draw the missile
	* \param renderer The SDL renderer used to draw the object.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Draw(SDL_Renderer *renderer, SDL_Window *window, float dt);
	/**
	* \fn void Missile::SetPosition(Vector3 pos)
	* \brief A virtual function that we’ll use as to define how our
	* object is drawn to the screen.
	* \param pos The position you want to set the missile to.
	*/
	void SetPosition(Vector3 pos);
	/**
	* \fn Vector3 GameObject::Draw(SDL_Renderer *renderer, float dt)
	* \brief A function that is used to get the position of the missile
	* \return Vector3 representing the position of the missile
	*/
	Vector3 GetPosition();
	/**
	* \fn void Missile::SetMissileSpeed(int speed)
	* \brief A function that is used to set the missile speed.
	* \param speed The speed you want the missile to travel at.
	*/
	void SetMissileSpeed(int speed);
	/**
	* \fn int Missile::GetMissileSpeed()
	* \brief A function that is used to get the speed of the missile
	* \return int the speed of the missile
	*/
	int GetMissileSpeed();
	/**
	* \fn Vector3 Missile::GetDirectionVector()
	* \brief A function that is used to get the direction vector of the missile
	* \return Vector3 representing the direction the missile is travelling
	*/
	Vector3 GetDirectionVector();
	/**
	* \fn void Missile::SetDirectionVector(Vector3 direction)
	* \brief A function that is used to set the direction fo the missile.
	* \param direction The direction you want the missile to travel.
	*/
	void SetDirectionVector(Vector3 direction);
	/**
	* \fn Vector3 Missile::GetMissileRotation()
	* \brief A virtual function that is used to get the missiles endpoint.
	* \return Vector3 representing the end point fo the missile.
	*/
	Vector3 GetMissileRotation();
	/**
	* \fn void Missile::SetMissileRotation(Vector3 posEndPoint)
	* \brief A function that is used to set the end point of the missle.
	* \param posEndPoint The point to set the endpoint of the Missile to.
	*/
	void SetMissileRotation(Vector3 posEndPoint);
	/**
	* \fn void Missile::SetKillFlag(bool isKilled)
	* \brief A function that is used to set the kill flag of the missile.
	* \param isKilled Wether or not the missile has expired or destroyed a asteroid
	*/
	void SetKillFlag(bool isKilled);
	/**
	* \fn bool Missile::GetKillFlag()
	* \brief A vfunction that is used to set the kill status of the missile
	* \param bool Wether or not the missile is expired or has killed an asteroid
	*/
	bool GetKillFlag();
	/**
	* \fn void Missile::SetNumBounces(int numBounces)
	* \brief A function that is used to set the number of bounces the missile has done.
	* \param numBounces value to set number of missiles bounces too
	*/
	void SetNumBounces(int numBounces);

protected:
	bool _killFlag = false;
	Vector3 _directionVector;
	int _missileSpeed;
	double _xDistanceTraveled = 0;
	double _yDistanceTraveled = 0;
	float _speed;
	int _screenWidth = 640;
	int _screenHeight = 480;
	SDL_Rect _missileRect;
	SDL_Surface *_missileImage;
	SDL_Texture *_missileTexture;
	int _numBounces = 0;

	bool _winState = false;
	bool _deadState = false;
};