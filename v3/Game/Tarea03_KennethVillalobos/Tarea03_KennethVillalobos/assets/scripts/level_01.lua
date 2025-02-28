-- Level 01 elements table
scene = {
  -- Input action table
  inputActions = {
    [0] =
    {input = "SPACE",       action = "jump"},
    {input = "A",           action = "move_left"},
    {input = "D",           action = "move_right"},
    {input = "S",           action = "move_down"},
    {input = "RETURN",      action = "dash"},
    {input = "LEFT_CLICK", action = "attack"}
  },

  -- Sounds table
  sounds = {
    [0] =
    {entityType = "rino_enemy",  id = "hit", soundId = "enemy_hit_1"},
    {entityType = "rino_enemy",  id = "hit", soundId = "enemy_hit_2"},
    {entityType = "rino_enemy",  id = "hit", soundId = "enemy_hit_3"}
  },

  -- Animation table
  animations = {
    [0] =
    {entityType = "player",       id = "idle",          spriteId = "mask_idle",       w = 32, h = 32, numFrames = 11, currentFrame = 1, speedRate = 25},
    {entityType = "player",       id = "run",           spriteId = "mask_run",        w = 32, h = 32, numFrames = 12, currentFrame = 1, speedRate = 25},
    {entityType = "player",       id = "dash",          spriteId = "mask_dash",       w = 32, h = 32, numFrames = 11, currentFrame = 1, speedRate = 35},
    {entityType = "player",       id = "jump",          spriteId = "mask_jump",       w = 32, h = 32, numFrames = 1,  currentFrame = 1, speedRate = 25},
    {entityType = "player",       id = "double_jump",   spriteId = "mask_djump",      w = 32, h = 32, numFrames = 6,  currentFrame = 1, speedRate = 25},
    {entityType = "player",       id = "wall_grab",     spriteId = "mask_wall",       w = 32, h = 32, numFrames = 5,  currentFrame = 1, speedRate = 25},
    {entityType = "player",       id = "fall",          spriteId = "mask_fall",       w = 32, h = 32, numFrames = 1,  currentFrame = 1, speedRate = 25},
    {entityType = "player",       id = "hit",           spriteId = "mask_hit",        w = 32, h = 32, numFrames = 7,  currentFrame = 1, speedRate = 15},
    {entityType = "player",       id = "attack",        spriteId = "mask_attack",     w = 44, h = 32, numFrames = 7,  currentFrame = 1, speedRate = 25},
    {entityType = "heart",        id = "healed",        spriteId = "heart_full",      w = 18, h = 16, numFrames = 1,  currentFrame = 1, speedRate = 20},
    {entityType = "heart",        id = "healing",       spriteId = "heart_healing",   w = 18, h = 16, numFrames = 6,  currentFrame = 1, speedRate = 8},
    {entityType = "heart",        id = "hurted",        spriteId = "heart_empty",     w = 18, h = 16, numFrames = 1,  currentFrame = 1, speedRate = 20},
    {entityType = "heart",        id = "hurting",       spriteId = "heart_hurting",   w = 18, h = 16, numFrames = 6,  currentFrame = 1, speedRate = 8},
    {entityType = "rino_enemy",   id = "run",           spriteId = "rino_run",        w = 52, h = 34, numFrames = 6,  currentFrame = 1, speedRate = 25},
    {entityType = "rino_enemy",   id = "hit",           spriteId = "rino_hit",        w = 52, h = 34, numFrames = 5,  currentFrame = 1, speedRate = 15},
    {entityType = "bird_enemy",   id = "run",           spriteId = "bird_run",        w = 32, h = 32, numFrames = 9,  currentFrame = 1, speedRate = 25},
    {entityType = "bird_enemy",   id = "hit",           spriteId = "bird_hit",        w = 32, h = 32, numFrames = 5,  currentFrame = 1, speedRate = 15},
    {entityType = "bunny_enemy",  id = "run",           spriteId = "bunny_run",       w = 34, h = 44, numFrames = 12, currentFrame = 1, speedRate = 25},
    {entityType = "bunny_enemy",  id = "fall",          spriteId = "bunny_fall",      w = 34, h = 44, numFrames = 1,  currentFrame = 1, speedRate = 25},
    {entityType = "bunny_enemy",  id = "jump",          spriteId = "bunny_jump",      w = 34, h = 44, numFrames = 1,  currentFrame = 1, speedRate = 25},
    {entityType = "bunny_enemy",  id = "hit",           spriteId = "bunny_hit",       w = 34, h = 44, numFrames = 5,  currentFrame = 1, speedRate = 15},
    {entityType = "bat_enemy",    id = "run",           spriteId = "bat_run",         w = 46, h = 30, numFrames = 7,  currentFrame = 1, speedRate = 35},
    {entityType = "bat_enemy",    id = "hit",           spriteId = "bat_hit",         w = 46, h = 30, numFrames = 5,  currentFrame = 1, speedRate = 15},
    {entityType = "saw_trap",     id = "run",           spriteId = "saw_run",         w = 38, h = 38, numFrames = 8,  currentFrame = 1, speedRate = 35}
  },

  -- Map table
  map = {
    path = "./assets/levels/level_01.tmx"
  },

  -- Entities table
  entities = {
    [0] =
    {
      -- Player
      tag = "player",
      components = {
        sprite = {
          assetId = "mask_idle",
          w = 32,
          h = 32,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 109.0, y = 510.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 11,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 22,
          h = 28,
          offset = {x = 6.0, y = 3.0}
        },

        hitBox = {
          damage = 1,
          w = 16,
          h = 28,
          offset = {x = 28.0, y = 3.0}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = false
        },

        cameraFollow = {},

        script =  {
          path = "./assets/scripts/player.lua"
        },

        health = {
          max = 10,
          current = 10,

          heartsCreation = function(index)
            return {
              tag = "heart",
              components = {
                sprite = {
                  assetId = "heart_full",
                  w = 16,
                  h = 16,
                  srcRectX = 0,
                  srcRectY = 0
                },

                transform = {
                  position = {x = 22 + (index - 1) * 18, y = 6},
                  scale = {x = 1.0, y = 1.0},
                  rotation = 0.0
                },

                animation = {
                  numFrames = 1,
                  currentFrame = 1,
                  speedRate = 20
                },

                cameraIndependent = {},

                script =  {
                  path = "./assets/scripts/heart.lua"
                }
              }
            }
          end
        }
      }
    },
    {
      -- Enemy
      tag = "rino_enemy",
      components = {
        sprite = {
          assetId = "rino_run",
          w = 52,
          h = 34,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 1074.0, y = 632.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 6,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 74,
          h = 56,
          offset = {x = 12.0, y = 9.0}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = false
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 5,
          current = 5
        }
      }
    },

    {
      -- Enemy
      tag = "rino_enemy",
      components = {
        sprite = {
          assetId = "rino_run",
          w = 52,
          h = 34,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 928.0, y = 996.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 6,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 74,
          h = 56,
          offset = {x = 12.0, y = 9.0}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = false
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 5,
          current = 5
        }
      }
    },

    {
      -- Enemy
      tag = "bird_enemy",
      components = {
        sprite = {
          assetId = "bird_run",
          w = 32,
          h = 32,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 1686.0, y = 211.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 6,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 26,
          h = 26,
          offset = {x = 4, y = 4}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = true
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 1,
          current = 1
        }
      }
    },

    {
      -- Enemy
      tag = "bird_enemy",
      components = {
        sprite = {
          assetId = "bird_run",
          w = 32,
          h = 32,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 1748.0, y = 240.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 6,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 26,
          h = 26,
          offset = {x = 4, y = 4}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = true
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 1,
          current = 1
        }
      }
    },

    {
      -- Enemy
      tag = "bird_enemy",
      components = {
        sprite = {
          assetId = "bird_run",
          w = 32,
          h = 32,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 1748.0, y = 182.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 6,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 26,
          h = 26,
          offset = {x = 4, y = 4}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = true
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 1,
          current = 1
        }
      }
    },

    {
      -- Enemy
      tag = "bird_enemy",
      components = {
        sprite = {
          assetId = "bird_run",
          w = 32,
          h = 32,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 154.0, y = 50.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 6,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 26,
          h = 26,
          offset = {x = 4, y = 4}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = true
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 1,
          current = 1
        }
      }
    },

    {
      -- Enemy
      tag = "bird_enemy",
      components = {
        sprite = {
          assetId = "bird_run",
          w = 32,
          h = 32,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 102.0, y = 88.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 6,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 26,
          h = 26,
          offset = {x = 4, y = 4}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = true
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 2,
          current = 2
        }
      }
    },

    {
      -- Enemy
      tag = "bunny_enemy",
      components = {
        sprite = {
          assetId = "bunny_run",
          w = 34,
          h = 44,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 570.0, y = 478.0},
          scale = {x = 0.8, y = 0.8},
          rotation = 0.0
        },

        animation = {
          numFrames = 12,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 22,
          h = 26,
          offset = {x = 2, y = 12}
        },

        rigidBody = {
          mass = 0.5,
          isStatic = false
        },

        script =  {
          path = "./assets/scripts/jumping_enemy.lua"
        },

        health = {
          max = 3,
          current = 3
        }
      }
    },

    {
      -- Enemy
      tag = "bunny_enemy",
      components = {
        sprite = {
          assetId = "bunny_run",
          w = 34,
          h = 44,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 1696.0, y = 548.0},
          scale = {x = 0.8, y = 0.8},
          rotation = 0.0
        },

        animation = {
          numFrames = 12,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 22,
          h = 26,
          offset = {x = 2, y = 12}
        },

        rigidBody = {
          mass = 0.5,
          isStatic = false
        },

        script =  {
          path = "./assets/scripts/jumping_enemy.lua"
        },

        health = {
          max = 3,
          current = 3
        }
      }
    },

    {
      -- Enemy
      tag = "bunny_enemy",
      components = {
        sprite = {
          assetId = "bunny_run",
          w = 34,
          h = 44,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 2100.0, y = 498.0},
          scale = {x = 0.8, y = 0.8},
          rotation = 0.0
        },

        animation = {
          numFrames = 12,
          currentFrame = 1,
          speedRate = 25
        },

        boxCollider = {
          w = 22,
          h = 26,
          offset = {x = 2, y = 12}
        },

        rigidBody = {
          mass = 0.5,
          isStatic = false
        },

        script =  {
          path = "./assets/scripts/jumping_enemy.lua"
        },

        health = {
          max = 3,
          current = 3
        }
      }
    },

    {
      -- Enemy
      tag = "bat_enemy",
      components = {
        sprite = {
          assetId = "bat_run",
          w = 46,
          h = 30,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 1810.0, y = 1040.0},
          scale = {x = 0.5, y = 0.5},
          rotation = 0.0
        },

        animation = {
          numFrames = 7,
          currentFrame = 1,
          speedRate = 35
        },

        boxCollider = {
          w = 14,
          h = 12,
          offset = {x = 4, y = 4}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = true
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 2,
          current = 2
        }
      }
    },

    {
      -- Enemy
      tag = "bat_enemy",
      components = {
        sprite = {
          assetId = "bat_run",
          w = 46,
          h = 30,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 320.0, y = 968.0},
          scale = {x = 0.5, y = 0.5},
          rotation = 0.0
        },

        animation = {
          numFrames = 7,
          currentFrame = 1,
          speedRate = 35
        },

        boxCollider = {
          w = 14,
          h = 12,
          offset = {x = 4, y = 4}
        },

        rigidBody = {
          mass = 5.0,
          isStatic = true
        },

        script =  {
          path = "./assets/scripts/basic_enemy.lua"
        },

        health = {
          max = 2,
          current = 2
        }
      }
    },

    {
      -- Enemy
      tag = "saw_trap",
      components = {
        sprite = {
          assetId = "saw_run",
          w = 38,
          h = 38,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 1540.0, y = 900.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 8,
          currentFrame = 1,
          speedRate = 35
        },

        boxCollider = {
          w = 66,
          h = 66,
          offset = {x = 5, y = 5}
        }
      }
    },

    {
      -- Enemy
      tag = "saw_trap",
      components = {
        sprite = {
          assetId = "saw_run",
          w = 38,
          h = 38,
          srcRectX = 0,
          srcRectY = 0
        },

        transform = {
          position = {x = 567.0, y = 1027.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0
        },

        animation = {
          numFrames = 8,
          currentFrame = 1,
          speedRate = 35
        },

        boxCollider = {
          w = 66,
          h = 66,
          offset = {x = 5, y = 5}
        }
      }
    }
  },

  -- Song table
  song = {
    id = "main_song"
  }
}