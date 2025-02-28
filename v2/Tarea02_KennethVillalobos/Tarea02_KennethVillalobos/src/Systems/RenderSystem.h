// Copyright 2024, Kenneth Villalobos

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <memory>
#include <SDL.h>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"

class RenderSystem : public System {
public:
  RenderSystem();

  void update(SDL_Renderer* renderer, std::shared_ptr<AssetStore>& assetStore);
};

#endif  // RENDERSYSTEM_H
