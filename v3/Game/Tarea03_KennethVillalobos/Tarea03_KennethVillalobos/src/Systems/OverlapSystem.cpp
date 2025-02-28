// Copyright 2024 Kenneth Villalobos

#include "../Components/BoxColliderComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include "OverlapSystem.h"
#include "../Systems/BoxCollisionSystem.h"

OverlapSystem::OverlapSystem() {
}

void OverlapSystem::subscribeToCollideEvents(
  std::shared_ptr<EventManager>& eventManager) {
  eventManager->subscribeToEvent<OverlapSystem, CollisionEvent>(this,
    &OverlapSystem::onCollisionEvent);
}

void OverlapSystem::onCollisionEvent(CollisionEvent& event) {
  if (event.first.hasComponent<BoxColliderComponent>() &&
    event.second.hasComponent<BoxColliderComponent>()) {

    const bool firstDynamic =
      event.first.hasComponent<RigidBodyComponent>();
    const bool secondDynamic =
      event.second.hasComponent<RigidBodyComponent>();
    const bool bothDynamic = firstDynamic && secondDynamic;

    if ((firstDynamic || secondDynamic) && !bothDynamic) {
      if (event.first.hasComponent<RigidBodyComponent>() &&
        event.second.getTag() != "platform") {
        avoidOverlap(event.first, event.second);
      } else if (event.first.getTag() != "platform") {
        avoidOverlap(event.second, event.first);
      }
    }
  }
}

#include <iostream>

void OverlapSystem::avoidOverlap(Entity& eDynamic, Entity& eStatic) {
  auto& dynamicCollider = eDynamic.getComponent<BoxColliderComponent>();
  auto& dynamicTransform = eDynamic.getComponent<TransformComponent>();
  auto& dynamicRigidBody = eDynamic.getComponent<RigidBodyComponent>();

  auto& staticCollider = eStatic.getComponent<BoxColliderComponent>();
  auto& staticTransform = eStatic.getComponent<TransformComponent>();

  if (BoxCollisionSystem::checkCollisionDirection(eDynamic, eStatic,
    CollisionDirection::down)) {
    dynamicTransform.position.y =
      staticTransform.position.y +
      staticCollider.height -
      dynamicCollider.offset.y;
    dynamicRigidBody.velocity.y = 0.0f;
  } else if (BoxCollisionSystem::checkCollisionDirection(eDynamic, eStatic,
    CollisionDirection::up)) {
    dynamicTransform.position.y =
      staticTransform.position.y -
      dynamicCollider.height -
      dynamicCollider.offset.y;
    dynamicRigidBody.velocity.y = 0.0f;
    dynamicRigidBody.onGround = true;
  }

  if (BoxCollisionSystem::checkCollisionDirection(eDynamic, eStatic,
    CollisionDirection::left)) {
    dynamicTransform.position.x =
      staticTransform.position.x -
      dynamicCollider.width -
      dynamicCollider.offset.x;
    dynamicRigidBody.velocity.x = 0.0f;
  }
  else if (BoxCollisionSystem::checkCollisionDirection(eDynamic, eStatic,
    CollisionDirection::right)) {
    dynamicTransform.position.x =
      staticTransform.position.x +
      staticCollider.width -
      dynamicCollider.offset.x;
    dynamicRigidBody.velocity.x = 0.0f;
  }
}
