-- jumping_enemy states
jumping_enemy_states = {
  run = {
    name = "run",
    speed = 0.8,

    on_enter = function(self, enemy)

    end
  },

  jump = {
    name = "jump",
    forceY = -275.0,
    forceX = 13,
    cooldown = 1500,

    on_enter = function(self, enemy)

      enemy.rigid_body.sum_forces.y = enemy.rigid_body.sum_forces.y +
        self.forceY * constants.pixels_per_meter

      if enemy.sprite.flip then
        enemy.rigid_body.sum_forces.x = enemy.rigid_body.sum_forces.x -
          self.forceX * constants.pixels_per_meter
      else
        enemy.rigid_body.sum_forces.x = enemy.rigid_body.sum_forces.x +
          self.forceX * constants.pixels_per_meter
      end

      enemy.can_jump = false
    end
  },

  fall = {
    name = "fall",

    on_enter = function(self, player)
    end
  },

  hit = {
    name = "hit",
    forceY = -270.0,
    forceX = 150.0,
    duration = 800,

    on_enter = function(self, enemy)
      enemy.hit_start_time = get_ticks()
    end
  }
}

-- Jumping_enemy class
Jumping_enemy = {
  entity = nil,
  state = jumping_enemy_states.run,
  rigid_body = nil,
  sprite = nil,
  health = nil,

  jump_finish_time = 0.0,
  hit_start_time = 0.0,

  can_jump = false
}

-- jumping_enemy constructor
function Jumping_enemy:new(o, entity)
  o = o or {}
  setmetatable(o, self)
  self.__index = self
  o.entity = entity
  o.state = jumping_enemy_states.run
  o.rigid_body = entity:get_rigid_body()
  o.sprite = entity:get_sprite()
  o.health = entity:get_health()
  o.jump_finish_time = 0.0
  o.hit_start_time = 0.0
  o.can_jump = false
  return o
end

function Jumping_enemy:flip(flip)
  self.sprite.flip = flip

  if flip then
    self.rigid_body.velocity.x = -jumping_enemy_states.run.speed *
      constants.pixels_per_meter
  else
    self.rigid_body.velocity.x = jumping_enemy_states.run.speed *
      constants.pixels_per_meter
  end
end

-- Change jumping_enemy state
function Jumping_enemy:change_state(new_state)
  if self.state.name ~= new_state.name then
    if self.state.on_exit then
      self.state:on_exit(self)
    end

    self.state = new_state

    play_sound(self.entity:get_tag(), self.state.name)
    change_animation(self.entity, self.entity:get_tag(), self.state.name)
    if self.state.on_enter then
      self.state:on_enter(self)
    end
  end
end

-- Check if jumping_enemy is stuck in a state
function Jumping_enemy:stuck_on_state(current_time)
  local stuck = false

  if self.state.name == jumping_enemy_states.hit.name then
    stuck = ((current_time - self.hit_start_time) < jumping_enemy_states.hit.duration)
  end

  return stuck
end

-- Initialize jumping_enemy
function Jumping_enemy:init()
  self:flip(true)
end

-- Update jumping_enemy
function Jumping_enemy:update()
  local current_time = get_ticks()
  -- If the jumping_enemy is not hit
  if not self:stuck_on_state(current_time) then

    -- Handle fall
    if self.rigid_body.velocity.y > 0.01  then
      self:change_state(jumping_enemy_states.fall)

    -- Handle jump
    elseif self.can_jump and
      ((current_time - self.jump_finish_time) >= jumping_enemy_states.jump.cooldown) then
      self:change_state(jumping_enemy_states.jump)
    end
  end
end

-- Handle collision
function Jumping_enemy:on_collision(other)
  if other:get_tag() == "floor" or other:get_tag() == "border" then
    local left_collision = check_collision_dir(self.entity, other, "left")
    if left_collision or check_collision_dir(self.entity, other, "right") then
      if left_collision then
        self:flip(true)
      else
        self:flip(false)
      end
    elseif check_collision_dir(self.entity, other, "up") then
      if not self.can_jump then
        self.jump_finish_time = get_ticks()
      end
      self.can_jump = true
      self:change_state(jumping_enemy_states.run)
    end
  end
end

-- Handle hit
function Jumping_enemy:hurt(damage, right)
  if self.state.name ~= jumping_enemy_states.hit.name then
    self.health.current_health = self.health.current_health - damage

    self:change_state(jumping_enemy_states.hit)
    self.rigid_body.sum_forces.y = self.rigid_body.sum_forces.y +
        jumping_enemy_states.hit.forceY * constants.pixels_per_meter
    if right then
      self.rigid_body.sum_forces.x = self.rigid_body.sum_forces.x -
        jumping_enemy_states.hit.forceX * constants.pixels_per_meter
    else
      self.rigid_body.sum_forces.x = self.rigid_body.sum_forces.x +
        jumping_enemy_states.hit.forceX * constants.pixels_per_meter
    end
  end
end

-- Ensure enemy table exists globally
if not enemies then
    enemies = {
      [0] = {}
    }
end

function awake()
  local enemy = Jumping_enemy:new(nil, this)
  enemy:init()
  enemies[this:get_id()] = enemy
end

function update()
  local enemy = enemies[this:get_id()]
  enemy:update()
end

function on_collision(other)
  local enemy = enemies[this:get_id()]
  enemy:on_collision(other)
end
