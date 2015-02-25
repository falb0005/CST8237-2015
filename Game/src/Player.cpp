#include "Player.h"
#include <stdio.h>
#include <math.h>
#include <SDL_image.h>
#include <SDL.h>
#include <windows.h>

Player::Player() : GameObject()
{
	/*_transform.position = { 320.0f, 240.0f, 0.0f };
	_transform.rotation = { 320.0f, 230.0f, 0.0f };
	_directionVector = { 0.0f, 0.0f, 0.0f };
	_speed = 80;
	_rotationSpeed = 100;*/
	_playerSpeed = 0;
}

Player::~Player()
{
	SDL_DestroyTexture(_playerTexture);
}

void Player::Initialize(SDL_Renderer *renderer, int angle)
{
	_playerAngle = angle;
	if (angle == 0){
		_playerTexture = IMG_LoadTexture(renderer, "res/tank0.bmp");
		if (_playerTexture == NULL){
			printf("%s\n", SDL_GetError());
			Sleep(3000);
			exit(EXIT_FAILURE);
		}
		int w, h;
		if (SDL_QueryTexture(_playerTexture, NULL, NULL, &w, &h) == -1){
			printf("%s\n", SDL_GetError());
			Sleep(3000);
			exit(EXIT_FAILURE);
		}
		_playerRect.w = w;
		_playerRect.h = h;
	}
	else{
		_playerTexture = IMG_LoadTexture(renderer, "res/tank0.bmp");
		if (_playerTexture == NULL){
			printf("%s\n", SDL_GetError());
			Sleep(3000);
			exit(EXIT_FAILURE);
		}
		int w, h;
		if (SDL_QueryTexture(_playerTexture, NULL, NULL, &w, &h) == -1){
			printf("%s\n", SDL_GetError());
			Sleep(3000);
			exit(EXIT_FAILURE);
		}
		_playerRect.w = w;
		_playerRect.h = h;
	}
}

void Player::Update(float dt, float rotationDegrees)
{
	/*_transform.position.y += (_speed * (_directionVector.y*0.1f)) * (1 * dt);
	_transform.rotation.y += (_speed * (_directionVector.y*0.1f)) * (1 * dt);
	_transform.position.x += (_speed * (_directionVector.x*0.1f)) * (1 * dt);
	_transform.rotation.x += (_speed * (_directionVector.x*0.1f)) * (1 * dt);*/
	if (_transform.position.y < 33){
		//int ydif = 0;
		//ydif = _transform.position.y - _transform.rotation.y;
		_transform.position.y = 33;
		//_transform.rotation.y = _transform.position.y - ydif;
	}
	else if (_transform.position.y > _screenHeight - 33){
		//int ydif = 0;
		//ydif = _transform.position.y - _transform.rotation.y;
		_transform.position.y = _screenHeight - 33;
		//_transform.rotation.y = _transform.position.y - ydif;
	}
	else if (_transform.position.x < 33){
		//int xdif = 0;
		//xdif = _transform.position.x - _transform.rotation.x;
		_transform.position.x = 33;
		//_transform.rotation.x = _transform.position.x - xdif;
	}
	else if (_transform.position.x > _screenWidth - 33){
		//int xdif = 0;
		//xdif = _transform.position.x - _transform.rotation.x;
		_transform.position.x = _screenWidth - 33;
		//_transform.rotation.x = _transform.position.x - xdif;
	}
	float deltaY, deltaX;
	deltaY = _transform.rotation.y - _transform.position.y;
	deltaX = _transform.rotation.x - _transform.position.x;
	_playerAngle = rotationDegrees;
	//_playerAngle = atan(deltaY / deltaX) * 180 / 3.14f;
	_playerRect.x = _transform.position.x;
	_playerRect.y = _transform.position.y;
}

void Player::Draw(SDL_Renderer *renderer, SDL_Window *window, float dt)
{
	/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);*
	/*SDL_RenderDrawLine(renderer, _transform.position.x, _transform.position.y, _transform.rotation.x, _transform.rotation.y);*/
	SDL_Point center;
	center.x = 17;
	center.y = 9;
	posRect.x = _transform.position.x - center.x;
	posRect.y = _transform.position.y - center.y;
	posRect.w = _playerRect.w;
	posRect.h = _playerRect.h;
	//printf("Player Angle: %d\n", _playerAngle);
	if (_isKilled == false)
	SDL_RenderCopyEx(renderer, _playerTexture, NULL, &posRect, _playerAngle, &center, SDL_FLIP_NONE);
	else
	{
		static float time_Elapsed = 0.0f;
		static float angle = 0.0f;
		time_Elapsed += dt;
		if (time_Elapsed > 2.0f){//ensure a delay has occured since last firing
			time_Elapsed = 0.0f;
			_isKilled = false;
		}
		else{
			angle++;
			if (angle == 360)
				angle = 0;
			SDL_RenderCopyEx(renderer, _playerTexture, NULL, &posRect, angle, &center, SDL_FLIP_NONE);
		}
	}

}

void Player::SetPosition(Vector3 position)
{
	_transform.position = position;
}

Vector3 Player::GetPosition()
{
	return this->_transform.position;
}

void Player::SetPlayerSpeed(int playerSpeed)
{
	_playerSpeed = playerSpeed;
}

int Player::GetPlayerSpeed()
{
	return _playerSpeed;
}


void Player::SetDirectionVector(Vector3 directionVector)
{
	_directionVector = directionVector;
}

Vector3 Player::GetDirectionVector()
{
	return _directionVector;
}

Vector3 Player::GetPlayerRotation()
{
	return _transform.rotation;
}

void Player::SetPlayerRotation(Vector3 rotation)
{
	_transform.rotation = rotation;
}

bool Player::GetIsKilled()
{
	return _isKilled;
}

void Player::SetIsKilled(bool isKilled)
{
	_isKilled = isKilled;
}