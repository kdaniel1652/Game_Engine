// Copyright 2024, Kenneth Villalobos

#include <glm/glm.hpp>

#include "../Components/KeyboardControllerComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "KeyboardControllerSystem.h"

KeyboardControllerSystem::KeyboardControllerSystem() {
  this->requireComponent<KeyboardControllerComponent>();
  this->requireComponent<RigidBodyComponent>();
}

void KeyboardControllerSystem::subscribeToKeyboardEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<KeyboardControllerSystem, KeyboardEvent>(
    this, &KeyboardControllerSystem::onKeyboardEvent);
}

void KeyboardControllerSystem::subscribeToGameUnPausedEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<KeyboardControllerSystem, GameUnPausedEvent>(
    this, &KeyboardControllerSystem::onGameUnPausedEvent);
}

void KeyboardControllerSystem::onKeyboardEvent(KeyboardEvent& event) {
  for (Entity entity : this->getSystemEntities()) {
    auto& controller = entity.getComponent<KeyboardControllerComponent>();
    auto& rigidBody = entity.getComponent<RigidBodyComponent>();

    if (event.keyDown) {
      if (event.keycode == SDLK_w) {
        controller.up = true;
      }
      if (event.keycode == SDLK_d) {
        controller.right = true;
      }
      if (event.keycode == SDLK_s) {
        controller.down = true;
      }
      if (event.keycode == SDLK_a) {
        controller.left = true;
      }
    }
    else {
      if (event.keycode == SDLK_w) {
        controller.up = false;
      }
      if (event.keycode == SDLK_d) {
        controller.right = false;
      }
      if (event.keycode == SDLK_s) {
        controller.down = false;
      }
      if (event.keycode == SDLK_a) {
        controller.left = false;
      }
    }

    rigidBody.velocity = glm::vec2(0);
    if (controller.up) {
      rigidBody.velocity.y -= rigidBody.speed;
    }
    if (controller.right) {
      rigidBody.velocity.x += rigidBody.speed;
    }
    if (controller.down) {
      rigidBody.velocity.y += rigidBody.speed;
    }
    if (controller.left) {
      rigidBody.velocity.x -= rigidBody.speed;
    }
  }
}

void KeyboardControllerSystem::onGameUnPausedEvent(
  GameUnPausedEvent& event) {
  for (Entity entity : this->getSystemEntities()) {
    auto& controller = entity.getComponent<KeyboardControllerComponent>();

    controller.up = false;
    controller.right = false;
    controller.down = false;
    controller.left = false;
  }
}
