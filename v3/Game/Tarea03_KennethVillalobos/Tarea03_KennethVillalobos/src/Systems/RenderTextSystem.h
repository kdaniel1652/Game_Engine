// Copyright 2024, Kenneth Villalobos

#ifndef RENDERTEXTSYSTEM_H
#define RENDERTEXTSYSTEM_H

#include <memory>
#include <SDL.h>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"

class RenderTextSystem : public System {
public:
  RenderTextSystem();

  void update(SDL_Renderer* renderer,
    std::shared_ptr<AssetStore>& assetStore, const SDL_Rect& camera);
};

#endif  // RENDERTEXTSYSTEM_H
