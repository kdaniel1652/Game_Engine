// Copyright 2024, Kenneth Villalobos

#include <fstream>
#include <iostream>

#include "Game.h"
#include <SDL_ttf.h>

void gameDev::Game::init() {
  // Initiliaze SDL and TTF
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error al inicializar el SDL" << std::endl;
    return;
  }
  if (TTF_Init() != 0) {
    std::cerr << "Error al inicializar el TTF" << std::endl;
    return;
  }

  // Read the config file
  this->readConfig();
  // Initialize the window
  if (!this->window.init()) {
    std::cerr << "Error al inicializar la ventana" << std::endl;
    return;
  }
  // Initialize the font
  if (!this->font.init()) {
    std::cerr << "Error al inicializar la fuente" << std::endl;
    return;
  }
  // Initialize the renderer
  this->renderer = SDL_CreateRenderer(this->window.window, -1, 0);
  if (this->renderer == nullptr) {
    std::cerr << "Error al inicializar el renderizador" << std::endl;
    return;
  }

  // Initialize all the entities and their labels
  for (size_t entity = 0; entity < this->entities.size(); ++entity) {
    if (!this->entities[entity].init(this->renderer)) {
      std::cerr << "Error al inicializar las entidades" << std::endl;
      return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(this->font.font,
      this->entities[entity].label.c_str(),
      { static_cast<unsigned char>(this->font.color.r),
        static_cast<unsigned char>(this->font.color.g),
        static_cast<unsigned char>(this->font.color.b), 255});

    this->entityLabels[entity].texture =
      SDL_CreateTextureFromSurface(this->renderer, surface);
    this->entityLabels[entity].width = surface->w;
    this->entityLabels[entity].height = surface->h;

    SDL_FreeSurface(surface);
  }
}

bool gameDev::Game::readConfig() {
  // Open the file
  const std::string filename("config.txt");
  std::ifstream inputFile(filename);

  // Cicle reading tokens to know
  // which type of class is comming
  std::string token;
  bool success = true;
  while (inputFile >> token && success) {
    // Entities first since they will usually be more
    if (token.compare("entity") == 0) {
      this->entities.emplace_back();
      this->entityLabels.push_back({ nullptr, 0, 0 });
      inputFile >> this->entities.back();

    // In case of multiple fonts, keeps the last
    } else if (token.compare("font") == 0) {
      inputFile >> this->font;

    // In case of multiple windows, keeps the last
    } else if (token.compare("window") == 0) {
      inputFile >> this->window;

    // If it reads something else, something went wrong
    } else {
      success = false;
    }
  }

  return success;
}

void gameDev::Game::destroy() {
  // Destroy all the entities
  for (auto& entity : this->entities) {
    entity.destroy();
  }
  // Clear the vectors for good messure
  this->entities.clear();
  this->entityLabels.clear();

  // Destroy the renderer
  SDL_DestroyRenderer(this->renderer);
  this->renderer = nullptr;

  // Destroy the fnot
  this->font.destroy();
  // Destroy the window
  this->window.destroy();

  // Quit both TTF and SDL
  TTF_Quit();
  SDL_Quit();
}

void gameDev::Game::processInput() {
  // Process all events from the poll
  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    switch (sdlEvent.type) {
      // Close button on the window was pressed
      case SDL_QUIT:
        this->isRunning = false;
      break;

      // A key was pressed
      case SDL_KEYDOWN:
        // If the key was esc
        if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
          this->isRunning = false;
        }
        // If the key was "t"
        if (sdlEvent.key.keysym.sym == SDLK_t) {
          this->isPaused = !this->isPaused;
          // Update the variable to prevent the
          // delta time from being affected
          this->msPreviousFrame = SDL_GetTicks();
        }
      break;
    }
  }
}

void gameDev::Game::update() {
  // Calculate the time it should delay to maintain the frame rate
  int timeToWait = gameDev::MILISECS_PER_FRAME -
    (SDL_GetTicks() - this->msPreviousFrame);

  // Delay if it has to
  if (timeToWait > 0 && timeToWait <= gameDev::MILISECS_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  // Calculate the time passed to use on the movement
  double deltaTime = (SDL_GetTicks() - this->msPreviousFrame) / 1000.0;
  // Update the variable
  this->msPreviousFrame = SDL_GetTicks();

  // Update the position of all the entities
  for (auto& entity : this->entities) {
    entity.pos.x += entity.vel.x * deltaTime;
    entity.pos.y += entity.vel.y * deltaTime;

    // In case they touched a wall, update their velocity too
    // to make them bounce
    // If they touch the right or left walls and their speed is not 0
    if (entity.vel.x != 0 &&
      ((entity.pos.x + entity.width) >= this->window.width ||
      entity.pos.x < 0)) {
      entity.vel.x *= -2;
    }

    // If they touche the top or bottom walls and their speed is not 0
    if (entity.vel.y != 0 &&
      ((entity.pos.y + entity.height) >= this->window.height ||
      entity.pos.y < 0)) {
      entity.vel.y *= -2;
    }
  }
}

void gameDev::Game::render() {
  // Set the color to the background
  SDL_SetRenderDrawColor(this->renderer, this->window.color.r,
    this->window.color.g, this->window.color.b, 255);
  // Clean the screen (paint the background)
  SDL_RenderClear(this->renderer);

  // Render all the entities and their labels
  for (size_t entity = 0; entity < this->entities.size(); ++entity) {
    SDL_Rect entityDestRect = {
      this->entities[entity].pos.x,
      this->entities[entity].pos.y,
      this->entities[entity].width,
      this->entities[entity].height };

    // The position of the labels must be calculated to ensure it is
    // centered
    SDL_Rect labelDestRect = {
      this->entities[entity].pos.x +
      (static_cast<double>((this->entities[entity].width) - 
       static_cast<double>(this->entityLabels[entity].width)) / 2.0),
      this->entities[entity].pos.y +
      (static_cast<double>((this->entities[entity].height) -
       static_cast<double>(this->entityLabels[entity].height)) / 2.0),
      this->entityLabels[entity].width,
      this->entityLabels[entity].height };

    SDL_RenderCopyEx(this->renderer, this->entities[entity].texture, NULL,
      &entityDestRect, this->entities[entity].angle, NULL, SDL_FLIP_NONE);

    SDL_RenderCopyEx(this->renderer, this->entityLabels[entity].texture, NULL,
      &labelDestRect, this->entities[entity].angle, NULL, SDL_FLIP_NONE);
  }

  SDL_RenderPresent(this->renderer);
}

gameDev::Game::Game() {
  this->init();
}

gameDev::Game::~Game() {
  this->destroy();
}

void gameDev::Game::run() {
  // Update the variable to ensure the game runs
  this->isRunning = true;

  while (this->isRunning) {
    this->processInput();
    // Id the game is paused, there
    // is no need to update nor render
    if (!this->isPaused) {
      this->update();
      this->render();
    }
  }
}
