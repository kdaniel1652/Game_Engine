// Copyright 2024 Kenneth Villalobos

#include "../Components/CameraIndependentComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "RenderSystem.h"

RenderSystem::RenderSystem() {
  this->requireComponent<SpriteComponent>();
  this->requireComponent<TransformComponent>();
}

void RenderSystem::update(SDL_Renderer* renderer,
  std::shared_ptr<AssetStore>& assetStore, const SDL_Rect& camera) {
  int positionX = 0;
  int positionY = 0;
  for (auto entity : this->getSystemEntities()) {
    const auto& sprite = entity.getComponent<SpriteComponent>();
    const auto& transform = entity.getComponent<TransformComponent>();

    positionX = static_cast<int>(transform.position.x);
    positionY = static_cast<int>(transform.position.y);

    if (!entity.hasComponent<CameraIndependentComponent>()) {
      positionX -= camera.x;
      positionY -= camera.y;
    }

    SDL_Rect destRect = {
      positionX,
      positionY,
      static_cast<int>(sprite.width * transform.scale.x),
      static_cast<int>(sprite.height * transform.scale.y)
    };

    SDL_RenderCopyEx(
      renderer,
      assetStore->getTexture(sprite.assetId),
      &sprite.srcRect,
      &destRect,
      transform.rotation,
      NULL,
      (sprite.flip)? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
  }
}
