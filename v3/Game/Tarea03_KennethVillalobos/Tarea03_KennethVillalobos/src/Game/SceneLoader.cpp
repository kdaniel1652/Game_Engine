// Copyright 2024 Kenneth Villalobos

#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/CameraIndependentComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/TransformComponent.h"
#include "Game.h"
#include <glm/glm.hpp>
#include <iostream>
#include "SceneLoader.h"
#include <SDL_image.h>
#include <sstream>
#include "../Util/common.h"

void SceneLoader::loadScenes(const sol::table& scenes) {
  size_t index = 0;
  bool keepReading = true;
  while (keepReading) {
    sol::optional<sol::table> hasScene = scenes[index];
    if (hasScene == sol::nullopt) {
      keepReading = false;

    } else {
      this->scenePaths.emplace(
        scenes[index]["id"],
        scenes[index]["path"]
      );

      ++index;
    }
  }
}

void SceneLoader::loadAssets(const sol::table& assets,
  std::shared_ptr<AssetStore>& assetStore,
  SDL_Renderer* renderer) {
  sol::table asset;
  std::string type;
  std::string id;
  std::string path;

  size_t index = 0;
  bool keepReading = true;
  while (keepReading) {
    sol::optional<sol::table> hasAsset = assets[index];
    if (hasAsset == sol::nullopt) {
      keepReading = false;

    } else {
      asset = assets[index];
      type = asset["type"];
      id = asset["id"];
      path = asset["path"];

      if (type == "texture") {
        assetStore->addTexture(id, path, renderer);
      }
      else if (type == "font") {
        const int fontSize = asset["size"];
        assetStore->addFont(id, path, fontSize);
      }
      else if (type == "song") {
        const int volume = asset["volume"];
        assetStore->addSong(id, path, volume);
      }
      else if (type == "sound") {
        const int volume = asset["volume"];
        assetStore->addSound(id, path, volume);
      }

      ++index;
    }
  }
}

void SceneLoader::loadInputActions(const sol::table& inputActions,
  std::shared_ptr<ControllerManager>& controllerManager) {
  sol::table inputAction;
  std::string inputString;
  SDL_Keycode key;
  std::string action;

  size_t index = 0;
  bool keepReading = true;
  while (keepReading) {
    sol::optional<sol::table> hasInputAction = inputActions[index];
    if (hasInputAction == sol::nullopt) {
      keepReading = false;

    } else {
      inputAction = inputActions[index];
      inputString = inputAction["input"];
      action = inputAction["action"];

      key = SDL_GetKeyFromName(inputString.c_str());
      if (key != SDLK_UNKNOWN) {
        controllerManager->mapKeyAction(key, action);

      }
      else {
        if (inputString == "LEFT_CLICK") {
          controllerManager->mapButtonAction(SDL_BUTTON_LEFT, action);
        }
        else if (inputString == "RIGHT_CLICK") {
          controllerManager->mapButtonAction(SDL_BUTTON_RIGHT, action);
        }
        else if (inputString == "MIDDLE_CLICK") {
          controllerManager->mapButtonAction(SDL_BUTTON_MIDDLE, action);
        }
        else {
          std::cerr << SDL_GetError() << std::endl;
          std::cerr << "READING ERROR: Can´t map: " << inputString << " to: "
            << action << std::endl;
          keepReading = false;
        }
      }
      ++index;
    }
  }
}

void SceneLoader::loadSounds(const sol::table& sounds,
  std::shared_ptr<SoundManager>& soundManager) {
  sol::table sound;
  std::string entityType;
  std::string id;
  std::string soundId;

  size_t index = 0;
  bool keepReading = true;
  while (keepReading) {
    sol::optional<sol::table> hasSound = sounds[index];
    if (hasSound == sol::nullopt) {
      keepReading = false;

    } else {
      sound = sounds[index];
      entityType = sound["entityType"];
      id = sound["id"];
      soundId = sound["soundId"];

      soundManager->addSound(entityType, id, soundId);
      ++index;
    }
  }
}

