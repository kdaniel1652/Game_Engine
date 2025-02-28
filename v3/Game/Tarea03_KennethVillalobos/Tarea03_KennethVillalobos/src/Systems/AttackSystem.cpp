// Copyright 2024 Kenneth Villalobos

#include "AttackSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/TransformComponent.h"
#include "../Systems/BoxCollisionSystem.h"

AttackSystem::AttackSystem() {
  this->requireComponent<TransformComponent>();
}

void AttackSystem::update(sol::state& lua) {
  auto entities = this->getSystemEntities();
  for (auto i = entities.begin(); i != entities.end(); ++i) {
    auto a = *i;

    if (a.hasComponent<HitBoxComponent>()) {
      const auto& aHitbox = a.getComponent<HitBoxComponent>();
      if (aHitbox.active) {
        const auto& aTransform = a.getComponent<TransformComponent>();

        for (auto j = entities.begin(); j != entities.end(); ++j) {
          auto b = *j;

          if (a != b && b.hasComponent<BoxColliderComponent>()) {
            const auto& bCollider = b.getComponent<BoxColliderComponent>();
            const auto& bTransform = b.getComponent<TransformComponent>();

            const bool collision = BoxCollisionSystem::checkAABBCollision(
              aTransform.position + aHitbox.offset,
              static_cast<float>(aHitbox.width),
              static_cast<float>(aHitbox.height),
              bTransform.position + bCollider.offset,
              static_cast<float>(bCollider.width),
              static_cast<float>(bCollider.height)
            );

            if (collision) {
              if (a.hasComponent<ScriptComponent>()) {
                const auto& scriptA = a.getComponent<ScriptComponent>();
                if (scriptA.onHit != sol::nil) {
                  lua["this"] = a;
                  scriptA.onHit(b);
                }
              }

              else if (b.hasComponent<ScriptComponent>()) {
                const auto& scriptB = b.getComponent<ScriptComponent>();
                if (scriptB.onHit != sol::nil) {
                  lua["this"] = b;
                  scriptB.onHit(a);
                }
              }
            }
          }
        }
      }
    }
  }
}