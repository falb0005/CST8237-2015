#include "Missile.h"
#include <stdio.h>
#include <math.h>
#include <SDL.h>
#include <Windows.h>
#include <SDL_image.h>

Missile::Missile()
{
	_transform.position = { -10000.0f, -10000.0f, -10000.0f };
	_transform.rotation = { -10000.0f, -10000.0f, -10000.0f };
	_directionVector = { 0.0f, 0.0f, 0.0f };
	_speed = 250;
	_missileSpeed = 0;
	_killFlag = true;
}

Missile::~Missile()
{
	SDL_DestroyTexture(_missileTexture);
}

void Missile::Initialize(SDL_Renderer * renderer, int angle)
{
	_missileTexture = IMG_LoadTexture(renderer, "res/missile.bmp");
	if (_missileTexture == NULL){
		printf("%s\n", SDL_GetError());
		Sleep(3000);
		exit(EXIT_FAILURE);
	}
	int w, h;
	if (SDL_QueryTexture(_missileTexture, NULL, NULL, &w, &h) == -1){
		printf("%s\n", SDL_GetError());
		Sleep(3000);
		exit(EXIT_FAILURE);
	}
	_missileRect.w = w;
	_missileRect.h = h;
}

void Missile::Update(float dt, float rotationDegrees)
{
	if (_killFlag == false)
	{
		float temp = 0;
		temp = (_speed * (_directionVector.y*0.1f)) * (1 * dt);
		_yDistanceTraveled += pow(temp, 2);
		_transform.position.y += temp;
		_transform.rotation.y += temp;
		temp = (_speed * (_directionVector.x*0.1f)) * (1 * dt);
		_xDistanceTraveled += pow(temp, 2);
		_transform.position.x += temp;
		_transform.rotation.x += temp;
		
		//if the missile goes out of the screen bounds bounce off wall
		if (_transform.position.y < 27){
			_transform.position.y = 27;
			_directionVector.y *= -1.0f;
			_numBounces++;
		}
		else if (_transform.position.y > _screenHeight - 27){
			_transform.position.y = _screenHeight - 33;
			_directionVector.y *= -1.0f;
			_numBounces++;
		}
		else if (_transform.position.x < 27){
			_transform.position.x = 27;
			_directionVector.x *= -1.0f;
			_numBounces++;
		}
		else if (_transform.position.x > _screenWidth - 27){
			_transform.position.x = _screenWidth - 27;
			_directionVector.x *= -1.0f;
			_numBounces++;
		}
		if (_numBounces > MAX_BOUNCES){
			_numBounces = 0;
			_xDistanceTraveled = 0;
			_yDistanceTraveled = 0;
			SetDirectionVector({ 0.0f, 0.0f, 0.0f });
			SetPosition({ -1000.0f, -1000.0f, -1000.0f });
			SetMissileRotation({ -1000.0f, -1000.0f, -1000.0f });
			SetKillFlag(true);
		}
	}
}

void Missile::Draw(SDL_Renderer *renderer, SDL_Window *window, float dt)
{
	SDL_Rect posRect;
	posRect.x = _transform.position.x;
	posRect.y = _transform.position.y;
	posRect.w = 8;
	posRect.h = 8;
	SDL_Point center;
	center.x = 4;
	center.y = 4;
	SDL_RenderCopyEx(renderer, _missileTexture, NULL, &posRect, 0.0f, &center, SDL_FLIP_NONE);
}

void Missile::SetPosition(Vector3 position)
{
	_transform.position = position;
}

Vector3 Missile::GetPosition()
{
	return this->_transform.position;
}

void Missile::SetMissileSpeed(int missileSpeed)
{
	_missileSpeed = missileSpeed;
}

int Missile::GetMissileSpeed()
{
	return _missileSpeed;
}


void Missile::SetDirectionVector(Vector3 directionVector)
{
	_directionVector = directionVector;
}

Vector3 Missile::GetDirectionVector()
{
	return _directionVector;
}

Vector3 Missile::GetMissileRotation()
{
	return _transform.rotation;
}

void Missile::SetMissileRotation(Vector3 rotation)
{
	_transform.rotation = rotation;
}

void Missile::SetKillFlag(bool flag)
{
	_killFlag = flag;
}

bool Missile::GetKillFlag()
{
	return _killFlag;
}

void Missile::SetNumBounces(int numBounces)
{
	_numBounces = numBounces;
}