void SceneLoader::loadAnimations(const sol::table& animations,
  std::shared_ptr<AnimationManager>& animationManager) {
  sol::table animation;
  std::string entityType;
  std::string id;
  std::string spriteId;
  int width = 0;
  int height = 0;
  int numFrames = 0;
  int currentFrame = 0;
  int speedRate = 0;

  size_t index = 0;
  bool keepReading = true;
  while (keepReading) {
    sol::optional<sol::table> hasAnimation = animations[index];
    if (hasAnimation == sol::nullopt) {
      keepReading = false;

    } else {
      animation = animations[index];
      entityType = animation["entityType"];
      id = animation["id"];
      spriteId = animation["spriteId"];
      width = animation["w"];
      height = animation["h"];
      numFrames = animation["numFrames"];
      currentFrame = animation["currentFrame"];
      speedRate = animation["speedRate"];

      animationManager->addAnimation(entityType, id, spriteId, width, height,
        numFrames, currentFrame, speedRate);

      ++index;
    }
  }
}

void SceneLoader::loadMap(const sol::table& map,
  std::shared_ptr<ECSManager>& manager,
  std::shared_ptr<AssetStore>& assetStore) {
  std::string mapPath = map["path"];

  tinyxml2::XMLDocument level;
  level.LoadFile(mapPath.c_str());

  tinyxml2::XMLElement* root = level.RootElement();
  int tileWidth = 0;
  int tileHeight = 0;
  int levelWidth = 0;
  int levelHeight = 0;
  int pixelWidth = 0;

  root->QueryIntAttribute("tilewidth", &tileWidth);
  root->QueryIntAttribute("tileheight", &tileHeight);
  root->QueryIntAttribute("width", &levelWidth);
  root->QueryIntAttribute("height", &levelHeight);
  SDL_QueryTexture(assetStore->getTexture(constants::TILESET_ID),
    nullptr, nullptr, &pixelWidth, nullptr);

  Game::mapWidth = tileWidth * levelWidth;
  Game::mapHeight = tileHeight * levelHeight;
  const int tilesInWidth = pixelWidth / tileWidth;

  tinyxml2::XMLElement* layer = root->FirstChildElement("layer");
  while (layer != nullptr) {
    this->loadMapSprites(manager, layer, tileWidth, tileHeight, levelWidth,
      levelHeight, tilesInWidth);
    layer = layer->NextSiblingElement("layer");
  }

  tinyxml2::XMLElement* objectGorup = root->FirstChildElement("objectgroup");
  tinyxml2::XMLElement* object = objectGorup->FirstChildElement("object");
  while (object != nullptr) {
    loadMapColliders(manager, object);
    object = object->NextSiblingElement("object");
  }
}

void SceneLoader::loadMapSprites(std::shared_ptr<ECSManager>& manager,
  tinyxml2::XMLElement* layer, const int tileWidth,
  const int tileHeight, const int levelWidth, const int levelHeight,
  const int tilesInWidth) {
  tinyxml2::XMLElement* layerData = layer->FirstChildElement("data");
  const char* data = layerData->GetText();

  std::stringstream tmpNumber;
  int pos = 0;
  int tileNumber = 0;

  bool keepReading = true;
  while (keepReading) {
    if (data[pos] == '\0') {
      keepReading = false;
    }
    else if (isdigit(data[pos])) {
      tmpNumber << data[pos];
    }
    else if (tmpNumber.str().length() != 0) {
      int tileId = std::stoi(tmpNumber.str());

      if (tileId > 0) {
        Entity tile = manager->createEntity();
        tile.addComponent<TransformComponent>(
          glm::vec2(
            (tileNumber % levelWidth) * tileWidth,
            (tileNumber / levelWidth) * tileHeight
          )
        );
        tile.addComponent<SpriteComponent>(
          constants::TILESET_ID,
          tileWidth,
          tileHeight,
          ((tileId - 1) % tilesInWidth) * tileWidth,
          ((tileId - 1) / tilesInWidth) * tileHeight
        );
      }
      tileNumber++;
      tmpNumber.str("");
    }
    pos++;
  }
}

void SceneLoader::loadMapColliders(std::shared_ptr<ECSManager>& manager,
  tinyxml2::XMLElement* object) {
  const char* type;
  std::string tag;
  int x; int y; int  width; int height;

  object->QueryStringAttribute("type", &type);
  tag = type;

  object->QueryIntAttribute("x", &x);
  object->QueryIntAttribute("y", &y);
  object->QueryIntAttribute("width", &width);
  object->QueryIntAttribute("height", &height);

  Entity collider = manager->createEntity();
  collider.addTag(tag);
  collider.addComponent<TransformComponent>(
    glm::vec2(x, y)
  );
  collider.addComponent<BoxColliderComponent>(
    width,
    height
  );
}

