// Copyright 2024 Kenneth Villalobos

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include <memory>
#include <SDL.h>

class RenderSystem : public System {
public:
  RenderSystem();

  void update(SDL_Renderer* renderer,
    std::shared_ptr<AssetStore>& assetStore, const SDL_Rect& camera);
};

#endif  // RENDERSYSTEM_H
