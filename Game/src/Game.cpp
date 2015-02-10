#include "Game.h"
#include <GameObject.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>

#include <Box2D\Box2D.h>

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

void Game::InitializeImpl()
{
  SDL_SetWindowTitle(_window, "Game");

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Initialize(_renderer);
  }

  //initialize box 2D world.
  b2Vec2 gravity(0.0f, 1.0f);

  _world = new b2World(gravity);

  //create the definition for our body.
  b2BodyDef boxBodyDef;
  boxBodyDef.type = b2_dynamicBody;

  _boxBody = _world->CreateBody(&boxBodyDef);
  b2Vec2 boxPosition(250, 0);
  _boxBody->SetTransform(boxPosition, 0.0f);

  b2PolygonShape boxShape;
  boxShape.SetAsBox(5, 5);

  _boxFixture = _boxBody->CreateFixture(&boxShape, 0.0f);
}

void Game::UpdateImpl(float dt)
{
  SDL_Event evt;
  SDL_PollEvent(&evt);

  for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
  {
    (*itr)->Update(dt);
  }
}

void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
  std::vector<GameObject *> renderOrder;
  CalculateDrawOrder(renderOrder);

  for (auto itr = renderOrder.begin(); itr != renderOrder.end(); itr++)
  {
    (*itr)->Draw(renderer, dt);
  }
}

void Game::CalculateDrawOrder(std::vector<GameObject *>& drawOrder)
{
  // SUPER HACK GARBAGE ALGO.
  drawOrder.clear();

  auto objectsCopy = _objects;
  auto farthestEntry = objectsCopy.begin();
  while (objectsCopy.size() > 0)
  {
    bool entryFound = true;
    for (auto itr = objectsCopy.begin(); itr != objectsCopy.end(); itr++)
    {
      if (farthestEntry != itr)
      {
        if ((*itr)->GetTransform().position.y < (*farthestEntry)->GetTransform().position.y)
        {
          entryFound = false;
          farthestEntry = itr;
          break;
        }
      }
    }

    if (entryFound)
    {
      GameObject *farthest = *farthestEntry;

      drawOrder.push_back(farthest);
      objectsCopy.erase(farthestEntry);
      farthestEntry = objectsCopy.begin();
    }
  }
}
