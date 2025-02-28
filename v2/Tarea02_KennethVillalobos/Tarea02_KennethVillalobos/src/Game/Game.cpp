// Copyright 2024, Kenneth Villalobos

// General libraries
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <map>

// Components
#include "../Components/AlliesComponent.h"
#include "../Components/BounceComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/EnemyGeneratorComponent.h"
#include "../Components/GameOverComponent.h"
#include "../Components/GameStateComponent.h"
#include "../Components/KeyboardControllerComponent.h"
#include "../Components/LifesComponent.h"
#include "../Components/MouseControllerComponent.h"
#include "../Components/MusicComponent.h"
#include "../Components/PauseComponent.h"
#include "../Components/PointsComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RespawnComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ScoreComponent.h"
#include "../Components/SoundComponent.h"
#include "../Components/SpecialAttackComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../Components/TransformComponent.h"

// Events
#include "../Events/GamePausedEvent.h"
#include "../Events/GameUnPausedEvent.h"
#include "../Events/KeyboardEvent.h"
#include "../Events/MouseClickEvent.h"
#include "../Events/MouseMotionEvent.h"

// Game
#include "Game.h"

// Readers
#include "../Readers/BulletReader.h"
#include "../Readers/EnemyReader.h"
#include "../Readers/FontReader.h"
#include "../Readers/ImageReader.h"
#include "../Readers/PlayerReader.h"
#include "../Readers/WindowReader.h"

// Systems
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/EnemyGeneratorSystem.h"
#include "../Systems/EntityCleanerSystem.h"
#include "../Systems/GameStateSystem.h"
#include "../Systems/KeyboardControllerSystem.h"
#include "../Systems/MouseControllerSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/MusicSystem.h"
#include "../Systems/ProjectileEmitterSystem.h"
#include "../Systems/RenderGameOverSystem.h"
#include "../Systems/RenderPauseSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Systems/RespawnSystem.h"
#include "../Systems/ScoreSystem.h"
#include "../Systems/SoundSystem.h"
#include "../Systems/SpecialAttackSystem.h"

#include "../Utils/common.h"

void Game::init() {
  // SDL init
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error al inicializar SDL" << std::endl;
    return;
  }
  // TTF init
  if (TTF_Init() != 0) {
    std::cerr << "Error al inicializar TTF" << std::endl;
    return;
  }
  // Mixer init
  Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 2048) != 0) {
    std::cerr << "Error al inicializar Mixer" << std::endl;
    return;
  }

  // Window creation
  const std::string filename("./config.txt");
  std::ifstream inputFile(filename);
  std::string token("");
  if (!inputFile) {
    std::cerr << "Error al abrir el archivo de configuración" << std::endl;
    return;
  }
  inputFile >> token;
  if (token != "window") {
    std::cerr << "Error al crear la ventana" << std::endl;
    return;
  }

  WindowReader windowR;
  inputFile >> windowR;
  inputFile.close();

  this->windowWidth = windowR.width;
  this->windowHeight = windowR.height;
  this->window = windowR.build(constNames::GAME_NAME);

  // Renderer creation
  this->renderer = SDL_CreateRenderer(
    this->window,
    -1,
    0
  );
}

void Game::destroy() {
  SDL_DestroyRenderer(this->renderer);
  this->renderer = nullptr;

  SDL_DestroyWindow(this->window);
  this->window = nullptr;

  Mix_Quit();
  TTF_Quit();
  SDL_Quit();
}

