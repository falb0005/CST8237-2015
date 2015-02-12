/**
* \class Player.h
* \brief A class that represents the player(ship) in the game
* \author  Johnathan Falbo
* \date January 29, 2014
*/

#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

#include "GameObject.h"
#include <SDL.h>

struct SDL_Surface;
struct SDL_Window;
struct SDL_Texture;

class Player : public GameObject
{
public:
	/**
	* \fn void Player::Player()
	* \brief Player Default Constructor
	*/
	Player();
	/**
	* \fn void Player::~Player()
	* \brief Player Deconstructor
	*/
	~Player();

	/**
	* \fn void Player::Initialize()
	* \brief A function that is used to intilize the player to default values
	*/
	void Initialize(SDL_Renderer * renderer);

	/**
	* \fn void Player::Update(float dt)
	* \brief A function that is used to update the position of the Player.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Update(float dt);
	/**
	* \fn void Player::Draw(SDL_Renderer *renderer, float dt)
	* \brief A function that we’ll use as to define how our
	* player is drawn to the screen.
	* \param renderer The SDL renderer used to draw the object.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Draw(SDL_Renderer *renderer, SDL_Window *window, float dt);
	/**
	* \fn void Player::SetPosition(Vector3 pos)
	* \brief A function that is used to set the PLayers position.
	* \param pos The position to set the Player too.
	*/
	void SetPosition(Vector3 pos);
	/**
	* \fn Vector3 Player::GetPosition()
	* \brief A function that is used to get the player sposition.
	* \return Vector3 The position fo the player.
	*/
	Vector3 GetPosition();
	/**
	* \fn void Player::SetPlayerSpeed(int speed)
	* \brief A function that is used to set the speed of the player
	* \param speed The speed to set the player to.
	*/
	void SetPlayerSpeed(int speed);
	/**
	* \fn int Player::GetPlayerSpeed()
	* \brief A function that is used to set the speed of the player
	* \return int The speed the player is traveling at.
	*/
	int GetPlayerSpeed();
	/**
	* \fn Vector3 Player::GetDirectionVector()
	* \brief A function that is used to get the direction of the player
	* \return Vector3 The direction the player is traveling
	*/
	Vector3 GetDirectionVector();
	/**
	* \fn void Player::SetDirectionVector(Vector3 direction)
	* \brief A function that is used to set the direction the player is traveling
	* \param Vector3 The travel direction to set the player to
	*/
	void SetDirectionVector(Vector3 direction);
	/**
	* \fn Vector3 Player::GetPlayerRotation()
	* \brief A function that is used to get the end point of the player
	* \return Vector3 The direction the player is facing
	*/
	Vector3 GetPlayerRotation();
	/**
	* \fn void Player::SetPlayerRotation(Vector3 endPoint)
	* \brief A function that is used to set the direction the player is traveling
	* \param Vector3 The position to set the end point of the player too
	*/
	void SetPlayerRotation(Vector3 endPoint);


protected:
	Vector3 _directionVector;
	int _playerSpeed;
	float _speed;
	float _rotationSpeed;
	int _screenWidth = 640;
	int _screenHeight = 480;
	SDL_Rect _playerRect;
	SDL_Surface *_playerImage;
	SDL_Texture *_playerTexture;

};