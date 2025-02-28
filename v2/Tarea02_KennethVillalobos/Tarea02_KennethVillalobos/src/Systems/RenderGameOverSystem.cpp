// Copyright 2024, Kenneth Villalobos

#include "../Components/GameOverComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/TransformComponent.h"
#include "RenderGameOverSystem.h"

RenderGameOverSystem::RenderGameOverSystem() {
  this->requireComponent<TextLabelComponent>();
  this->requireComponent<GameOverComponent>();
}

void RenderGameOverSystem::update(SDL_Renderer* renderer,
  std::shared_ptr<AssetStore>& assetStore, const int windowWidth,
  const int windowHeght) {
  for (auto entity : this->getSystemEntities()) {
    const auto& textLabel = entity.getComponent<TextLabelComponent>();

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
      (windowWidth / 2) - (surface->w / 2),
      (windowHeght / 2) - (surface->h / 2),
      surface->w,
      surface->h
    };

    SDL_FreeSurface(surface);

    SDL_RenderCopyEx(
      renderer,
      texture,
      NULL,
      &destRect,
      0,
      NULL,
      SDL_FLIP_NONE
    );

    SDL_DestroyTexture(texture);
  }
}