void Game::setUp() {
  // System adding
  this->generalManager->addSystem<RenderSystem>();
  this->generalManager->addSystem<KeyboardControllerSystem>();
  this->generalManager->addSystem<MovementSystem>();
  this->generalManager->addSystem<CollisionSystem>();
  this->generalManager->addSystem<DamageSystem>();
  this->generalManager->addSystem<MouseControllerSystem>();
  this->generalManager->addSystem<ProjectileEmitterSystem>();
  this->generalManager->addSystem<EntityCleanerSystem>();
  this->generalManager->addSystem<EnemyGeneratorSystem>();
  this->generalManager->addSystem<RenderTextSystem>();
  this->generalManager->addSystem<ScoreSystem>();
  this->generalManager->addSystem<RespawnSystem>();
  this->generalManager->addSystem<RenderGameOverSystem>();
  this->generalManager->addSystem<GameStateSystem>();
  this->generalManager->addSystem<SpecialAttackSystem>();
  this->generalManager->addSystem<MusicSystem>();
  this->generalManager->addSystem<SoundSystem>();
  this->generalManager->addSystem<RenderPauseSystem>();

  // Initial texture loading
  this->assetStore->addTexture("background_img",
    "./assets/images/Background.png",
    this->renderer);
  this->assetStore->addTexture("pause_img",
    "./assets/images/Pause.png",
    this->renderer);
  this->assetStore->addSong("main_song",
    "./assets/songs/I_Like_The_Way_You_Kiss_Me.mp3");
  this->assetStore->addSong("gameOver_song",
    "./assets/songs/Saturday_In_The_Park.mp3");
  this->assetStore->addSound("death_sound_01",
    "./assets/sounds/death_01.wav");
  this->assetStore->addSound("enemy_killed_sound_01",
    "./assets/sounds/enemy_killed_01.wav");
  this->assetStore->addSound("enemy_killed_sound_02",
    "./assets/sounds/enemy_killed_02.wav");
  this->assetStore->addSound("enemy_killed_sound_03",
    "./assets/sounds/enemy_killed_03.wav");
  this->assetStore->addSound("pause_sound_01",
    "./assets/sounds/pause_01.wav");
  this->assetStore->addSound("shot_sound_01",
    "./assets/sounds/shot_01.wav");
  this->assetStore->addSound("special_attack_sound_01",
    "./assets/sounds/special_attack_01.wav");
  this->assetStore->addSound("special_attack_sound_02",
    "./assets/sounds/special_attack_02.wav");
  this->assetStore->addSound("revive_sound_01",
    "./assets/sounds/revive_01.wav");

  // Background creation
  Entity background = this->generalManager->createEntity();
  background.addComponent<TagComponent>(tags::BACKGROUND);
  background.addComponent<SpriteComponent>("background_img", 800, 600, 0, 0);
  background.addComponent<TransformComponent>(glm::vec2(0, 0),
    glm::vec2(1, 1), 0);

  // Pause entities creation
  Entity pauseBackfound = this->generalManager->createEntity();
  pauseBackfound.addComponent<TagComponent>(tags::PAUSE_BACKGROUND);
  pauseBackfound.addComponent<SpriteComponent>("pause_img", 800, 600, 0, 0);
  pauseBackfound.addComponent<PauseComponent>();

  // Song entities creation
  this->mainSong = this->generalManager->createEntity();
  this->mainSong.addComponent<TagComponent>(tags::songs::MAIN);
  this->mainSong.addComponent<MusicComponent>("main_song", 60, false);

  this->gameOverSong = this->generalManager->createEntity();
  this->gameOverSong.addComponent<TagComponent>(tags::songs::GAME_OVER);
  this->gameOverSong.addComponent<MusicComponent>("gameOver_song", 60, false);
  
  // Sound entities creation
  Entity death_sound = this->generalManager->createEntity();
  death_sound.addComponent<TagComponent>(tags::sounds::PLAYER_KILLED);
  std::vector<std::string> labels;
  labels.push_back("death_sound_01");
  std::vector<int> volumnes;
  volumnes.push_back(100);
  death_sound.addComponent<SoundComponent>(labels,
    volumnes, 0);

  Entity enemy_killed_sound = this->generalManager->createEntity();
  enemy_killed_sound.addComponent<TagComponent>(tags::sounds::ENEMY_KILLED);
  labels.clear();
  labels.push_back("enemy_killed_sound_01");
  labels.push_back("enemy_killed_sound_02");
  labels.push_back("enemy_killed_sound_03");
  volumnes.clear();
  volumnes.push_back(100);
  volumnes.push_back(100);
  volumnes.push_back(100);
  enemy_killed_sound.addComponent<SoundComponent>(labels,
    volumnes, 0);

  Entity pause_sound = this->generalManager->createEntity();
  pause_sound.addComponent<TagComponent>(tags::sounds::PAUSE);
  labels.clear();
  labels.push_back("pause_sound_01");
  volumnes.clear();
  volumnes.push_back(100);
  pause_sound.addComponent<SoundComponent>(labels,
    volumnes, 0);

  Entity shot_sound = this->generalManager->createEntity();
  shot_sound.addComponent<TagComponent>(
    tags::sounds::PROJECTILE_SHOOTED);
  labels.clear();
  labels.push_back("shot_sound_01");
  volumnes.clear();
  volumnes.push_back(100);
  shot_sound.addComponent<SoundComponent>(labels,
    volumnes, 0);

  Entity special_attack_sound = this->generalManager->createEntity();
  special_attack_sound.addComponent<TagComponent>(
    tags::sounds::SPECIAL_ATTACK);
  labels.clear();
  labels.push_back("special_attack_sound_01");
  labels.push_back("special_attack_sound_02");
  volumnes.clear();
  volumnes.push_back(100);
  volumnes.push_back(100);
  special_attack_sound.addComponent<SoundComponent>(labels,
    volumnes, 0);

  Entity revive_sound = this->generalManager->createEntity();
  revive_sound.addComponent<TagComponent>(tags::sounds::REVIVE);
  labels.clear();
  labels.push_back("revive_sound_01");
  volumnes.clear();
  volumnes.push_back(100);
  revive_sound.addComponent<SoundComponent>(labels,
    volumnes, 0);

  // Config reading
  if (!this->readConfig()) {
    this->gameState.getComponent<GameStateComponent>().failed = true;
    std::cerr << "Error al leer el archivo de configuración" << std::endl;
  }
}

