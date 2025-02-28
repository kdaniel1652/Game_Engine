// Copyright 2024, Kenneth Villalobos

#ifndef GAMESTATESYSTEM_H
#define GAMESTATESYSTEM_H

#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Events/GameOverEvent.h"

class GameStateSystem : public System {

public:
  GameStateSystem();

  void subscribeToGameOverEvents(std::shared_ptr<EventManager>& eventManager);
  void onGameOverEvent(GameOverEvent& event);
};

#endif  // GAMESTATESYSTEM_H
