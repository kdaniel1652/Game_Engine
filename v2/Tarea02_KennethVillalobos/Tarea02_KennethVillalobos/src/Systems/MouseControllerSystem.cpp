// Copyright 2024, Kenneth Villalobos

#include <glm/glm.hpp>

#include "../Components/MouseControllerComponent.h"
#include "../Components/SpecialAttackComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"
#include "MouseControllerSystem.h"
#include "../Utils/common.h"

MouseControllerSystem::MouseControllerSystem() {
  this->requireComponent<MouseControllerComponent>();
  this->requireComponent<SpriteComponent>();
  this->requireComponent<TransformComponent>();
  this->requireComponent<TagComponent>();
}

void MouseControllerSystem::subscribeToMouseMotionEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<MouseControllerSystem, MouseMotionEvent>(
    this, &MouseControllerSystem::onMouseMotionEvent);
}

void MouseControllerSystem::onMouseMotionEvent(MouseMotionEvent& event) {
  for (Entity entity : this->getSystemEntities()) {
    auto& transform = entity.getComponent<TransformComponent>();
    auto& sprite = entity.getComponent<SpriteComponent>();
    auto& mouseController = entity.getComponent<MouseControllerComponent>();

    const glm::vec2 entityCenter = glm::vec2(
      transform.position.x + (sprite.width * transform.scale.x),
      transform.position.y + (sprite.height * transform.scale.y));

    const glm::vec2 diff =
      glm::normalize(event.position - entityCenter);

    transform.rotation = glm::degrees(std::atan2(diff.y, diff.x)) + 92.8f;

    if (entity.hasComponent<SpecialAttackComponent>()) {
      Entity& clone = entity.getComponent<SpecialAttackComponent>().clone;
      if (clone.isValid()) {
        auto& cloneTransform = clone.getComponent<TransformComponent>();

        const float radius = glm::distance(transform.position,
          cloneTransform.position);
        const float radians = glm::radians(transform.rotation + 90);

        cloneTransform.position.x = transform.position.x +
          radius * std::cos(radians);
        cloneTransform.position.y = transform.position.y +
          radius * std::sin(radians);
        cloneTransform.rotation = transform.rotation + 180.0f;
      }
    }
  }
}
