// Copyright 2024 Kenneth Villalobos

#include <cstdio>
#include "Game.h"
#include <glm/glm.hpp>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <sstream>
#include "../Systems/AnimationSystem.h"
#include "../Systems/AttackSystem.h"
#include "../Systems/BoxCollisionSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CircleCollisionSystem.h"
#include "../Systems/CleaningSystem.h"
#include "../Systems/OverlapSystem.h"
#include "../Systems/RenderBoxColliderSystem.h"
#include "../Systems/RenderHitBoxSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Systems/ScriptSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/WeightForceSystem.h"
#include "../Util/common.h"

size_t Game::windowWidth;
size_t Game::windowHeight;
size_t Game::mapWidth;
size_t Game::mapHeight;

Game::Game() {
  this->animationManager = std::make_shared<AnimationManager>();
  this->assetStore = std::make_shared<AssetStore>();
  this->manager = std::make_shared<ECSManager>();
  this->eventManager = std::make_shared<EventManager>();
  this->controllerManager = std::make_shared<ControllerManager>();
  this->musicManager = std::make_shared<MusicManager>();
  this->soundManager = std::make_shared<SoundManager>();
  this->sceneLoader = std::make_shared<SceneLoader>();

  this->init();
}

Game::~Game() {
  this->destroy();
}

void Game::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "INIT ERROR: Could not initialize SDL" << std::endl;
    return;
  }
  if (TTF_Init() != 0) {
    std::cerr << "INIT ERROR: Could not initialize TTF" << std::endl;
    return;
  }
  Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 2048) != 0) {
    std::cerr << "INIT ERROR: Could not initialize Mixer" << std::endl;
    return;
  }

  Game::windowWidth = 480;
  Game::windowHeight = 320;

  this->window = SDL_CreateWindow(
    constants::GAME_NAME.c_str(),
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    Game::windowWidth,
    Game::windowHeight,
    SDL_WINDOW_SHOWN
  );
  if (!this->window) {
    std::cerr << "INIT ERROR: Could not create the window" << std::endl;
    return;
  }

  this->renderer = SDL_CreateRenderer(
    this->window,
    -1,
    0
  );
  if (!this->renderer) {
    std::cerr << "INIT ERROR: Could not create the renderer" << std::endl;
    return;
  }

  this->camera.x = 0;
  this->camera.y = 0;
  this->camera.w = Game::windowWidth;
  this->camera.h = Game::windowHeight;
}

void Game::destroy() {
  this->manager->destroy();

  this->lua = sol::state();

  if (this->renderer) {
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
  }
  
  if (this->window) {
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
  }

  SDL_Quit();
}

void Game::setUp() {
  this->manager->addSystem<AnimationSystem>();
  this->manager->addSystem<AttackSystem>();
  this->manager->addSystem<BoxCollisionSystem>();
  this->manager->addSystem<CameraMovementSystem>();
  this->manager->addSystem<CleaningSystem>();
  this->manager->addSystem<MovementSystem>();
  this->manager->addSystem<OverlapSystem>();
  this->manager->addSystem<RenderBoxColliderSystem>();
  this->manager->addSystem<RenderHitBoxSystem>();
  this->manager->addSystem<RenderSystem>();
  this->manager->addSystem<RenderTextSystem>();
  this->manager->addSystem<ScriptSystem>();
  this->manager->addSystem<WeightForceSystem>();
  
  this->manager->getSystem<ScriptSystem>().createLuaBindings(this->lua);

  this->lua.open_libraries(sol::lib::base);

  this->sceneLoader->loadGame("game.lua", this->lua, this->assetStore,
    this->renderer);
  this->loadScene("level_01");
}