bool Game::readConfig() {
  const std::string filename("./config.txt");
  std::ifstream inputFile(filename);

  std::string token;
  bool success = true;

  // Readers
  FontReader fontR;
  ImageReader imageR;
  PlayerReader playerR;
  BulletReader bulletR;
  EnemyReader enemyR;

  Entity player;

  std::map<std::string, int> fontSizes;
  std::map<std::string, std::pair<int, int>> imageSizes;

  while (inputFile >> token && success) {
    if (token.compare("asset") == 0) {
      if (inputFile >> token) {
        if (token.compare("image") == 0) {
          inputFile >> imageR;
          imageSizes[imageR.label] =
            std::pair<int, int>(imageR.width, imageR.height);
          imageR.build(this->assetStore, this->renderer);

        } else if (token.compare("font") == 0) {
          inputFile >> fontR;
          fontSizes[fontR.label] = fontR.size;
          fontR.build(this->assetStore);

        } else {
          success = false;
        }

      } else {
        success = false;
      }

    } else if (token.compare("enemy") == 0) {
      inputFile >> enemyR;
      if (imageSizes.find(enemyR.label) != imageSizes.end()) {
        enemyR.build(this->generalManager, imageSizes[enemyR.label].first,
          imageSizes[enemyR.label].second);

      } else {
        success = false;
      }
      
    } else if (token.compare("player") == 0) {
      inputFile >> playerR;
      player = playerR.build(this->generalManager,
        imageSizes[playerR.label].first,
        imageSizes[playerR.label].second,
        this->windowWidth,
        this->windowHeight);

    } else if (token.compare("bullet") == 0) {
      inputFile >> bulletR;

    } else if (token.compare("window") == 0) {
      int x;
      inputFile >> x;
      inputFile >> x;

    }
    else {
      success = false;
    }
  }
  inputFile.close();

  if (player.isValid() &&
    imageSizes.find(bulletR.label) != imageSizes.end()) {
    bulletR.build(player, imageSizes[bulletR.label].first,
      imageSizes[bulletR.label].second);

    // ASUNPTION
    const std::string forceFieldLabel("forcefield_img");

    if (imageSizes.find(forceFieldLabel) != imageSizes.end()) {
      Entity forceField = this->generalManager->createEntity();
      forceField.addComponent<TagComponent>(tags::FORCEFIELD);
      forceField.addComponent<SpriteComponent>(forceFieldLabel,
        imageSizes[forceFieldLabel].first,
        imageSizes[forceFieldLabel].second);

      player.getComponent<RespawnComponent>().forceField = forceField;
    }

  } else {
    success = false;
  }

  if (!fontSizes.empty()) {
    // ASUMPTIONS
    const std::string scoreFontLabel = (fontSizes.find("score_font") !=
      fontSizes.end()) ? "score_font" : (*fontSizes.begin()).first;
    const std::string scoreStartingText = "000000";
    const SDL_Color scoreColor = { 92, 16, 2, 255 };
    const glm::vec2 scorePosition(10, 5);
    const glm::vec2 scoreScale(1, 1);
    const float scoreRotation = 0.0f;
    const int scoreStartingPoints = 0;

    Entity score = this->generalManager->createEntity();
    score.addComponent<TagComponent>(tags::SCORE);
    score.addComponent<TextLabelComponent>(scoreFontLabel, scoreStartingText,
      scoreColor.r, scoreColor.g, scoreColor.b);
    score.addComponent<TransformComponent>(scorePosition, scoreScale,
      scoreRotation);
    score.addComponent<ScoreComponent>(scoreStartingPoints);

    // ASUMPTIONS
    const std::string gameOverFontLabel = (fontSizes.find("gameOver_font") !=
      fontSizes.end()) ? "gameOver_font" : (*fontSizes.rbegin()).first;
    const SDL_Color gameOverColor = { 92, 16, 2, 255 };
    const std::string gameOverText = "Game Over";

    Entity gameOver = this->generalManager->createEntity();
    gameOver.addComponent<TagComponent>(tags::GAME_OVER_TEXT);
    gameOver.addComponent<TextLabelComponent>(gameOverFontLabel,
      gameOverText, gameOverColor.r, gameOverColor.g,
      gameOverColor.b);
    gameOver.addComponent<GameOverComponent>();

    // ASUMPTIONS
    const std::string pauseFont = (fontSizes.find("pause_font") !=
      fontSizes.end()) ? "pause_font" : (*fontSizes.begin()).first;
    const SDL_Color pauseColor = { 255, 255, 255, 255 };
    const std::string pauseText = "Paused";

    Entity pause = this->generalManager->createEntity();
    pause.addComponent<TagComponent>(tags::PAUSE_TEXT);
    pause.addComponent<TextLabelComponent>(pauseFont, pauseText,
      pauseColor.r, pauseColor.g, pauseColor.b);
    pause.addComponent<PauseComponent>();

  } else {
    success = false;
  }

  return success;
}

