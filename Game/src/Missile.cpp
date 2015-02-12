#include "Missile.h"
#include <stdio.h>
#include <math.h>
#include <SDL.h>

Missile::Missile() : GameObject()
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

}

void Missile::Initialize()
{

}

void Missile::Update(float dt)
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

		//destroy missiles after traveling a certain distance
		if (_yDistanceTraveled > (_screenHeight))
		{
			//reset missile
			_yDistanceTraveled = 0;
			_xDistanceTraveled = 0;
			SetDirectionVector({ 0.0f, 0.0f, 0.0f });
			SetPosition({ -1000.0f, -1000.0f, -1000.0f });
			SetMissileRotation({ -1000.0f, -1000.0f, -1000.0f });
			SetKillFlag(true);
			return;
		}
		else if (_xDistanceTraveled > (_screenWidth))
		{
			//reset missile
			_xDistanceTraveled = 0;
			_yDistanceTraveled = 0;
			SetDirectionVector({ 0.0f, 0.0f, 0.0f });
			SetPosition({ -1000.0f, -1000.0f, -1000.0f });
			SetMissileRotation({ -1000.0f, -1000.0f, -1000.0f });
			SetKillFlag(true);
			return;
		}
		//if the missile goes out of the screen bounds wrap it too other side
		if (_transform.position.y < 0){
			int ydif = 0;
			ydif = _transform.position.y - _transform.rotation.y;
			_transform.position.y = 480;
			_transform.rotation.y = _transform.position.y - ydif;
		}
		else if (_transform.position.y > _screenHeight){
			int ydif = 0;
			ydif = _transform.position.y - _transform.rotation.y;
			_transform.position.y = 0;
			_transform.rotation.y = _transform.position.y - ydif;
		}
		else if (_transform.position.x < 0){
			int xdif = 0;
			xdif = _transform.position.x - _transform.rotation.x;
			_transform.position.x = 640;
			_transform.rotation.x = _transform.position.x - xdif;
		}
		else if (_transform.position.x > _screenWidth){
			int xdif = 0;
			xdif = _transform.position.x - _transform.rotation.x;
			_transform.position.x = 0;
			_transform.rotation.x = _transform.position.x - xdif;
		}
	}
}

void Missile::Draw(SDL_Renderer *renderer, float dt)
{
	SDL_RenderDrawLine(renderer, _transform.position.x, _transform.position.y, _transform.rotation.x, _transform.rotation.y);
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