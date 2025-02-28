// Copyright 2024, Kenneth Villalobos

#include "../Components/AlliesComponent.h"
#include "../Components/BounceComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/EnemyGeneratorComponent.h"
#include "../Components/PointsComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"
#include "EnemyGeneratorSystem.h"

EnemyGeneratorSystem::EnemyGeneratorSystem() {
  this->requireComponent<EnemyGeneratorComponent>();
  this->requireComponent<SpriteComponent>();
  this->requireComponent<AlliesComponent>();
  this->requireComponent<BounceComponent>();
  this->requireComponent<TagComponent>();
}

void EnemyGeneratorSystem::update(const int xLimit,
  const int yLimit, const int msSinceLastUpdate) {
  for (auto entity : this->getSystemEntities()) {
    auto& generator = entity.getComponent<EnemyGeneratorComponent>();
    if (generator.msSinceGeneration >= generator.msToGenerate) {
      auto& sprite = entity.getComponent<SpriteComponent>();
      auto& allies = entity.getComponent<AlliesComponent>();
      auto& points = entity.getComponent<PointsComponent>();
      auto& tag = entity.getComponent<TagComponent>();
      auto& bounce = entity.getComponent<BounceComponent>();

      Entity spawn = entity.createAnotherEntity();
      spawn.addComponent<TagComponent>(tag.tag);
      spawn.addComponent<SpriteComponent>(
        sprite.assetId,
        sprite.width,
        sprite.height,
        sprite.srcRect.x,
        sprite.srcRect.y
      );

      RandomGenerator xGen(0, xLimit - sprite.width);
      RandomGenerator yGen(0, yLimit - sprite.height);

      glm::vec2 randPos(static_cast<int>(xGen.generate()),
        static_cast<int>(yGen.generate()));

      spawn.addComponent<TransformComponent>(randPos,
        generator.enemyScale, 0);

      RandomGenerator randSpeed(static_cast<float>(generator.minSpeed),
        static_cast<float>(generator.maxSpeed));
      spawn.addComponent<RigidBodyComponent>(
        glm::vec2(randSpeed.generate(), randSpeed.generate()),
        0, true);

      spawn.addComponent<CircleColliderComponent>(
        std::min(sprite.width * generator.enemyScale.x,
                 sprite.height * generator.enemyScale.y) * 0.5f);
      spawn.addComponent<AlliesComponent>(allies.team);
      spawn.addComponent<BounceComponent>(bounce.bounceSpeedup);
      spawn.addComponent<PointsComponent>(points.points);

      generator.msSinceGeneration = 0;
    }
    generator.msSinceGeneration += msSinceLastUpdate;
  }
}