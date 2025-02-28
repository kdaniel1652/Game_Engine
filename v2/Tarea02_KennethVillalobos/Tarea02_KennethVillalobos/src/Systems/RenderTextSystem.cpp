// Copyright 2024, Kenneth Villalobos

#include "../Components/GameOverComponent.h"
#include "../Components/PauseComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/TransformComponent.h"
#include "RenderTextSystem.h"

RenderTextSystem::RenderTextSystem() {
  this->requireComponent<TextLabelComponent>();
  this->requireComponent<TransformComponent>();
}

void RenderTextSystem::update(SDL_Renderer* renderer,
  std::shared_ptr<AssetStore>& assetStore) {
  for (auto entity : this->getSystemEntities()) {
    if (!entity.hasComponent<GameOverComponent>() &&
      !entity.hasComponent<PauseComponent>()) {
      const auto& textLabel = entity.getComponent<TextLabelComponent>();
      const auto& transform = entity.getComponent<TransformComponent>();

      SDL_Surface* surface = TTF_RenderText_Solid(
        assetStore->getFont(textLabel.assetId),
        textLabel.text.c_str(),
        { static_cast<unsigned char>(textLabel.r),
          static_cast<unsigned char>(textLabel.g),
          static_cast<unsigned char>(textLabel.b),
          static_cast<unsigned char>(textLabel.alpha) });

      SDL_Texture* texture =
        SDL_CreateTextureFromSurface(renderer, surface);

      SDL_Rect destRect = {
        static_cast<int>(transform.position.x),
        static_cast<int>(transform.position.y),
        static_cast<int>(surface->w * transform.scale.x),
        static_cast<int>(surface->h * transform.scale.y)
      };

      SDL_FreeSurface(surface);

      SDL_RenderCopyEx(
        renderer,
        texture,
        NULL,
        &destRect,
        transform.rotation,
        NULL,
        SDL_FLIP_NONE
      );

      SDL_DestroyTexture(texture);
    }
  }
}