void SceneLoader::loadEntities(const sol::table& entities, sol::state& lua,
  std::shared_ptr<ECSManager>& manager) {
  sol::table entity;

  size_t index = 0;
  bool keepReading = true;
  while (keepReading) {
    sol::optional<sol::table> hasEntity = entities[index];
    if (hasEntity == sol::nullopt) {
      keepReading = false;

    } else {
      entity = entities[index];
      loadEntity(entity, lua, manager);
      ++index;
    }
  }
}

Entity SceneLoader::loadEntity(const sol::table& entity,
  sol::state& lua, std::shared_ptr<ECSManager>& manager) {
  Entity newEntity = manager->createEntity();

  sol::optional<std::string> tag = entity["tag"];
  if (tag == sol::nullopt) {
    std::cerr << "GAME LOADING ERROR: entity tag not found" << std::endl;
  }
  else {
    newEntity.addTag(tag.value());

    sol::optional<sol::table> components = entity["components"];
    if (components != sol::nullopt) {

      loadComponent<SpriteComponent>(newEntity,
        components.value()["sprite"],
        [](const sol::table& table) {
          return SpriteComponent(
            table["assetId"],
            table["w"],
            table["h"],
            table["srcRectX"],
            table["srcRectY"]);
        });

      loadComponent<TextComponent>(newEntity,
        components.value()["text"],
        [](const sol::table& table) {
          return TextComponent(
            table["assetId"],
            table["label"],
            table["r"],
            table["g"],
            table["b"],
            table["a"]);
        });

      loadComponent<TransformComponent>(newEntity,
        components.value()["transform"],
        [](const sol::table& table) {
          return TransformComponent(
            glm::vec2(
              table["position"]["x"],
              table["position"]["y"]
            ),
            glm::vec2(
              table["scale"]["x"],
              table["scale"]["y"]
            ),
            table["rotation"]);
        });

      loadComponent<AnimationComponent>(newEntity,
        components.value()["animation"],
        [](const sol::table& table) {
          return AnimationComponent(
            table["numFrames"],
            table["currentFrame"],
            table["speedRate"]);
        });

      loadComponent<BoxColliderComponent>(newEntity,
        components.value()["boxCollider"],
        [](const sol::table& table) {
          return BoxColliderComponent(
            table["w"],
            table["h"],
            glm::vec2(
              table["offset"]["x"],
              table["offset"]["y"])
            );
        });

      loadComponent<HitBoxComponent>(newEntity,
        components.value()["hitBox"],
        [](const sol::table& table) {
          return HitBoxComponent(
            table["damage"],
            table["w"],
            table["h"],
            glm::vec2(
              table["offset"]["x"],
              table["offset"]["y"])
            );
        });

      loadComponent<RigidBodyComponent>(newEntity,
        components.value()["rigidBody"],
        [](const sol::table& table) {
          return RigidBodyComponent(
            table["mass"],
            table["isStatic"]
          );
        });

      loadComponent<CameraFollowComponent>(newEntity,
        components.value()["cameraFollow"],
        [](const sol::table&) {
          return CameraFollowComponent(
          );
        });

      loadComponent<CameraIndependentComponent>(newEntity,
        components.value()["cameraIndependent"],
        [](const sol::table&) {
          return CameraIndependentComponent(
          );
        });

      loadScriptComponent(newEntity, components.value()["script"], lua);

      loadHealthComponent(newEntity, components.value()["health"], lua,
        manager);
    }
  }

  return newEntity;
}

void SceneLoader::loadScriptComponent(Entity& entity,
  const sol::optional<sol::table>& componentTable,
  sol::state& lua) {
  if (componentTable != sol::nullopt) {
    lua["awake"] = sol::nil;
    lua["update"] = sol::nil;
    lua["on_collision"] = sol::nil;
    lua["on_hit"] = sol::nil;
    lua["on_death"] = sol::nil;

    std::string scriptPath =
      componentTable.value()["path"];
    lua.script_file(scriptPath);

    sol::optional<sol::function> hasAwake = lua["awake"];
    sol::function awake = sol::nil;
    if (hasAwake != sol::nullopt) {
      awake = lua["awake"];
    }

    sol::optional<sol::function> hasUpdate = lua["update"];
    sol::function update = sol::nil;
    if (hasUpdate != sol::nullopt) {
      update = lua["update"];
    }

    sol::optional<sol::function> hasOnCollision = lua["on_collision"];
    sol::function onCollision = sol::nil;
    if (hasOnCollision != sol::nullopt) {
      onCollision = lua["on_collision"];
    }

    sol::optional<sol::function> hasOnHit = lua["on_hit"];
    sol::function onHit = sol::nil;
    if (hasOnHit != sol::nullopt) {
      onHit = lua["on_hit"];
    }

    sol::optional<sol::function> hasOnDeath = lua["on_death"];
    sol::function onDeath = sol::nil;
    if (hasOnDeath != sol::nullopt) {
      onDeath = lua["on_death"];
    }

    entity.addComponent<ScriptComponent>(
      awake,
      update,
      onCollision,
      onHit,
      onDeath
    );
  }
}

