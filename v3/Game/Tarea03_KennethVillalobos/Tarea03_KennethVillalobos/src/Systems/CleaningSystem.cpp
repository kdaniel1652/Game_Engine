// Copyright 2024 Kenneth Villalobos

#include "CleaningSystem.h"
#include "../Components/HealthComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Game/Game.h"

CleaningSystem::CleaningSystem() {
  this->requireComponent<HealthComponent>();
}

void CleaningSystem::update(sol::state& lua) {
  for (auto entity : this->getSystemEntities()) {
    const auto& health = entity.getComponent<HealthComponent>();

    if (health.currentHealth <= 0) {
      if (entity.hasComponent<ScriptComponent>()) {
        const auto& script = entity.getComponent<ScriptComponent>();
        if (script.onDeath != sol::nil) {
          lua["this"] = entity;
          script.onDeath();
        }
        entity.kill();
      }
    }
  }
}
