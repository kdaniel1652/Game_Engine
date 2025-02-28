-- Player states
player_states = {
  idle = {
    name = "idle",

    on_enter = function(self, player)
    end
  },

  run = {
    name = "run",
    speed = 3.0,

    on_enter = function(self, player)
    end
  },

  dash = {
    name = "dash",
    boost = 550.0,
    duration = 1350.0,
    cooldown = 1000.0,

    on_enter = function(self, player)
      player.dash_start_time = get_ticks()
      self:on_update(player)
    end,
    on_update = function(self, player)
      player.rigid_body.sum_forces.y = 0.0
      player.rigid_body.velocity.y = 0.0
      if (player.sprite.flip) then
        player.rigid_body.velocity.x = -self.boost
      else
        player.rigid_body.velocity.x = self.boost
      end
    end,
    on_exit = function(self, player)
      player.is_static = false
      player.dash_finish_time = get_ticks()
    end
  },

  jump = {
    name = "jump",
    force = -650.0,

    on_enter = function(self, player)
      player.rigid_body.sum_forces.y = player.rigid_body.sum_forces.y +
        self.force * constants.pixels_per_meter
      player.can_jump = false
      player.jump_start_time = get_ticks()
    end
  },

  double_jump = {
    name = "double_jump",
    force = -700.0,
    duration = 250.0,
    cooldown = 250.0,

    on_enter = function(self, player)
      player.rigid_body.sum_forces.y = player.rigid_body.sum_forces.y +
        self.force * constants.pixels_per_meter
      player.can_double_jump = false
      player.double_jump_start_time = get_ticks()
    end
  },

  wall_grab = {
    name = "wall_grab",

    on_enter = function(self, player)
      player.can_wall_grab = false
      player.can_jump = true
      player.can_double_jump = true

      if player.rigid_body.sum_forces.y > 0.0 then
        player.rigid_body.sum_forces.y = player.rigid_body.sum_forces.y / 8.0
      else
        player.rigid_body.sum_forces.y = 0.0
      end
    end
  },

  fall = {
    name = "fall",

    on_enter = function(self, player)
    end
  },

  hit = {
    name = "hit",
    forceY = -550.0,
    forceX = 245.0,
    duration = 800,

    on_enter = function(self, player)
      player.hit_start_time = get_ticks()
      player.rigid_body.sum_forces.y = player.rigid_body.sum_forces.y +
        self.forceY * constants.pixels_per_meter
      if (player.sprite.flip) then
        player.rigid_body.sum_forces.x = player.rigid_body.sum_forces.x +
          self.forceX * constants.pixels_per_meter
      else
        player.rigid_body.sum_forces.x = player.rigid_body.sum_forces.x +
          -self.forceX * constants.pixels_per_meter
      end
    end,

    on_update = function(self, player)
    end
  },

  attack = {
    name = "attack",
    damage = 1,
    duration = 350.0,
    cooldown = 400.0,
    bounce = 8,

    on_enter = function(self, player)
      player.attack_start_time = get_ticks()
      player.hitbox.active = true
      if (player.sprite.flip) then
        player:flip(player.sprite.flip)
      end
    end,

    on_update = function(self, player)
    end,

    on_exit = function(self, player)
      player.attack_finish_time = get_ticks()
      player.hitbox.active = false
    end
  }
}

-- Player class
Player = {
  entity = nil,
  state = player_states.idle,
  rigid_body = nil,
  transform = nil,
  sprite = nil,
  collider = nil,
  hitbox = nil,
  health = nil,
  hearts = {
  },
  current_heart = 0,

  collider_roffset = 0.0,
  hitbox_roffset = 0.0,

  jump_start_time = 0.0,
  double_jump_start_time = 0.0,
  dash_start_time = 0.0,
  dash_finish_time = 0.0,
  hit_start_time = 0.0,
  attack_start_time = 0.0,
  attack_finish_time = 0.0,

  can_jump = false,
  can_double_jump = false,
  can_wall_grab = false
}

-- Change player state
function Player:change_state(new_state)
  if self.state.name ~= new_state.name then

    if self.state.on_exit then
      self.state:on_exit(self)
    end

    self.state = new_state

    change_animation(self.entity, self.entity:get_tag(), self.state.name)
    player:flip(player.sprite.flip)
    self.state:on_enter(self)

  end
end

function Player:change_health(change)
  self.health.current_health = self.health.current_health + change
  local current_time = get_ticks()
  for heart_num = 0, self.health.max_health - 1 do
    local heart = self.hearts[heart_num]
    if heart_num < self.health.current_health then
      heart:heal(current_time)
    else
      heart:hurt(current_time)
    end
  end
end

function Player:flip(flip)
  self.sprite.flip = flip

  if flip then
    self.collider.offset.x =
      (self.sprite.width - self.collider_roffset - self.collider.width)
    self.hitbox.offset.x =
      (self.sprite.width - self.hitbox_roffset - self.hitbox.width)
  else
    self.collider.offset.x = self.collider_roffset
    self.hitbox.offset.x = self.hitbox_roffset
  end
end

