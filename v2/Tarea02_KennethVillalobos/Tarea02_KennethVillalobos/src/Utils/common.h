// Copyright 2024, Kenneth Villalobos

#ifndef COMMON_H
#define COMMON_H

#include <string>
namespace constNames {
  static const std::string GAME_NAME("Tank Fighters");
  static const std::string CONFIG_FILE("./config.txt");
}

namespace tags {
  static const std::string BACKGROUND("Background");
  static const std::string PAUSE_BACKGROUND("Pause Background");
  static const std::string PAUSE_TEXT("Pause Text");
  static const std::string GAME_OVER_TEXT("Game Over Text");

  namespace songs {
    static const std::string MAIN("Main Song");
    static const std::string GAME_OVER("Game Over Song");
  }

  namespace sounds {
    static const std::string ENEMY_KILLED("Enemy Killed Sound");
    static const std::string PLAYER_KILLED("Player Killed Sound");
    static const std::string REVIVE("Player Revived Sound");
    static const std::string PAUSE("Pause Sound");
    static const std::string PROJECTILE_SHOOTED("Projectile Shoot Sound");
    static const std::string SPECIAL_ATTACK("Special Attack Sound");
  }

  static const std::string PLAYER("Player");
  static const std::string ENEMY("Enemy");
  static const std::string BULLET("Bullet");
  static const std::string CLONE("Clone");
  static const std::string FORCEFIELD("Forcefield");

  static const std::string SCORE("Score");

  static const std::string GAME_STATE("Game State");
}

static const int MS_GRACE_TIME = 2000;

#endif  // COMMON_H