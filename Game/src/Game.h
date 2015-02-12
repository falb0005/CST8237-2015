#pragma once

#include <GameEngine.h>
#include "Player.h"
#include "../../Engine/src/MathUtils.h"

union SDL_Event;
struct SDL_Texture;
struct SDL_Renderer;

class b2World;
class b2Body;
class b2Fixture;

class Game: public GameEngine
{
  friend class GameEngine;

public:
  ~Game();

protected:
  Game();

  void InitializeImpl(SDL_Renderer *renderer);
  void UpdateImpl(float dt);
  void DrawImpl(SDL_Renderer *renderer, float dt);
  void RenderWorldWalls(SDL_Renderer* renderer);
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

  int _screenWidth = 640;
  int _screenHeight = 480;
};