#include "Game.h"
#include <GameObject.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include "../../Engine/src/MathUtils.h"
#include <Box2D\Box2D.h>
#include "InputManager.h"

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
  if (_instance == nullptr)
  {
    _instance = new Game();
  }
  return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{
}

void Game::InitializeImpl(SDL_Renderer * renderer)
{
  SDL_SetWindowTitle(_window, "Extreme Combat");

  _endPointOffset = { 0, 10 };

  _speed = 80;
  _rotationSpeed = 200;
  _player1.Initialize(renderer);

  //initialize players too default positions
  _player1Pos = { 20.0f, 240.0f, 0.0f };
  _player2Pos = { 620.0f, 240.0f, 0.0f };
  _player1Rot = { 1.0f, 0.0f, 0.0f };
  _player2Rot = { -1.0f, 0.0f, 0.0f };
  _player1.SetPosition(_player1Pos);
  _player2.SetPosition(_player2Pos);
  _player1.SetPlayerRotation(_player1Rot);
  _player2.SetPlayerRotation(_player2Rot);
}

void Game::UpdateImpl(float dt)
{
  static float player1RotationDegrees = 0;
  static float player2RotationDegrees = 0;
  SDL_Event evt;
  SDL_PollEvent(&evt);
  InputManager *im = InputManager::GetInstance();
  im->Update(dt);
  // Check for user input.
  if (im->IsKeyDown(SDLK_UP) == true)
  {
	  float xVector = 0, yVector = 0;

	  //get player position and end point position.
	  _player1Pos = _player1.GetPosition();
	  _player1Rot = _player1.GetPlayerRotation();

	  //calculate players trajectory.
	  xVector = MathUtils::CalculateShipXVector(_player1Pos.x, _player1Rot.x);
	  yVector = MathUtils::CalculateShipYVector(_player1Pos.y, _player1Rot.y);

	  //set player tajectory.
	  _player1.SetDirectionVector({ xVector, yVector, 0.0f });

	  //boost player in direction of trajectory.
	  _player1Pos.y += (_speed * (yVector*0.1f)) * (1 * dt);
	  _player1Rot.y += (_speed * (yVector*0.1f)) * (1 * dt);
	  _player1Pos.x += (_speed * (xVector*0.1f)) * (1 * dt);
	  _player1Rot.x += (_speed * (xVector*0.1f)) * (1 * dt);

	  //set player position and end point position.
	  _player1.SetPosition(_player1Pos);
	  _player1.SetPlayerRotation(_player1Rot);
  }
  else if (im->IsKeyDown(SDLK_RIGHT) == true)
  {
	  //rotate players ship right.
	  player1RotationDegrees += (_rotationSpeed * dt);
	  player1RotationDegrees += (player1RotationDegrees >= 360.0f ? -360.0f : 0);

	  float rotationRadians = MathUtils::ToRadians(player1RotationDegrees);

	  Vector2 rotatedOffset =
	  {
		  _endPointOffset.x * cosf(rotationRadians) + _endPointOffset.y * sinf(rotationRadians),
		  _endPointOffset.x * sinf(rotationRadians) - _endPointOffset.y * cosf(rotationRadians)
	  };

	  _player1.SetPlayerRotation({ _player1.GetPosition().x + rotatedOffset.x, _player1.GetPosition().y + rotatedOffset.y, 0 });
  }
  else if (im->IsKeyDown(SDLK_LEFT) == true)
  {
	  //rotate players ship left
	  player1RotationDegrees -= (_rotationSpeed * dt);
	  player1RotationDegrees += (player1RotationDegrees <= 0.0f ? +360.0f : 0);

	  float rotationRadians = MathUtils::ToRadians(player1RotationDegrees);

	  Vector2 rotatedOffset =
	  {
		  _endPointOffset.x * cosf(rotationRadians) + _endPointOffset.y * sinf(rotationRadians),
		  _endPointOffset.x * sinf(rotationRadians) - _endPointOffset.y * cosf(rotationRadians)
	  };

	  _player1.SetPlayerRotation({ _player1.GetPosition().x + rotatedOffset.x, _player1.GetPosition().y + rotatedOffset.y, 0 });
  }

}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
	//RenderWorldWalls(renderer);
	SDL_SetRenderDrawColor(renderer, NULL, NULL, NULL, NULL);
	_player1.Draw(renderer, _window, dt);
}

void Game::RenderWorldWalls(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//left wall
	SDL_RenderDrawLine(renderer, 0, 0, 0, _screenHeight);
	SDL_RenderDrawLine(renderer, 1, 0, 1, _screenHeight);
	SDL_RenderDrawLine(renderer, 2, 0, 2, _screenHeight);
	SDL_RenderDrawLine(renderer, 3, 0, 3, _screenHeight);
	SDL_RenderDrawLine(renderer, 4, 0, 4, _screenHeight);
	SDL_RenderDrawLine(renderer, 5, 0, 5, _screenHeight);
	SDL_RenderDrawLine(renderer, 6, 0, 6, _screenHeight);
	SDL_RenderDrawLine(renderer, 7, 0, 7, _screenHeight);
	SDL_RenderDrawLine(renderer, 8, 0, 8, _screenHeight);
	SDL_RenderDrawLine(renderer, 9, 0, 9, _screenHeight);

	//right wall
	SDL_RenderDrawLine(renderer, _screenWidth - 1, 0, _screenWidth - 1, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 2, 0, _screenWidth - 2, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 3, 0, _screenWidth - 3, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 4, 0, _screenWidth - 4, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 5, 0, _screenWidth - 5, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 6, 0, _screenWidth - 6, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 7, 0, _screenWidth - 7, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 8, 0, _screenWidth - 8, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 9, 0, _screenWidth - 9, _screenHeight);
	SDL_RenderDrawLine(renderer, _screenWidth - 10, 0, _screenWidth - 10, _screenHeight);

	//top wall
	SDL_RenderDrawLine(renderer, 0, 0, _screenWidth, 0);
	SDL_RenderDrawLine(renderer, 0, 1, _screenWidth, 1);
	SDL_RenderDrawLine(renderer, 0, 2, _screenWidth, 2);
	SDL_RenderDrawLine(renderer, 0, 3, _screenWidth, 3);
	SDL_RenderDrawLine(renderer, 0, 4, _screenWidth, 4);
	SDL_RenderDrawLine(renderer, 0, 5, _screenWidth, 5);
	SDL_RenderDrawLine(renderer, 0, 6, _screenWidth, 6);
	SDL_RenderDrawLine(renderer, 0, 7, _screenWidth, 7);
	SDL_RenderDrawLine(renderer, 0, 8, _screenWidth, 8);
	SDL_RenderDrawLine(renderer, 0, 9, _screenWidth, 9);

	//bottom wall
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 1, _screenWidth, _screenHeight - 1);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 2, _screenWidth, _screenHeight - 2);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 3, _screenWidth, _screenHeight - 3);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 4, _screenWidth, _screenHeight - 4);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 5, _screenWidth, _screenHeight - 5);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 6, _screenWidth, _screenHeight - 6);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 7, _screenWidth, _screenHeight - 7);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 8, _screenWidth, _screenHeight - 8);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 9, _screenWidth, _screenHeight - 9);
	SDL_RenderDrawLine(renderer, 0, _screenHeight - 10, _screenWidth, _screenHeight - 10);
}


