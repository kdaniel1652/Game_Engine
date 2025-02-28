// Copyright 2024, Kenneth Villalobos

#include "../Components/PauseComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextLabelComponent.h"

#include "RenderPauseSystem.h"

RenderPauseSystem::RenderPauseSystem() {
  this->requireComponent<PauseComponent>();
}

void RenderPauseSystem::update(SDL_Renderer* renderer,
  std::shared_ptr<AssetStore>& assetStore,
  const int windowWidth, const int windowHeght) {
  for (Entity entity : this->getSystemEntities()) {
    auto& pause = entity.getComponent<PauseComponent>();
    if (pause.mustBeRender) {
      if (entity.hasComponent<SpriteComponent>()) {
        const auto& sprite = entity.getComponent<SpriteComponent>();

        SDL_Rect destRect = {
          0,
          0,
          windowWidth,
          windowHeght
        };

        SDL_SetTextureAlphaMod(assetStore->getTexture(
          sprite.assetId), 120);

        SDL_RenderCopyEx(
          renderer,
          assetStore->getTexture(sprite.assetId),
          &sprite.srcRect,
          &destRect,
          0,
          NULL,
          SDL_FLIP_NONE
        );
      }

      if (entity.hasComponent<TextLabelComponent>()) {
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
          (windowHeght / 2) * 0.3,
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

      pause.mustBeRender = false;
    }
  }
}

void RenderPauseSystem::subscribeToGamePausedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<RenderPauseSystem, GamePausedEvent>(this,
    &RenderPauseSystem::onGamePausedEvent);
}

void RenderPauseSystem::onGamePausedEvent(GamePausedEvent& event) {
  for (Entity entity : this->getSystemEntities()) {
    auto& pause = entity.getComponent<PauseComponent>();
    pause.mustBeRender = true;
  }
}
