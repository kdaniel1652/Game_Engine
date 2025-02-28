// Copyright 2024, Kenneth Villalobos

#ifndef RENDERPAUSESYSTEM_H
#define RENDERPAUSESYSTEM_H

#include <memory>
#include <SDL.h>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"

#include "../Events/GamePausedEvent.h"

class RenderPauseSystem : public System {

public:
  RenderPauseSystem();

  void update(SDL_Renderer* renderer, std::shared_ptr<AssetStore>& assetStore,
    const int windowWidth, const int windowHeght);

  void subscribeToGamePausedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onGamePausedEvent(GamePausedEvent& event);
};

#endif  // RENDERPAUSESYSTEM_H
