// Copyright 2024, Kenneth Villalobos

#ifndef RENDERGAMEOVERSYSTEM_H
#define RENDERGAMEOVERSYSTEM_H

#include <memory>
#include <SDL.h>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"

class RenderGameOverSystem : public System {

public:
  RenderGameOverSystem();

  void update(SDL_Renderer* renderer, std::shared_ptr<AssetStore>& assetStore,
    const int windowWidth, const int windowHeght);
};

#endif  // RENDERGAMEOVERSYSTEM_H
