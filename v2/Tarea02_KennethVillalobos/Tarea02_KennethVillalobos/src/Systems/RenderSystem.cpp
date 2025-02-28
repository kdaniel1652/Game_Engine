// Copyright 2024, Kenneth Villalobos

#include "../Components/GameOverComponent.h"
#include "../Components/PauseComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

#include "RenderSystem.h"

#include "../Utils/common.h"

RenderSystem::RenderSystem() {
  this->requireComponent<SpriteComponent>();
  this->requireComponent<TransformComponent>();
}

void RenderSystem::update(SDL_Renderer* renderer,
  std::shared_ptr<AssetStore>& assetStore) {
  for (auto entity : this->getSystemEntities()) {
    if ((!entity.hasComponent<GameOverComponent>() &&
      !entity.hasComponent<PauseComponent>()) &&
      (!entity.hasComponent<RespawnComponent>() ||
      !entity.getComponent<RespawnComponent>().defeated)) {
      const auto& sprite = entity.getComponent<SpriteComponent>();
      const auto& transform = entity.getComponent<TransformComponent>();

      SDL_Rect destRect = {
        static_cast<int>(transform.position.x),
        static_cast<int>(transform.position.y),
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
        SDL_FLIP_NONE
      );

      if (entity.hasComponent<RespawnComponent>() &&
        entity.getComponent<RespawnComponent>().msSinceRespawn <
        MS_GRACE_TIME) {
        auto& respawn = entity.getComponent<RespawnComponent>();
        if (respawn.msSinceRespawn < MS_GRACE_TIME &&
          respawn.forceField.isValid()) {
          auto& forceFieldSprite =
            respawn.forceField.getComponent<SpriteComponent>();

          SDL_SetTextureAlphaMod(assetStore->getTexture(
            forceFieldSprite.assetId), 128);

          SDL_Rect destRectForceField = {
            static_cast<int>(transform.position.x -
              sprite.width * transform.scale.x * 0.8 / 2),
            static_cast<int>(transform.position.y -
              sprite.height * transform.scale.y * 0.8 / 2),
            static_cast<int>(sprite.width * transform.scale.x * 1.8),
            static_cast<int>(sprite.height * transform.scale.y * 1.8)
          };

          SDL_RenderCopyEx(
            renderer,
            assetStore->getTexture(forceFieldSprite.assetId),
            &forceFieldSprite.srcRect,
            &destRectForceField,
            transform.rotation,
            NULL,
            SDL_FLIP_NONE
          );
        }
      }
    }
  }
}
