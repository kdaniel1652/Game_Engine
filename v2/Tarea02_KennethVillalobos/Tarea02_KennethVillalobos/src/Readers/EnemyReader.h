// Copyright 2024, Kenneth Villalobos

#ifndef ENEMYREADER_H
#define ENEMYREADER_H

#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "../Components/AlliesComponent.h"
#include "../Components/BounceComponent.h"
#include "../Components/EnemyGeneratorComponent.h"
#include "../Components/PointsComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"

#include "../ECS/ECS.h"

#include "Reader.h"

#include "../Utils/common.h"

class EnemyReader : Reader {
protected:
  std::string label;
  int points;
  int minSpeed;
  int maxSpeed;
  int respawnTime;
  friend class Game;

protected:
  virtual std::istream& read(std::istream& is) override {
    return is >> this->label >> this->points >> this->minSpeed
      >> this->maxSpeed >> this->respawnTime;
  };

public:
  EnemyReader() = default;
  virtual ~EnemyReader() = default;

  Entity build(std::shared_ptr<ECSManager>& generalManager,
    const int width, const int height) {
    // ASUMPTIONS
    const int srcRectX = 0;
    const int srcRectY = 0;
    const int team = 2;
    const glm::vec2 scale(2.5, 2.5);
    const float bounceSpeedup = 1.1;

    Entity enemy = generalManager->createEntity();

    enemy.addComponent<TagComponent>(tags::ENEMY);

    enemy.addComponent<SpriteComponent>(label, width, height, srcRectX,
      srcRectY);

    enemy.addComponent<AlliesComponent>(team);

    enemy.addComponent<EnemyGeneratorComponent>(this->respawnTime,
      this->minSpeed, this->maxSpeed, scale);

    enemy.addComponent<PointsComponent>(this->points);

    enemy.addComponent<BounceComponent>(bounceSpeedup);

    return enemy;
  }
};

#endif  // ENEMYREADER_H