void Game::processInput() {
  // Process all SDL events
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
      // X On window
    case SDL_QUIT:
      this->gameState.getComponent<GameStateComponent>().isRunning = false;
      break;

      // A key was pressed
    case SDL_KEYDOWN:
      // ESC
      if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
        this->gameState.getComponent<GameStateComponent>().isRunning = false;
      }
      if (sdlEvent.key.keysym.sym == SDLK_p) {
        auto& state = this->gameState.getComponent<GameStateComponent>();
        state.isPaused = !state.isPaused;
        this->msPreviousFrame = SDL_GetTicks();

        if (state.isPaused) {
          this->eventManager->emitEvent<GamePausedEvent>();
        } else {
          this->eventManager->emitEvent<GameUnPausedEvent>();
        }
      }
      this->eventManager->emitEvent<KeyboardEvent>(
        true, sdlEvent.key.keysym.sym);
      break;

      // A key was released
    case SDL_KEYUP:
      this->eventManager->emitEvent<KeyboardEvent>(
        false, sdlEvent.key.keysym.sym);
      break;

      // The mouse moved
    case SDL_MOUSEMOTION:
    {
      int x = 0;
      int y = 0;
      SDL_GetMouseState(&x, &y);
      this->eventManager->emitEvent<MouseMotionEvent>(glm::vec2(x, y));
    }
    break;

    // The mouse moved
    case SDL_MOUSEBUTTONDOWN:
      this->eventManager->emitEvent<MouseClickEvent>(true,
        sdlEvent.button.button, this->eventManager);
      break;

      // The mouse moved
    case SDL_MOUSEBUTTONUP:
      this->eventManager->emitEvent<MouseClickEvent>(false,
        sdlEvent.button.button, this->eventManager);
      break;
    }
  }
}

