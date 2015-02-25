/**
* \class Game.h
* \brief A class that represents the game
* \author  Johnathan Falbo
* \date February 24, 2015
*/

#pragma once

#include "../../Engine/src/GameEngine.h"
#include "Player.h"
#include "../../Engine/src/MathUtils.h"
#include "Missile.h"

union SDL_Event;
struct SDL_Texture;
struct SDL_Renderer;

class b2World;
class b2Body;
class b2Fixture;

class Missile;

#define NUM_MISSILES 5

class Game: public GameEngine
{
  friend class GameEngine;

public:
	/**
	* \fn void Gane::~Game()
	* \brief Game destructor
	*/
  ~Game();

protected:
	/**
	* \fn void Game::Game()
	* \brief Default Game Constructor
	*/
  Game();

  /**
  * \fn void Game::InitializeImpl()
  * \brief A function that is used to initialize the game to default values
  */
  void InitializeImpl(SDL_Renderer *renderer);

  /**
  * \fn void Game::UpdateImpl(float, SDL_Window*)
  * \brief A function that is used to update the game each tick
  * \param dt The time in fractions of a second since the last pass.
  * \param renderer The SDL renderer used to draw the object.
  */
  void UpdateImpl(float dt, SDL_Window* window);

  /**
  * \fn void Game::DrawImpl(SDL_Renderer* renderer, float dt)
  * \brief A function that is used to draw the game objects each tick
  * \param renderer The SDL renderer used to draw the object.
  * \param dt The time in fractions of a second since the last pass.
  */
  void DrawImpl(SDL_Renderer *renderer, float dt);

  /**
  * \fn void Game::RenderWorldWalls(SDL_Renderer* renderer)
  * \brief A function that is used to draw the game objects each tick
  * \param renderer The SDL renderer used to draw the object.
  * \param dt The time in fractions of a second since the last pass.
  */
  void RenderWorldWalls(SDL_Renderer* renderer);

  /**
  * \fn void Game::CheckCollissions()
  * \brief A function that is used to check for various collisions of objects within the world
  */
  void CheckCollissions();

  /**
  * \fn int Game::CheckPlayerMissileCollissions()
  * \brief A function that is used to check player missile collisions
  * \return int -1 if player1, -2 if player2, 1 if both, 0 if none
  */
  int CheckPlayerMissileCollissions();

  /**
  * \fn void Game::Reset()
  * \brief A function that is used to reset the game
  */
  void Reset();

  Player _player1;
  Player _player2;
  Vector3 _player1Pos;
  Vector3 _player2Pos;
  Vector3 _player1Rot;
  Vector3 _player2Rot;
  Vector2 _endPointOffset;
  float _speed;
  float _rotationSpeed;
  float _rotationDegrees;
  SDL_Rect _backgroundRect;
  SDL_Surface *_backgroundImage;
  SDL_Texture *_backgroundTexture;
  int _screenWidth = 640;
  int _screenHeight = 480;
  SDL_Rect posRect;
  char* buffer;
  char* buffer2;
  Missile _player1Missiles[NUM_MISSILES];
  Missile _player2Missiles[NUM_MISSILES];
  int _player1Score = 0;
  int _player2Score = 0;
  char *_title;
};