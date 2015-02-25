#include "Game.h"
#include "../../Engine/src/GameObject.h"
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include "../../Engine/src/MathUtils.h"
#include <Box2D\Box2D.h>
#include "../../Engine/src/InputManager.h"
#include <windows.h>
#include <string>
#include <iostream>

using namespace std;

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
	free(_title);
}

void Game::InitializeImpl(SDL_Renderer * renderer)
{
	//set initilial window title
  SDL_SetWindowTitle(_window, "Extreme Combat");

  _endPointOffset = { 10, 0 };

  _speed = 80;
  _rotationSpeed = 200;

  //set players facing eachother
  _player1.Initialize(renderer, 0);
  _player2.Initialize(renderer, 180);

  //initialize players too default positions
  _player1Pos = { 50.0f, 240.0f, 0.0f };
  _player2Pos = { _screenWidth - 50, 240.0f, 0.0f };
  _player1Rot = { 60.0f, 240.0f, 0.0f };
  _player2Rot = { _screenWidth - 60, 240.0f, 0.0f };
  _player1.SetPosition(_player1Pos);
  _player2.SetPosition(_player2Pos);
  _player1.SetPlayerRotation(_player1Rot);
  _player2.SetPlayerRotation(_player2Rot);


  //load background image
  _backgroundTexture = IMG_LoadTexture(renderer, "res/BackGround.bmp");
  if (_backgroundTexture == NULL){
	  printf("%s\n", SDL_GetError());
	  Sleep(3000);
	  exit(EXIT_FAILURE);
  }

  //initialize all of the missile.
  for (int i = 0; i < NUM_MISSILES; i++)
  {
	  _player1Missiles[i].Initialize(renderer, 0);
  }
  for (int i = 0; i < NUM_MISSILES; i++)
  {
	  _player2Missiles[i].Initialize(renderer, 0);
  }

  //allocate memory for the title string
  _title = (char*)malloc(sizeof(char)* 50);
}

