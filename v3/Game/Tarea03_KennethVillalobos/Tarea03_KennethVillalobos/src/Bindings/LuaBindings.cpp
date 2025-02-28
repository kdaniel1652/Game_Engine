// Copyright 2024 Kenneth Villalobos

#include "../Components/AnimationComponent.h"
#include "../Game/Game.h"
#include <glm/glm.hpp>
#include "LuaBindings.h"
#include <SDL.h>
#include "../Systems/BoxCollisionSystem.h"

bool isActionActive(const std::string& action) {
  return Game::getInstance().controllerManager->getActionState(action);
}

Uint32 getTicks() {
  return SDL_GetTicks();
}

bool stringContains(const std::string& main, const std::string& contained) {
  return main.find(contained) != std::string::npos;
}

BoxColliderComponent& getBoxCollider(Entity& entity) {
  return entity.getComponent<BoxColliderComponent>();
}

bool hasHealth(Entity& entity) {
  return entity.hasComponent<HealthComponent>();
}

HealthComponent& getHealth(Entity& entity) {
  return entity.getComponent<HealthComponent>();
}

HitBoxComponent& getHitBox(Entity& entity) {
  return entity.getComponent<HitBoxComponent>();
}

RigidBodyComponent& getRigidBody(Entity& entity) {
  return entity.getComponent<RigidBodyComponent>();
}

SpriteComponent& getSprite(Entity& entity) {
  return entity.getComponent<SpriteComponent>();
}

TransformComponent& getTransform(Entity& entity) {
  return entity.getComponent<TransformComponent>();
}

void playSound(const std::string& entityType, const std::string& id) {
  if (Game::getInstance().soundManager->hasSound(entityType, id)) {
    Game::getInstance().soundManager->playSound(entityType, id);
  }
}

void changeAnimation(Entity& entity, const std::string& entityType,
  const std::string& id) {
  auto& animation = entity.getComponent<AnimationComponent>();
  auto& sprite = entity.getComponent<SpriteComponent>();

  AnimationData animationData;
  animationData = Game::getInstance().animationManager->getAnimationData(
    entityType, id);

  sprite.assetId = animationData.spriteLabel;
  sprite.width = animationData.width;
  sprite.height = animationData.height;
  sprite.srcRect.x = 0;
  sprite.srcRect.y = 0;
  sprite.srcRect.w = animationData.width;
  sprite.srcRect.h = animationData.width;

  animation.currentFrame = animationData.currentFrame;
  animation.frameSpeedRate = animationData.frameSpeedRate;
  animation.numberFrames = animationData.numberFrames;
  animation.startTime = SDL_GetTicks();
}

bool checkCollisionDirection(const Entity& a, const Entity& b,
  const std::string& direction) {
  CollisionDirection realDirection = CollisionDirection::up;

  if (direction == "down") {
    realDirection = CollisionDirection::down;
  } else if (direction == "right") {
    realDirection = CollisionDirection::right;
  } else if (direction == "left") {
    realDirection = CollisionDirection::left;
  }

  return BoxCollisionSystem::checkCollisionDirection(a, b, realDirection);
}

void changeScene(const std::string& sceneId) {
  Game::getInstance().loadScene(sceneId);
}
