// Copyright 2024, Kenneth Villalobos

#include "../Components/GameStateComponent.h"
#include "GameStateSystem.h"

GameStateSystem::GameStateSystem() {
  this->requireComponent<GameStateComponent>();
}

void GameStateSystem::subscribeToGameOverEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<GameStateSystem, GameOverEvent>(this,
    &GameStateSystem::onGameOverEvent);
}

void GameStateSystem::onGameOverEvent(GameOverEvent& event) {
  for (Entity entity : this->getSystemEntities()) {
    auto& gameState = entity.getComponent<GameStateComponent>();
    gameState.gameOver = true;
  }
}
