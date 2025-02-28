// Copyright 2024, Kenneth Villalobos

#include <algorithm>

#include "Entity.h"

gameDev::Entity::Entity(const std::string& label, const std::string& path,
  const size_t width, const size_t height, const glm::vec2& pos,
  const glm::vec2& vel, const double angle)
  : label(label),
  path(path),
  width(width),
  height(height), 
  pos(pos),
  vel(vel), 
  angle(angle) {
}

gameDev::Entity::Entity(const Entity& other)
  : label(other.label),
  path(other.path),
  width(other.width),
  height(other.height),
  pos(other.pos),
  vel(other.vel),
  angle(other.angle) {
}

gameDev::Entity::Entity(Entity&& other)
  : label(""),
  path(""),
  width(0),
  height(0),
  pos(),
  vel(),
  angle(0.0) {
  std::swap(this->label, other.label);
  std::swap(this->path, other.path);
  std::swap(this->width, other.width);
  std::swap(this->height, other.height);
  std::swap(this->pos, other.pos);
  std::swap(this->vel, other.vel);
  std::swap(this->angle, other.angle);
}

gameDev::Entity::~Entity() {
  this->destroy();
}

gameDev::Entity gameDev::Entity::operator=(const Entity& other) {
  this->destroy();

  this->label = other.label;
  this->path = other.path;
  this->width = other.width;
  this->height = other.height;
  this->pos = other.pos;
  this->vel = other.vel;
  this->angle = other.angle;
  return *this;
}

gameDev::Entity gameDev::Entity::operator=(Entity&& other) {
  this->destroy();

  std::swap(this->label, other.label);
  std::swap(this->path, other.path);
  std::swap(this->width, other.width);
  std::swap(this->height, other.height);
  std::swap(this->pos, other.pos);
  std::swap(this->vel, other.vel);
  std::swap(this->angle, other.angle);
  return *this;
}

std::istream& gameDev::operator>>(std::istream& is, Entity& entity) {
  entity.destroy();

  return is
    >> entity.label >> entity.path
    >> entity.width >> entity.height
    >> entity.pos.x >> entity.pos.y
    >> entity.vel.x >> entity.vel.y
    >> entity.angle;
}

bool gameDev::Entity::init(SDL_Renderer* renderer) {
  SDL_Surface* surface = IMG_Load(this->path.c_str());

  this->texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  return this->texture != nullptr;
}

void gameDev::Entity::destroy() {
  if (this->texture) {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }
}