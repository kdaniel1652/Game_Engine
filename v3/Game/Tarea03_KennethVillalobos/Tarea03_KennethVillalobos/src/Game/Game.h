// Copyright 2024 Kenneth Villalobos

#ifndef GAME_H
#define GAME_H

#include "../AnimationManager/AnimationManager.h"
#include "../AssetStore/AssetStore.h"
#include "../ControllerManager/ControllerManager.h"
#include "../ECS/ECS.h"
#include "../EventManager/EventManager.h"
#include "../MusicManager/MusicManager.h"
#include "SceneLoader.h"
#include <SDL.h>
#include <sol/sol.hpp>
#include "../SoundManager/SoundManager.h"
#include <string>
#include <tinyxml2/tinyxml2.h>

class Game {
private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Rect camera = { 0, 0, 0, 0 };

  bool debugMode = false;
  bool isRunning = false;

  int msPreviousFrame = 0;
  int delayCicles = 0;

  std::shared_ptr<ECSManager> manager;
  std::shared_ptr<EventManager> eventManager;
  std::shared_ptr<MusicManager> musicManager;
  std::shared_ptr<SceneLoader> sceneLoader;

  sol::state lua;

  Game();
  ~Game();

  void init();
  void destroy();

  void setUp();
  void processInput();
  void update();
  void render();

public:
  std::shared_ptr<AssetStore> assetStore;
  std::shared_ptr<SoundManager> soundManager;
  std::shared_ptr<AnimationManager> animationManager;
  std::shared_ptr<ControllerManager> controllerManager;

  static size_t windowWidth;
  static size_t windowHeight;
  static size_t mapWidth;
  static size_t mapHeight;

  static Game& getInstance();

  void run();

  void loadScene(const std::string& sceneId);
};

#endif  // GAME_H

