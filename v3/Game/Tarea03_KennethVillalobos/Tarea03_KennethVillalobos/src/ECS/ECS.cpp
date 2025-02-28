// Copyright 2024 Kenneth Villalobos

#include <algorithm>
#include "ECS.h"

Entity::Entity(const size_t id)
  : id(id) {
}

void Entity::kill() {
  this->manager->killEntity(*this);
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

void Entity::addTag(const std::string& tag) {
  this->manager->addTagToEntity(*this, tag);
}

std::string Entity::getTag() const {
  return this->manager->getTagFromEntity(*this);
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
  for (auto entity : this->entitiesToBeKilled) {
    size_t id = entity.getId();
    std::string oldTag = this->entityTag[id].first;

    this->removeEntityFromSystem(entity);
    this->entityTag.erase(id);
    this->entityGroups[oldTag].remove(id);
    this->entityComponentSignatures[id].reset();
    this->freeIds.push_back(id);
  }
  this->entitiesToBeKilled.clear();

  for (auto entity : this->entitiesToBeAdded) {
    this->addEntityToSystem(entity);
  }
  this->entitiesToBeAdded.clear();
}

Entity ECSManager::createEntity() {
  size_t entityId = 0;

  if (this->freeIds.empty()) {
    entityId = this->numEntities++;
    if (entityId >= this->entityComponentSignatures.size()) {
      this->entityComponentSignatures.resize(entityId + 1);
    }
  } else {
    entityId = this->freeIds.front();
    this->freeIds.pop_front();
  }
  
  Entity entity(entityId);
  entity.manager = this;
  this->entitiesToBeAdded.insert(entity);

  return entity;
}

void ECSManager::killEntity(Entity& entity) {
  this->entitiesToBeKilled.insert(entity);
}

std::set<Entity>& ECSManager::getEntitiesToBeAdded() {
  return this->entitiesToBeAdded;
}

void ECSManager::addEntityToSystem(Entity& entity) {
  const size_t entityId = entity.getId();
  const Signature& entitySignatute = this->entityComponentSignatures[entityId];

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

Entity ECSManager::getEntity(const int id) {
  const auto it = this->entityTag.find(id);
  return (it != this->entityTag.cend()) ? it->second.second : Entity();
}

void ECSManager::clean() {
  for (auto entity : this->entityTag) {
    this->killEntity(entity.second.second);
  }
}

void ECSManager::destroy() {
  this->entityComponentSignatures.clear();
  this->componentPools.clear();
  this->systems.clear();
  this->entitiesToBeAdded.clear();
  this->entitiesToBeKilled.clear();
  this->freeIds.clear();
  this->entityTag.clear();
  this->entityGroups.clear();
  this->numEntities = 0;
}

void ECSManager::addTagToEntity(Entity& entity, const std::string& tag) {
  const size_t id = entity.getId();

  auto it = this->entityTag.find(id);

  if (it == this->entityTag.end()) {
    this->entityTag.emplace(id, std::pair<std::string, Entity>(tag, entity));
    this->entityGroups[tag].push_back(id);
  }
}

void ECSManager::setTagToEntity(Entity& entity, const std::string& tag) {
  const size_t id = entity.getId();

  std::string oldTag = this->entityTag[id].first;
  if (oldTag != tag) {
    this->entityTag[id] = std::pair<std::string, Entity>(tag, entity);
    this->entityGroups[oldTag].remove(id);
    this->entityGroups[tag].push_back(id);
  }
}

std::string ECSManager::getTagFromEntity(const Entity& entity) const {
  const auto it = this->entityTag.find(entity.getId());

  return (it != this->entityTag.cend()) ? it->second.first : std::string("");
}

void ECSManager::clearTags() {
  this->entityTag.clear();
  this->entityGroups.clear();
}
