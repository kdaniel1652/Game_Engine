// Copyright 2024, Kenneth Villalobos

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>

#include "../window/Window.h"
#include "../font/Font.h"
#include "../entity/Entity.h"
#include "../label/Label.h"

/**
  * @namespace Namespace to store all the classes and structs implemented on
  * the project
  */
namespace gameDev {
  /**
    * @brief Constant for the desired FPS to standarize the game to
    */
  const int FPS = 60;
  /**
    * @brief Constant to know the miliseconds per frama. Depends on a@ FPS
    * @see FPS
    */
  const int MILISECS_PER_FRAME = 1000 / FPS;

  /**
    * @class Class to act as the controller of the program
    */
  class Game {
  // Attributes
  private:
    // Window class
    Window window = Window();
    // Renderer
    SDL_Renderer* renderer = nullptr;

    // Font class
    Font font = Font();
    // Vectors to store all the entitites and their labels
    std::vector<Entity> entities = std::vector<Entity>();
    std::vector<Label> entityLabels = std::vector<Label>();

    // Bool to know if the game is running
    bool isRunning = false;
    // Bool to know if the game is paused (but still running)
    bool isPaused = false;
    // int to help maintain a somewhat stable frame rate
    int msPreviousFrame = 0;

    /**
     * @brief Initializes the controller allocating the necessary memory
     * @remark This method is automatically called upon construction
     */
    void init();
    /**
     * @brief Reads all the data from the config.txt file
     * @bool Boolean indicating if the read was successfull
     */
    bool readConfig();
    /**
     * @brief Frees all the allocated memory
     * @remark This method is automatically called upon destruction
     */
    void destroy();

    /**
     * @brief Processes key inputs and events
     */
    void processInput();
    /**
     * @brief Updates the entities on the game
     */
    void update();
    /**
     * @brief Renderizes all the elements on the window
     */
    void render();

   public:
    /**
     * @brief Default constructor
     * @remark This method calls the @a init method by itself
     * @see void init()
     */
    Game();
    Game(const Game& other) = delete;
    Game(Game&& other) = delete;
    /**
     * @brief Destructor
     * @remark This method calls the @a destroy() method by itself
     * @see void destroy();
     */
    ~Game();
    Game& operator=(const Game& other) = delete;
    Game& operator=(Game&& other) = delete;

    /**
     * @brief Starts the game and keeps it running idifinitely
     * @Remark This method uses an "infinite" loop in which it calls
     * the @a processInput(), @a update() and @a render() methods
     * @see void processInput()
     * @see void update()
     * @see void render()
     */
    void run();
  };
}

#endif  // GAME_H
