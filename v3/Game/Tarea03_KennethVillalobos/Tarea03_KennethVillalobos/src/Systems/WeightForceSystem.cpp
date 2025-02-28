// Copyright 2024 Kenneth Villalobos

#include "../Components/RigidBodyComponent.h"
#include "WeightForceSystem.h"
#include "../Util/common.h"

WeightForceSystem::WeightForceSystem() {
  this->requireComponent<RigidBodyComponent>();
}

void WeightForceSystem::update() {
  for (auto entity : this->getSystemEntities()) {
    auto& rigidBody = entity.getComponent<RigidBodyComponent>();
    if (!rigidBody.isStatic) {
      rigidBody.sumForces.y += (constants::GRAVITY *
        constants::PIXELS_PER_METER * rigidBody.mass);
    }
  }
}
