// Copyright 2024, Kenneth Villalobos

#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <istream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

/**
  * @namespace Namespace to store all the classes and structs implemented on
  * the project
  */
namespace gameDev {
  // forward delcaration (To avoid circular inclusion problems)
  class Game;

  /**
    * @class Class mainly to store most objects relevant to an entity
    */
  class Entity {
    // Attributes
  private:
    // Image of the entity
    SDL_Texture* texture = nullptr;
    // Label of the entity
    // (Store here for convenience)
    std::string label;
    // Path to the image
    std::string path;
    // Dimensions
    size_t width;
    size_t height;
    // Position of the entity
    glm::vec2 pos;
    // Velocity of the entity (speed and direction)
    glm::vec2 vel;
    // Angle of rotation of the entity
    double angle;
    
    // The Game must be able to interact with the private members
    friend class Game;

  // Constructors
  public:
    /**
     * @brief Default constructor
     * @param label Label to be displayed on top the entity
     * @param path relative path to the image
     * @param width The Width of the image (in pixels)
     * @param height The height of the image (in pixels)
     * @param pos Current position of the entity (x, y)
     * @param vel Current velocity of the entity (x, y). Positive values
     * go right and doww, while negatives go left and up.
     * @param angle of rotation of the entity
     * @remark This method does not call the @a init method by itself, as
     * it migth be desirable to store the data without initializing the
     * entity right away
     * @see bool init(SDL_Renderer* renderer)
     */
    Entity(const std::string& label = std::string(""),
      const std::string& path = std::string(""), const size_t width = 0,
      const size_t height = 0, const glm::vec2& pos = glm::vec2(),
      const glm::vec2& vel = glm::vec2(), const double angle = 0.0);
    /**
     * @brief Copy constructor
     * @param other Entity to copy the data from
     * @remark This constructor will not copy the texture pointer or
     * initialize the entity.
     * @see bool init(SDL_Renderer* renderer)
     */
    Entity(const Entity& other);
    /**
     * @brief Move memory constructor
     * @param other Entity to steal the memory from
     * @remark This constructor WILL copy the texture leaving the other
     * entity invalid, after that only this entity must be destroyed
     * @see void destroy();
     */
    Entity(Entity&& other);
    /**
     * @brief Destructor
     * @remark Automatically calls the @a destroy() method in case it
     * is needed
     * @see void destroy();
     */
    ~Entity();
    /**
     * @brief Copy assignator
     * @param other Entity to copy the data from
     * @returns a reference to the Entity that called the method
     * @remark This assignator will not copy the texture pointer or
     * initialize the entity.
     * @remark Using this method will automatically call the a@ destroy()
     * metbhod on this object previously to prevent memory leaks
     * @see bool init(SDL_Renderer* renderer)
     * @see void destroy();
     */
    Entity operator=(const Entity& other);
    /**
     * @brief Move memory assignator
     * @param other Entity to steal the memory from
     * @returns a reference to the Entity that called the method
     * @remark This assignator WILL swap all parameters between the two
     * objects
     * @remark Using this method will automatically call the a@ destroy()
     * method on this object previously to prevent memory leaks
     * @see void destroy();
     */
    Entity operator=(Entity&& other);

    /**
     * @brief Reads the information necessary for an entity from the stream
     * @param is Input stream to read from
     * @param entity Entity where the data will be stored
     * @details The reading format is "string string int int float float
     *  float float double", the number of spaces between the elements is
     * variable.
     * @remark If the reading format is not followed, the behavior is
     * undefined
     */
    friend std::istream& operator>>(std::istream& is, Entity& entity);

    /**
     * @brief Initializes the entity allocating the necessary memory
     * @param renderer Renderer from SDL to render the entity with
     * @returns a bool indicating if the procedure was successfull
     */
    bool init(SDL_Renderer* renderer);
    /**
     * @brief Frees all the allocated memory
     * @remark If the Entity was already destroyed, does nothing
     */
    void destroy();
  };
}

#endif  // ENTITY_H
