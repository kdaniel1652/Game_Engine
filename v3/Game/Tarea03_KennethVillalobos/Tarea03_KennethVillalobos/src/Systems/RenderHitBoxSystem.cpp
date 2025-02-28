// Copyright 2024 Kenneth Villalobos

#include "../Components/HitBoxComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "RenderHitBoxSystem.h"

RenderHitBoxSystem::RenderHitBoxSystem() {
  this->requireComponent<HitBoxComponent>();
  this->requireComponent<SpriteComponent>();
  this->requireComponent<TransformComponent>();
}

void RenderHitBoxSystem::update(SDL_Renderer* renderer,
  const SDL_Rect& camera) {
  for (const auto entity : this->getSystemEntities()) {
    const auto& hitBox = entity.getComponent<HitBoxComponent>();
    const auto& sprite = entity.getComponent<SpriteComponent>();
    const auto& transform = entity.getComponent<TransformComponent>();


    SDL_Rect box = {
      static_cast<int>(transform.position.x +
        hitBox.offset.x - camera.x),
      static_cast<int>(transform.position.y +
        hitBox.offset.y - camera.y),
      static_cast<int>(hitBox.width),
      static_cast<int>(hitBox.height)
    };

    if (hitBox.active) {
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    

    SDL_RenderDrawRect(renderer, &box);
  }
}
