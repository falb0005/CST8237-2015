#pragma once 

#include "MathUtils.h"

struct SDL_Renderer;
struct SDL_Window;

class GameObject
{
public:
  virtual void Initialize(SDL_Renderer * renderer, int angle) = 0;
  
  virtual void Update(float dt, float rotationDegrees) = 0;
  virtual void Draw(SDL_Renderer *renderer, SDL_Window *window, float dt) = 0;

  Transform& GetTransform();

  ~GameObject();

protected:
  GameObject();

  Transform _transform;
};