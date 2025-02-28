// Copyright 2024, Kenneth Villalobos

#include <algorithm>

#include "ECS.h"

Entity::Entity(const size_t id)
  : id(id) {
}

void Entity::kill() {
  this->manager->killEntity(*this);
}

Entity Entity::createAnotherEntity() const {
  return this->manager->createEntity();
}

bool Entity::operator==(const Entity& other) const {
  return this->id == other.id;
}

bool Entity::operator!=(const Entity& other) const {
  return this->id != other.id;
}

bool Entity::operator>(const Entity& other) const {
  return this->id > other.id;
}

bool Entity::operator<(const Entity& other) const {
  return this->id < other.id;
}

void System::addEntityToSystem(Entity& entity) {
  this->entities.push_back(entity);
}

void System::removeEntityFromSystem(Entity& entity) {
  std::vector<Entity>::iterator newEnd =
    std::remove_if(
      this->entities.begin(),
      this->entities.end(),
      [&entity](const Entity& other) {
        return entity == other;
      }
    );
  this->entities.erase(newEnd, this->entities.end());
}

std::vector<Entity> System::getSystemEntities() const {
  return this->entities;
}

const Signature& System::getComponentSignature() const {
  return this->componentSignature;
}

void ECSManager::update() {
  // Add entties
  for (Entity entity : this->entitiesToBeAdded) {
    this->addEntityToSystem(entity);
  }
  this->entitiesToBeAdded.clear();

  // Remove entities
  for (Entity entity : this->entitiesToBeKilled) {
    this->removeEntityFromSystem(entity);
    this->entityComponentSignatures[entity.getId()].reset();
    this->freeIds.push_back(entity.getId());
  }
  this->entitiesToBeKilled.clear();
}

Entity ECSManager::createEntity() {
  size_t entityId = 0;

  // If there are no free id´s
  if (this->freeIds.empty()) {
    entityId = ++this->numEntities;
    if (entityId >= this->entityComponentSignatures.size()) {
      this->entityComponentSignatures.resize(entityId + 1);
    }

  // If there are free id´s
  } else {
    entityId = this->freeIds.front();
    this->freeIds.pop_front();
  }
  
  // Create the entity
  Entity entity(entityId);
  entity.manager = this;
  this->entitiesToBeAdded.insert(entity);

  return entity;
}

void ECSManager::killEntity(Entity& entity) {
  this->entitiesToBeKilled.insert(entity);
}

void ECSManager::addEntityToSystem(Entity& entity) {
  // Get info from the entity
  const size_t entityId = entity.getId();
  const Signature& entitySignatute = this->entityComponentSignatures[entityId];

  // Go through all the systems and add
  // the entity to the corresponding ones
  for (auto system : this->systems) {
    const Signature& systemSignature =
      system.second->getComponentSignature();

    bool isInterested =
      (entitySignatute & systemSignature) == systemSignature;

    if (isInterested) {
      system.second->addEntityToSystem(entity);
    }
  }
}

void ECSManager::removeEntityFromSystem(Entity& entity) {
  for (auto system : this->systems) {
    system.second->removeEntityFromSystem(entity);
  }
}
