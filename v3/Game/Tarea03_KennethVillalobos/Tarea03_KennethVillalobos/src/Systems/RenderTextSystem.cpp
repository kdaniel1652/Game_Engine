// Copyright 2024, Kenneth Villalobos

#include "../Components/CameraIndependentComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/TransformComponent.h"
#include "RenderTextSystem.h"

RenderTextSystem::RenderTextSystem() {
  this->requireComponent<TextComponent>();
  this->requireComponent<TransformComponent>();
}

void RenderTextSystem::update(SDL_Renderer* renderer,
  std::shared_ptr<AssetStore>& assetStore, const SDL_Rect& camera) {
  int positionX = 0;
  int positionY = 0;

  for (auto entity : this->getSystemEntities()) {
    const auto& text = entity.getComponent<TextComponent>();
    const auto& transform = entity.getComponent<TransformComponent>();

    SDL_Surface* surface = TTF_RenderText_Solid(
      assetStore->getFont(text.assetId),
      text.label.c_str(),
      { static_cast<unsigned char>(text.r),
        static_cast<unsigned char>(text.g),
        static_cast<unsigned char>(text.b),
        static_cast<unsigned char>(text.a) });

    SDL_Texture* texture =
      SDL_CreateTextureFromSurface(renderer, surface);

    positionX = static_cast<int>(transform.position.x);
    positionY = static_cast<int>(transform.position.y);
    if (!entity.hasComponent<CameraIndependentComponent>()) {
      positionX -= camera.x;
      positionY -= camera.y;
    }

    SDL_Rect destRect = {
      positionX,
      positionY,
      static_cast<int>(surface->w * transform.scale.x),
      static_cast<int>(surface->h * transform.scale.y)
    };

    SDL_FreeSurface(surface);

    int hola = SDL_RenderCopyEx(
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