void Game::UpdateImpl(float dt, SDL_Window* window)
{
	//static player angles
  static float player1RotationDegrees = 0;
  static float player2RotationDegrees = 180;

  //update window title scores
  sprintf_s(_title, 50, "Extreme Combat   Score 1: %d   Score 2: %d", _player1Score, _player2Score);
  SDL_SetWindowTitle(window, _title);

  //input code
  InputManager *im = InputManager::GetInstance();
  im->Update(dt);
  // Check for user input.
  if (_player1.GetIsKilled() == false)
  if (im->IsKeyDown(SDLK_w) == true)//move player 1 forward
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
  else if (im->IsKeyDown(SDLK_d) == true)//turn player 1 right
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
  else if (im->IsKeyDown(SDLK_a) == true)//turn player1 left
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
  else if (im->IsKeyDown(SDLK_SPACE) == true)//fire player 1 missiles
  {
	  float xVector = 0, yVector = 0;

	  //calculate players trajectory.
	  xVector = MathUtils::CalculateShipXVector(_player1.GetPosition().x, _player1.GetPlayerRotation().x);
	  yVector = MathUtils::CalculateShipYVector(_player1.GetPosition().y, _player1.GetPlayerRotation().y);

	  for (int i = 0; i < NUM_MISSILES; i++)
	  {
		  if (_player2.GetIsKilled() == true)
			  break;
		  if (_player1Missiles[i].GetKillFlag() == true)//fire next available missile
		  {
			  static float time_Elapsed = 0.0f;
			  time_Elapsed += dt;
			  if (time_Elapsed > 0.5){//ensure time has elapsed between firing
				  time_Elapsed = 0.0f;
				  _player1Missiles[i].SetDirectionVector({ xVector, yVector, 0.0f });
				  _player1Missiles[i].SetPosition(_player1.GetPosition());
				  _player1Missiles[i].SetMissileRotation(_player1.GetPlayerRotation());
				  _player1Missiles[i].SetKillFlag(false);
				  break;
			  }
		  }
	  }
  }

  if (_player2.GetIsKilled() == false)
  if (im->IsKeyDown(SDLK_UP) == true)//move player 2 forward
  {
	  float xVector = 0, yVector = 0;

	  //get player position and end point position.
	  _player2Pos = _player2.GetPosition();
	  _player2Rot = _player2.GetPlayerRotation();

	  //calculate players trajectory.
	  xVector = MathUtils::CalculateShipXVector(_player2Pos.x, _player2Rot.x);
	  yVector = MathUtils::CalculateShipYVector(_player2Pos.y, _player2Rot.y);

	  //set player tajectory.
	  _player2.SetDirectionVector({ xVector, yVector, 0.0f });

	  //boost player in direction of trajectory.
	  _player2Pos.y += (_speed * (yVector*0.1f)) * (1 * dt);
	  _player2Rot.y += (_speed * (yVector*0.1f)) * (1 * dt);
	  _player2Pos.x += (_speed * (xVector*0.1f)) * (1 * dt);
	  _player2Rot.x += (_speed * (xVector*0.1f)) * (1 * dt);

	  //set player position and end point position.
	  _player2.SetPosition(_player2Pos);
	  _player2.SetPlayerRotation(_player2Rot);
  }
  else if (im->IsKeyDown(SDLK_RIGHT) == true)//turn player 2 right
  {
	  //rotate players ship right.
	  player2RotationDegrees += (_rotationSpeed * dt);
	  player2RotationDegrees += (player2RotationDegrees >= 360.0f ? -360.0f : 0);

	  float rotationRadians = MathUtils::ToRadians(player2RotationDegrees);

	  Vector2 rotatedOffset =
	  {
		  _endPointOffset.x * cosf(rotationRadians) + _endPointOffset.y * sinf(rotationRadians),
		  _endPointOffset.x * sinf(rotationRadians) - _endPointOffset.y * cosf(rotationRadians)
	  };

	  _player2.SetPlayerRotation({ _player2.GetPosition().x + rotatedOffset.x, _player2.GetPosition().y + rotatedOffset.y, 0 });
  }
  else if (im->IsKeyDown(SDLK_LEFT) == true)//turn player 2 left
  {
	  //rotate players ship left
	  player2RotationDegrees -= (_rotationSpeed * dt);
	  player2RotationDegrees += (player2RotationDegrees <= 0.0f ? +360.0f : 0);

	  float rotationRadians = MathUtils::ToRadians(player2RotationDegrees);

	  Vector2 rotatedOffset =
	  {
		  _endPointOffset.x * cosf(rotationRadians) + _endPointOffset.y * sinf(rotationRadians),
		  _endPointOffset.x * sinf(rotationRadians) - _endPointOffset.y * cosf(rotationRadians)
	  };

	  _player2.SetPlayerRotation({ _player2.GetPosition().x + rotatedOffset.x, _player2.GetPosition().y + rotatedOffset.y, 0 });
  }
  else if (im->IsKeyDown(SDLK_RETURN) == true || im->IsKeyDown(SDLK_RETURN2) == true)//fire player 2 missiles
  {
	  float xVector = 0, yVector = 0;

	  //calculate players trajectory.
	  xVector = MathUtils::CalculateShipXVector(_player2.GetPosition().x, _player2.GetPlayerRotation().x);
	  yVector = MathUtils::CalculateShipYVector(_player2.GetPosition().y, _player2.GetPlayerRotation().y);

	  for (int i = 0; i < NUM_MISSILES; i++)
	  {
		  if (_player1.GetIsKilled() == true)
			  break;
		  if (_player2Missiles[i].GetKillFlag() == true)//fire next available missile
		  {
			  static float time_Elapsed2 = 0.0f;
			  time_Elapsed2 += dt;
			  if (time_Elapsed2 > 0.5){//ensure a delay has occured since last firing
				  time_Elapsed2 = 0.0f;
				  _player2Missiles[i].SetDirectionVector({ xVector, yVector, 0.0f });
				  _player2Missiles[i].SetPosition(_player2.GetPosition());
				  _player2Missiles[i].SetMissileRotation(_player2.GetPlayerRotation());
				  _player2Missiles[i].SetKillFlag(false);
				  break;
			  }
		  }
	  } 
  }
  
  //update players
  _player1.Update(dt, player1RotationDegrees);
  _player2.Update(dt, player2RotationDegrees);

  //update missiles
  for (int i = 0; i < NUM_MISSILES; i++)
  {
	  _player1Missiles[i].Update(dt, NULL);
  }
  for (int i = 0; i < NUM_MISSILES; i++)
  {
	  _player2Missiles[i].Update(dt, NULL);
  }

  //check for various types of collissions
  CheckCollissions();
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{

	//draw background image
	SDL_RenderCopy(renderer, _backgroundTexture, NULL, NULL);

	//draw middle walls
	RenderWorldWalls(renderer);

	//draw missiles
	for (int i = 0; i < NUM_MISSILES; i++)
	{
		_player1Missiles[i].Draw(renderer, _window, dt);
	}
	for (int i = 0; i < NUM_MISSILES; i++)
	{
		_player2Missiles[i].Draw(renderer, _window, dt);
	}

	//draw players
	_player1.Draw(renderer, _window, dt);
	_player2.Draw(renderer, _window, dt);
}

void Game::RenderWorldWalls(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int x = 100;
	SDL_Rect wall;
	wall.h = 100;
	wall.w = 20;
	while (x <= 500){//loop to draw walls accross world
		wall.y = 100;
		wall.x = x;
		SDL_RenderDrawRect(renderer, &wall);
		wall.y = 300;
		SDL_RenderDrawRect(renderer, &wall);
		x += 100;
	}
}

void Game::CheckCollissions()
{
	int result = 0;
	result = CheckPlayerMissileCollissions();
	if (result == 1)//if both players shot eachother
	{
		if (_player1.GetIsKilled() == false && _player2.GetIsKilled() == false)
		{
			_player1Score += 1;
			_player2Score += 1;
			_player1.SetIsKilled(true);
			_player2.SetIsKilled(true);
		}
	}
	else if (result == -1)//if player 1 shot player 2
	{
		if (_player2.GetIsKilled() == false)
		{
			_player1Score += 1;
			_player2.SetIsKilled(true);
		}
	}
	else if (result == -2)//if player 2 shot player 1
	{
		if (_player1.GetIsKilled() == false)
		{
			_player2Score += 1;
			_player1.SetIsKilled(true);
		}
	}
}

//-1 if player1, -2 if player2, 1 if both, 0 if none
int Game::CheckPlayerMissileCollissions()
{
	float disCol1 = 0, disCol2 = 0;
	bool boolCol1 = false, boolCol2 = false;

	//check if player 1 shot player 2
	for (int i = 0; i < NUM_MISSILES; i++)
	{
		if (_player1Missiles[i].GetKillFlag() == false)//if missile is live
		{
			//caluculate distance between missile and oposing player
			disCol1 = MathUtils::CalculateDistance(_player2.GetPosition().x, _player1Missiles[i].GetPosition().x, _player2.GetPosition().y, _player1Missiles[i].GetPosition().y);
			printf("Distance p1: %f\n", disCol1);
			//if missile colllides
			if (disCol1 < 15)
			{
				boolCol1 = true;
				_player1Missiles[i].SetNumBounces(0);
				_player1Missiles[i].SetDirectionVector({ 0.0f, 0.0f, 0.0f });
				_player1Missiles[i].SetPosition({ -1000.0f, -1000.0f, -1000.0f });
				_player1Missiles[i].SetMissileRotation({ -1000.0f, -1000.0f, -1000.0f });
				_player1Missiles[i].SetKillFlag(true);
				break;
			}
		}
	}

	//check if payer 2 has shot player 1
	for (int i = 0; i < NUM_MISSILES; i++)
	{
		if (_player2Missiles[i].GetKillFlag() == false)
		{
			//caluculate distance between missile and oposing player
			disCol2 = MathUtils::CalculateDistance(_player2Missiles[i].GetPosition().x, _player1.GetPosition().x, _player2Missiles[i].GetPosition().y, _player1.GetPosition().y);
			printf("Distance p2: %f\n", disCol2);
			//if missile collides
			if (disCol2 < 15)
			{
				boolCol2 = true;
				_player2Missiles[i].SetNumBounces(0);
				_player2Missiles[i].SetDirectionVector({ 0.0f, 0.0f, 0.0f });
				_player2Missiles[i].SetPosition({ -1000.0f, -1000.0f, -1000.0f });
				_player2Missiles[i].SetMissileRotation({ -1000.0f, -1000.0f, -1000.0f });
				_player2Missiles[i].SetKillFlag(true);
				break;
			}
		}
	}

	//determine outcome of collision analysis
	if (boolCol1 && boolCol2)
	{
		return 1;
	}
	else if (boolCol1)
	{
		return -1;
	}
	else if (boolCol2)
	{
		return -2;
	}
	else
	{
		return 0;
	}
}
