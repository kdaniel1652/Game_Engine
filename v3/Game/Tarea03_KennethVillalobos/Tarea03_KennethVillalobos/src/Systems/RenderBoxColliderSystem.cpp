// Copyright 2024 Kenneth Villalobos

#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "RenderBoxColliderSystem.h"

RenderBoxColliderSystem::RenderBoxColliderSystem() {
  this->requireComponent<BoxColliderComponent>();
  this->requireComponent<TransformComponent>();
}

void RenderBoxColliderSystem::update(SDL_Renderer* renderer,
  const SDL_Rect& camera) {
  for (const auto entity : this->getSystemEntities()) {
    const auto& collider = entity.getComponent<BoxColliderComponent>();
    const auto& transform = entity.getComponent<TransformComponent>();

    SDL_Rect box = {
      static_cast<int>(transform.position.x + collider.offset.x - camera.x),
      static_cast<int>(transform.position.y + collider.offset.y - camera.y),
      static_cast<int>(collider.width),
      static_cast<int>(collider.height)
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderDrawRect(renderer, &box);
  }
}
