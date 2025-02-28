// Copyright 2024, Kenneth Villalobos

#ifndef MUSICSYSTEM_H
#define MUSICSYSTEM_H

#include <memory>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/GamePausedEvent.h"
#include "../Events/GameUnPausedEvent.h"

class MusicSystem : public System {
public:
  MusicSystem();

  void update(Entity& song, std::shared_ptr<AssetStore>& assetStore);

  void subscribeToGamePausedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void subscribeToGameUnPausedEvents(
    std::shared_ptr<EventManager>& eventManager);
  void onGamePausedEvent(GamePausedEvent& event);
  void onGameUnPausedEvent(GameUnPausedEvent& event);
};

#endif  // MUSICSYSTEM_H
