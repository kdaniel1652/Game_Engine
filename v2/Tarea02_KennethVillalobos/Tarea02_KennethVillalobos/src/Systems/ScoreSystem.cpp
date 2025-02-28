// Copyright 2024, Kenneth Villalobos

#include "../Components/PointsComponent.h"
#include "../Components/ScoreComponent.h"
#include "../Components/TextLabelComponent.h"
#include "ScoreSystem.h"

ScoreSystem::ScoreSystem() {
  this->requireComponent<ScoreComponent>();
  this->requireComponent<TextLabelComponent>();
}

void ScoreSystem::subscribeToEnemyKilledEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<ScoreSystem, EnemyKilledEvent>(
    this, &ScoreSystem::onEnemyKilledEvent);
}

void ScoreSystem::onEnemyKilledEvent(EnemyKilledEvent& event) {
  if (event.diyingEntity.hasComponent<PointsComponent>()) {
    auto& points = event.diyingEntity.getComponent<PointsComponent>();

    for (Entity entity : this->getSystemEntities()) {
      auto& score = entity.getComponent<ScoreComponent>();
      auto& textLabel = entity.getComponent<TextLabelComponent>();

      score.score += points.points;

      const size_t minLength = textLabel.text.length();
      textLabel.text = std::to_string(score.score);
      if (textLabel.text.length() < minLength) {
        textLabel.text =
          std::string(minLength - textLabel.text.length(), '0') +
          textLabel.text;
      }
    }
  }
}
