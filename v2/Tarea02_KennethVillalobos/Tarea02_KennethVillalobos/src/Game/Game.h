// Copyright 2024, Kenneth Villalobos

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../Utils/RandomGenerator.h"

const int FPS = 60;
const int MILISECS_PER_FRAME = 1000 / FPS;

class Game {
private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  size_t windowWidth = 0;
  size_t windowHeight = 0;
  int msPreviousFrame = 0;

  std::shared_ptr<AssetStore> assetStore;
  std::shared_ptr<ECSManager> generalManager;
  std::shared_ptr<EventManager> eventManager;

  Entity gameState;

  Entity mainSong;
  Entity gameOverSong;

  void init();
  void destroy();

  void setUp();
  bool readConfig();
  void processInput();
  void update();
  void render();

public:
  Game();
  ~Game();

  void run();
};

#endif  // GAME_H
