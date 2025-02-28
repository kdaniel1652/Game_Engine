// Copyright 2024 Kenneth Villalobos

#ifndef LUABINDINGS_H
#define LUABINDINGS_H

#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../ECS/ECS.h"
#include <string>

bool isActionActive(const std::string& action);

Uint32 getTicks();

bool stringContains(const std::string& main, const std::string& contained);

BoxColliderComponent& getBoxCollider(Entity& entity);

bool hasHealth(Entity& entity);
HealthComponent& getHealth(Entity& entity);

HitBoxComponent& getHitBox(Entity& entity);

RigidBodyComponent& getRigidBody(Entity& entity);

SpriteComponent& getSprite(Entity& entity);

TransformComponent& getTransform(Entity& entity);

void playSound(const std::string& entityType,
  const std::string& id);

void changeAnimation(Entity& entity, const std::string& entityType,
  const std::string& id);

bool checkCollisionDirection(const Entity& a, const Entity& b,
  const std::string& direction);

void changeScene(const std::string& sceneId);

#endif  // LUABINDINGS_H
