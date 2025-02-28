-- Basic_Enemy states
basic_enemy_states = {
  run = {
    name = "run",
    speed = 2,

    on_enter = function(self, basic_enemy)
    end
  },

  hit = {
    name = "hit",
    forceY = -270.0,
    forceX = 150.0,
    duration = 800,

    on_enter = function(self, basic_enemy)
      basic_enemy.hit_start_time = get_ticks()
    end
  }
}

-- Basic_Enemy class
Basic_Enemy = {
  entity = nil,
  state = basic_enemy_states.run,
  rigid_body = nil,
  sprite = nil,
  health = nil,

  hit_start_time = 0.0
}

-- Basic_Enemy constructor
function Basic_Enemy:new(o, entity)
  o = o or {}
  setmetatable(o, self)
  self.__index = self
  o.entity = entity
  o.state = basic_enemy_states.run
  o.rigid_body = entity:get_rigid_body()
  o.sprite = entity:get_sprite()
  o.health = entity:get_health()
  o.hit_start_time = 0.0
  return o
end

-- Change basic_enemy state
function Basic_Enemy:change_state(new_state)
  if self.state.name ~= new_state.name then

    self.state = new_state
    play_sound(self.entity:get_tag(), self.state.name)
    change_animation(self.entity, self.entity:get_tag(), self.state.name)
    self.state:on_enter(self)
  end
end

function Basic_Enemy:flip(flip)
  self.sprite.flip = flip

  if flip then
    self.rigid_body.velocity.x = -basic_enemy_states.run.speed *
      constants.pixels_per_meter
  else
    self.rigid_body.velocity.x = basic_enemy_states.run.speed *
      constants.pixels_per_meter
  end
end

-- Check if basic_enemy is stuck in a state
function Basic_Enemy:stuck_on_state(current_time)
  local stuck = false

  if self.state.name == basic_enemy_states.hit.name then
    stuck = ((current_time - self.hit_start_time) < basic_enemy_states.hit.duration)
  end

  return stuck
end

-- Initialize basic_enemy
function Basic_Enemy:init()
  self:flip(true)
end

-- Update basic_enemy
function Basic_Enemy:update()
  local current_time = get_ticks()
  -- If the basic_enemy is not dashing or hit
  if not self:stuck_on_state(current_time) then
    -- Handle movement
      self:change_state(basic_enemy_states.run)
  end
end

-- Handle collision
function Basic_Enemy:on_collision(other)
	if other:get_tag() == "floor" or other:get_tag() == "border" then
		left_colision =  check_collision_dir(self.entity, other, "left")
    if left_colision or check_collision_dir(self.entity, other, "right") then
			if left_colision then
				self:flip(true)
			else
				self:flip(false)
			end
		end
	end
end

-- Handle hit
function Basic_Enemy:hurt(damage, right)
  if self.state.name ~= basic_enemy_states.hit.name then
    self.health.current_health =
      self.health.current_health - damage

    self:change_state(basic_enemy_states.hit)
    self.rigid_body.sum_forces.y = self.rigid_body.sum_forces.y +
        basic_enemy_states.hit.forceY * constants.pixels_per_meter
    if right then
      self.rigid_body.sum_forces.x = self.rigid_body.sum_forces.x +
        -basic_enemy_states.hit.forceX * constants.pixels_per_meter
    else
      self.rigid_body.sum_forces.x = self.rigid_body.sum_forces.x +
        basic_enemy_states.hit.forceX * constants.pixels_per_meter
    end
  end
end

-- Ensure enemy table exists globally
if not enemies then
    enemies = {
      [0] = {}
    }
end

-- Script functions
function awake()
  local enemy = Basic_Enemy:new(nil, this)
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