-- Check if player is stuck in a state
function Player:stuck_on_state(current_time)
  local stuck = false

  if self.state.name == player_states.dash.name then
    stuck = ((current_time - self.dash_start_time) < player_states.dash.duration)
  elseif self.state.name == player_states.attack.name then
    stuck = ((current_time - self.attack_start_time) < player_states.attack.duration)
  elseif self.state.name == player_states.hit.name then
    stuck = ((current_time - self.hit_start_time) < player_states.hit.duration)
  end

  return stuck
end

-- Initialize player
function Player:init(entity)
  self.entity = entity
  self.rigid_body = entity:get_rigid_body()
  self.transform = entity:get_transform()
  self.sprite = entity:get_sprite()
  self.collider = entity:get_box_collider()
  self.hitbox = entity:get_hit_box()
  self.health = entity:get_health()
  self.hearts = {
    [0] = {},
  }

  self.hitbox_roffset = self.hitbox.offset.x
  self.collider_roffset = self.collider.offset.x
end

-- Update player
function Player:update()
  local current_time = get_ticks()

  -- If the player is not dashing or hit
  if not self:stuck_on_state(current_time) then
    self.rigid_body.velocity.x = 0
    
    -- Handle movement
    if is_action_active("move_left") then
      self.rigid_body.velocity.x = self.rigid_body.velocity.x -
        (player_states.run.speed * constants.pixels_per_meter)

      self:flip(true)

      if self.rigid_body.on_ground then
        self:change_state(player_states.run)
      end

    elseif is_action_active("move_right") then
      self.rigid_body.velocity.x = self.rigid_body.velocity.x +
        (player_states.run.speed * constants.pixels_per_meter)

      self:flip(false)

      if self.rigid_body.on_ground then
        self:change_state(player_states.run)
      end

    end

    -- Handle fall
    if self.rigid_body.velocity.y > 0.01 then
      if self.can_wall_grab then
        self:change_state(player_states.wall_grab)
      elseif self.can_double_jump or
        ((current_time - self.double_jump_start_time) >= player_states.double_jump.duration) then
        self:change_state(player_states.fall)
      end
    end

    -- Handle jump
    if is_action_active("jump") then
      if self.can_jump and self.rigid_body.on_ground then
        self:change_state(player_states.jump)
      elseif ((current_time - self.jump_start_time) >= player_states.double_jump.cooldown) and
        self.can_double_jump and not self.rigid_body.on_ground then
        self:change_state(player_states.double_jump)
      end
    end

    -- Handle dash
    if is_action_active("dash") and ((current_time - self.dash_finish_time) >=
      player_states.dash.cooldown) then
      self:change_state(player_states.dash)

    -- Handle attack
    elseif is_action_active("attack") and ((current_time - self.attack_finish_time) >=
      player_states.attack.cooldown) then
      self:change_state(player_states.attack)
    

    -- Handle idle
    elseif self.rigid_body.velocity.x <= 0.01 and
      self.rigid_body.velocity.x >= -0.01 and
      self.rigid_body.velocity.y <= 0.01 and
      self.rigid_body.velocity.y >= -0.01 then
      self:change_state(player_states.idle)
    end
  else
    -- States consistency
    if self.state.on_update then
      self.state:on_update(self)
    end
  end
end

-- Handle collision
function Player:on_collision(other)
  local is_enemy = str_contains(other:get_tag(), "enemy")
  if (is_enemy or
    str_contains(other:get_tag(), "trap")) and
    self.state.name ~= player_states.hit.name and
    self.state.name ~= player_states.dash.name then
    if is_enemy then
      self:change_health(-1)
    else
      self:change_health(-2)
    end
    self:change_state(player_states.hit)

  elseif other:get_tag() == "floor" then
    if check_collision_dir(self.entity, other, "up") then
      self.can_jump = true
      self.can_double_jump = true
      self.rigid_body.on_ground = true
    elseif check_collision_dir(self.entity, other, "left") or
      check_collision_dir(self.entity, other, "right") then
      self.can_wall_grab = true
      self.rigid_body.on_ground = true
    end

  elseif other:get_tag() == "platform" and not is_action_active("move_down") then
    if check_collision_dir(self.entity, other, "up") then
      self.can_jump = true
      self.can_double_jump = true
      self.rigid_body.on_ground = true

      local other_transform = other:get_transform()
      self.transform.position.y = other_transform.position.y -
        self.sprite.height * self.transform.scale.y
      self.rigid_body.velocity.y = 0.0
    end
  end
end


function Player:on_hit(other)
  if str_contains(other:get_tag(), "enemy") then
    local enemy = enemies[other:get_id()]
    enemy:hurt(self.hitbox.damage, self.sprite.flip)
  end

  if (self.sprite.flip) then
    self.rigid_body.sum_forces.x = self.rigid_body.sum_forces.x +
      player_states.attack.bounce * constants.pixels_per_meter
  else
    self.rigid_body.sum_forces.x = self.rigid_body.sum_forces.x +
      -player_states.attack.bounce * constants.pixels_per_meter
  end
end

-- Global player instance
player = Player

-- Script functions
function awake()
  player:init(this)
end

function update()
  player:update()
end

function on_collision(other)
  player:on_collision(other)
end

function on_hit(other)
  player:on_hit(other)
end