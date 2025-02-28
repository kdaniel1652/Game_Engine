// Copyright 2024, Kenneth Villalobos

#ifndef PLAYERREADER_H
#define PLAYERREADER_H

#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "../Components/AlliesComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/LifesComponent.h"
#include "../Components/MouseControllerComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpecialAttackComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"

#include "../ECS/ECS.h"

#include "Reader.h"

#include "../Utils/common.h"

class PlayerReader : Reader {
protected:
  std::string label;
  int lifes;
  int speed;
  friend class Game;

protected:
  virtual std::istream& read(std::istream& is) override {
    return is >> this->label >> this->lifes >> this->speed;
  };

public:
  PlayerReader() = default;
  virtual ~PlayerReader() = default;

  Entity build(std::shared_ptr<ECSManager>& generalManager,
    const int width, const int height, const int windowWidth,
    const int windowHeight) {
    // ASUMPTIONS
    const int srcRectX = 0;
    const int srcRectY = 0;
    const glm::vec2 scale(0.5, 0.5);
    const int rotation = 0;
    const glm::vec2 velocity(0.0f, 0.0f);
    const int team = 1;
    const int respawnTime = 3000;

    Entity player = generalManager->createEntity();

    player.addComponent<TagComponent>(tags::PLAYER);

    player.addComponent<SpriteComponent>(this->label, width, height,
      srcRectX, srcRectY);

    player.addComponent<TransformComponent>(
      glm::vec2(windowWidth / 2 - width / 2, windowHeight / 2 - height / 2),
      scale, rotation);

    player.addComponent<RigidBodyComponent>(velocity, speed, true);

    player.addComponent<CircleColliderComponent>(
      std::min(width * scale.x, height * scale.y) * 0.8f);

    player.addComponent<KeyboardControllerComponent>();

    player.addComponent<MouseControllerComponent>();

    player.addComponent<AlliesComponent>(team);

    player.addComponent<LifesComponent>(this->lifes);

    player.addComponent<RespawnComponent>(respawnTime,
      glm::vec2(windowWidth / 2 - width / 2, windowHeight / 2 - height / 2));

    return player;
  }
};

#endif  // PLAYERREADER_H