void SceneLoader::loadHealthComponent(Entity& entity,
  const sol::optional<sol::table>& componentTable,
  sol::state& lua, std::shared_ptr<ECSManager>& manager) {
  if (componentTable != sol::nullopt) {
    entity.addComponent<HealthComponent>(
      componentTable.value()["max"],
      componentTable.value()["current"]
    );

    sol::optional<sol::function> hearts =
      componentTable.value()["heartsCreation"];

    if (hearts != sol::nullopt) {
      sol::function heartsCreation =
        componentTable.value()["heartsCreation"];

      sol::table heartTable;
      auto& healthComponent = entity.getComponent<HealthComponent>();
      for (int heart = 0; heart < healthComponent.maxHealth; ++heart) {
        heartTable = heartsCreation(heart);
        Entity heartEntity = this->loadEntity(heartTable, lua, manager);
        healthComponent.hearts.push_back(heartEntity);
      }
    }
  }
}

void SceneLoader::loadGame(const std::string& gameName, sol::state& lua,
  std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer) {
  sol::load_result script = lua.load_file("./assets/scripts/" + gameName);
  if (!script.valid()) {
    sol::error err = script;
    std::string errMesage = err.what();
    std::cerr << "GAME LOADING ERROR: " << errMesage << std::endl;

  } else {
    lua.script_file("./assets/scripts/" + gameName);
    sol::table game = lua["game"];

    sol::table scenes = game["scenes"];
    this->loadScenes(scenes);
    
    sol::table assets = game["assets"];
    this->loadAssets(assets, assetStore, renderer);
  }
}

void SceneLoader::loadSong(const sol::table& song,
  std::shared_ptr<MusicManager>& musicManager,
  std::shared_ptr<AssetStore>& assetStore) {
  if (!song.valid()) {
    std::cerr << "GAME WARNING: No song was give for a scene" << std::endl;
    musicManager->pauseSong();

  } else {
    std::string songId = song["id"];
    musicManager->playSong(songId, assetStore);
  }
}

void SceneLoader::loadScene(const std::string& sceneId, sol::state& lua,
  std::shared_ptr<AssetStore>& assetStore,
  std::shared_ptr<ControllerManager>& controllerManager,
  std::shared_ptr<SoundManager>& soundManager,
  std::shared_ptr<AnimationManager>& animationManager,
  std::shared_ptr<ECSManager>& manager,
  std::shared_ptr<MusicManager>& musicManager) {
  auto it = this->scenePaths.find(sceneId);
  if (it != this->scenePaths.end()) {
    sol::load_result script = lua.load_file(it->second);
    if (!script.valid()) {
      sol::error err = script;
      std::string errMesage = err.what();
      std::cerr << "GAME LOADING ERROR: " << errMesage << std::endl;

    } else {
      controllerManager->clear();
      soundManager->clear();
      animationManager->clear();
      manager->clean();

      lua.script_file(it->second);
      sol::table scene = lua["scene"];

      sol::optional<sol::table> inputActions = scene["inputActions"];
      if (inputActions) {
        this->loadInputActions(*inputActions, controllerManager);
      }

      sol::optional<sol::table> sounds = scene["sounds"];
      if (sounds) {
        this->loadSounds(*sounds, soundManager);
      }

      sol::optional<sol::table> animations = scene["animations"];
      if (animations) {
        this->loadAnimations(*animations, animationManager);
      }

      sol::optional<sol::table> map = scene["map"];
      if (map) {
        this->loadMap(*map, manager, assetStore);
      }

      sol::optional<sol::table> entities = scene["entities"];
      if (entities) {
        this->loadEntities(*entities, lua, manager);
      }

      sol::optional<sol::table> song = scene["song"];
      if (song) {
        this->loadSong(*song, musicManager, assetStore);
      }
    }
  }
}