void Game::update() {
  // Clean subscriptions
  this->eventManager->clear();

  // Add subscriptions
  this->generalManager->getSystem<KeyboardControllerSystem>(
  ).subscribeToGameUnPausedEvents(this->eventManager);
  this->generalManager->getSystem<MusicSystem>(
  ).subscribeToGameUnPausedEvents(this->eventManager);
  this->generalManager->getSystem<SoundSystem>(
  ).subscribeToGamePausedEvents(this->eventManager);
  this->generalManager->getSystem<SoundSystem>(
  ).subscribeToGameUnPausedEvents(this->eventManager);
  this->generalManager->getSystem<RenderPauseSystem>(
  ).subscribeToGamePausedEvents(this->eventManager);

  if (!this->gameState.getComponent<GameStateComponent>().isPaused) {
    // Keep stable framerate
    int timeToWait = MILISECS_PER_FRAME -
      (SDL_GetTicks() - this->msPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILISECS_PER_FRAME) {
      SDL_Delay(timeToWait);
    }
    const int msSinceLastUpdate = SDL_GetTicks() - this->msPreviousFrame;
    const double deltaTime = msSinceLastUpdate / 1000.0;
    this->msPreviousFrame = SDL_GetTicks();

    // Add subscriptions
    this->generalManager->getSystem<KeyboardControllerSystem>(
    ).subscribeToKeyboardEvents(this->eventManager);
    this->generalManager->getSystem<DamageSystem>(
    ).subscribeToCollisionEvents(this->eventManager);
    this->generalManager->getSystem<MouseControllerSystem>(
    ).subscribeToMouseMotionEvents(this->eventManager);
    this->generalManager->getSystem<ProjectileEmitterSystem>(
    ).subscribeToMouseClickEvents(this->eventManager);
    this->generalManager->getSystem<EntityCleanerSystem>(
    ).subscribeToOutOfBoundsEvents(this->eventManager);
    this->generalManager->getSystem<ScoreSystem>(
    ).subscribeToEnemyKilledEvents(this->eventManager);
    this->generalManager->getSystem<RespawnSystem>(
    ).subscribeToEntityDefeatedEvents(this->eventManager);
    this->generalManager->getSystem<GameStateSystem>(
    ).subscribeToGameOverEvents(this->eventManager);
    this->generalManager->getSystem<SpecialAttackSystem>(
    ).subscribeToMouseClickEvents(this->eventManager);
    this->generalManager->getSystem<MusicSystem>(
    ).subscribeToGamePausedEvents(this->eventManager);
    this->generalManager->getSystem<SoundSystem>(
    ).subscribeToEnemyKilledEvents(this->eventManager);
    this->generalManager->getSystem<SoundSystem>(
    ).subscribeToEntityDefeatedEvents(this->eventManager);
    this->generalManager->getSystem<SoundSystem>(
    ).subscribeToEntityRespawnedEvents(this->eventManager);
    this->generalManager->getSystem<SoundSystem>(
    ).subscribeToProjectileShootedEvents(this->eventManager);
    this->generalManager->getSystem<SoundSystem>(
    ).subscribeToSpecialAttackActivatedEvents(this->eventManager);

    // Updates
    this->generalManager->getSystem<MovementSystem>().update(this->eventManager,
      deltaTime, this->windowWidth, this->windowHeight);
    this->generalManager->getSystem<CollisionSystem>().update(this->eventManager);
    if (!this->gameState.getComponent<GameStateComponent>().gameOver) {
      this->generalManager->getSystem<EnemyGeneratorSystem>().update(
        this->windowWidth, this->windowHeight, msSinceLastUpdate);
    }
    this->generalManager->getSystem<RespawnSystem>().update(this->eventManager,
      msSinceLastUpdate);
    this->generalManager->getSystem<SpecialAttackSystem>().update(
      msSinceLastUpdate);
    this->generalManager->update();
  }
}

void Game::render() {
  this->generalManager->getSystem<SoundSystem>().update(this->assetStore);
  if (!this->gameState.getComponent<GameStateComponent>().isPaused) {
    // Clear the window
    SDL_SetRenderDrawColor(this->renderer, 100, 100, 100, 255);
    SDL_RenderClear(this->renderer);

    // Use the render systems
    this->generalManager->getSystem<RenderSystem>().update(this->renderer,
      this->assetStore);
    this->generalManager->getSystem<RenderTextSystem>().update(this->renderer,
      this->assetStore);
    if (this->gameState.getComponent<GameStateComponent>().gameOver) {
      this->generalManager->getSystem<RenderGameOverSystem>().update(
        this->renderer, this->assetStore, this->windowWidth,
        this->windowHeight);
      this->generalManager->getSystem<MusicSystem>().update(this->gameOverSong,
        this->assetStore);
    }
    else {

      this->generalManager->getSystem<MusicSystem>().update(this->mainSong,
        this->assetStore);
    }

  }
  else {
    this->generalManager->getSystem<RenderPauseSystem>().update(
      this->renderer, this->assetStore, this->windowWidth,
      this->windowHeight);
  }

  // Show the rendered items
  SDL_RenderPresent(this->renderer);
}

Game::Game() {
  // Create the shared pointer for the managers
  this->assetStore = std::make_shared<AssetStore>();
  this->generalManager = std::make_shared<ECSManager>();
  this->eventManager = std::make_shared<EventManager>();

  // Create a game state
  this->gameState = this->generalManager->createEntity();
  this->gameState.addComponent<TagComponent>(tags::GAME_STATE);
  this->gameState.addComponent<GameStateComponent>(false, false, true, false);

  // Initialize other data
  this->init();
}

Game::~Game() {
  this->destroy();
}

void Game::run() {
  this->setUp();
  this->gameState.getComponent<GameStateComponent>().isRunning =
    !this->gameState.getComponent<GameStateComponent>().failed;

  while (this->gameState.getComponent<GameStateComponent>().isRunning) {
    this->processInput();
    this->update();
    this->render();
  }
}
