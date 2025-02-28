// Copyright 2024 Kenneth Villalobos

#include "CameraMovementSystem.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../Game/Game.h"

CameraMovementSystem::CameraMovementSystem() {
  this->requireComponent<CameraFollowComponent>();
  this->requireComponent<TransformComponent>();
}

void CameraMovementSystem::update(SDL_Rect& camera) {
  for (auto entity : this->getSystemEntities()) {
    const auto& transform = entity.getComponent<TransformComponent>();

    if (transform.position.x + (Game::windowWidth / 2) < Game::mapWidth) {
      camera.x = static_cast<int>(transform.position.x) -
        (Game::windowWidth / 2);
    }

    if (transform.position.y + (Game::windowHeight / 2) < Game::mapHeight) {
      camera.y = static_cast<int>(transform.position.y) -
        (Game::windowHeight / 2);
    }

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
  }
}