void Game::processInput() {
  SDL_Event sdlEvent;

  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
    case SDL_QUIT:
      this->isRunning = false;
      break;

    case SDL_KEYDOWN:
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        this->isRunning = false;
      } else if (sdlEvent.key.keysym.sym == SDLK_b) {
        this->debugMode = !debugMode;
      } else if (this->controllerManager->isKeyMapped(
        sdlEvent.key.keysym.sym)) {
        std::string action = this->controllerManager->getAction(
          sdlEvent.key.keysym.sym);
        this->controllerManager->changeActionState(action, true);
      }
      break;

    case SDL_KEYUP:
      if (this->controllerManager->isKeyMapped(
        sdlEvent.key.keysym.sym)) {
        std::string action = this->controllerManager->getAction(
          sdlEvent.key.keysym.sym);
        this->controllerManager->changeActionState(action, false);
      }
      break;

    case SDL_MOUSEBUTTONDOWN:
      if (this->controllerManager->isButtonMapped(
        sdlEvent.button.button)) {
        std::string action = this->controllerManager->getAction(
          sdlEvent.button.button);
        this->controllerManager->changeActionState(action, true);
      }
    break;

    case SDL_MOUSEBUTTONUP:
      if (this->controllerManager->isButtonMapped(
        sdlEvent.button.button)) {
        std::string action = this->controllerManager->getAction(
          sdlEvent.button.button);
        this->controllerManager->changeActionState(action, false);
      }
    break;

    case SDL_MOUSEMOTION:
      this->controllerManager->changeMousePosition(sdlEvent.motion.x,
        sdlEvent.motion.y);
    break;
    }
  }
}

void Game::update() {
  int timeToWait = constants::MILISECS_PER_FRAME -
    (SDL_GetTicks() - this->msPreviousFrame);
  if (timeToWait > 0 && timeToWait <= constants::MILISECS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }
  float currentTime = SDL_GetTicks();
  float deltaTime = (currentTime - this->msPreviousFrame) / 1000.0f;
  this->msPreviousFrame = currentTime;

  this->eventManager->clear();
  this->manager->getSystem<OverlapSystem>().subscribeToCollideEvents(
    this->eventManager);

  if (this->delayCicles <= 0) {
    static float uprocessedTime = 0.0f;
    uprocessedTime += deltaTime;

    for (size_t update = 0; uprocessedTime >= constants::TIME_PER_STEP &&
      update < constants::MAX_STEPS; ++update) {
      this->manager->getSystem<WeightForceSystem>().update();
      this->manager->getSystem<ScriptSystem>().update(this->lua);
      this->manager->getSystem<MovementSystem>().update(
        constants::TIME_PER_STEP);
      this->manager->getSystem<BoxCollisionSystem>().update(
        this->eventManager, this->lua);
      this->manager->getSystem<AttackSystem>().update(this->lua);
      this->manager->getSystem<CleaningSystem>().update(this->lua);
      uprocessedTime -= constants::TIME_PER_STEP;
    }

    this->manager->getSystem<AnimationSystem>().update();
    this->manager->getSystem<CameraMovementSystem>().update(this->camera);
  } else {
    --this->delayCicles;
  }

  this->manager->getSystem<ScriptSystem>().awake(this->lua,
    this->manager->getEntitiesToBeAdded());
  this->manager->update();
}

void Game::render() {
  SDL_SetRenderDrawColor(this->renderer, 35, 35, 35, 255);
  SDL_RenderClear(this->renderer);
  this->manager->getSystem<RenderSystem>().update(this->renderer,
    this->assetStore, this->camera);

  if (this->debugMode) {
    this->manager->getSystem<RenderBoxColliderSystem>().update(this->renderer,
      this->camera);
    this->manager->getSystem<RenderHitBoxSystem>().update(this->renderer,
      this->camera);
  }

  this->manager->getSystem<RenderTextSystem>().update(this->renderer,
    this->assetStore, this->camera);

  SDL_RenderPresent(this->renderer);
}

Game& Game::getInstance() {
  static Game game;
  return game;
}

void Game::run() {
  this->setUp();
  this->isRunning = true;

  while (this->isRunning) {
    this->processInput();
    this->update();
    this->render();
  }

  this->destroy();
}

void Game::loadScene(const std::string& sceneId) {
  this->sceneLoader->loadScene(sceneId, this->lua,
  this->assetStore, this->controllerManager, this->soundManager,
  this->animationManager, this->manager, this->musicManager);

  ++this->delayCicles;
}
