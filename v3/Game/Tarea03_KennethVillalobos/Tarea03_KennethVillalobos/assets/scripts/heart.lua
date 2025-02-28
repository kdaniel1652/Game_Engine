-- Heart states
heart_states = {
  hurted = {
    name = "hurted"
  },

  hurting = {
    name = "hurting"
  },

  healed = {
    name = "healed"
  },

  healing = {
    name = "healing"
  }
}

Heart = {
  index = 0,
  entity = nil,
  state = heart_states.healed,

  state_start_time = 0,
  state_duration = 0
}

-- Heart constructor
function Heart:new(o, heart_num, entity)
  o = o or {}
  setmetatable(o, self)
  self.__index = self
  o.index = heart_num
  o.entity = entity
  o.state = heart_states.healed
  o.state_start_time = 0
  o.state_duration = 700
  return o
end

function Heart:hurt(current_time)
  if self.state.name ~= heart_states.hurted.name and
    self.state.name ~= heart_states.hurting.name then
    self.state = heart_states.hurting
    self.state_start_time = current_time
    change_animation(self.entity, self.entity:get_tag(), self.state.name)
  end
end

function Heart:heal(current_time)
  if self.state.name ~= heart_states.healed.name and
    self.state.name ~= heart_states.healing.name then
    self.state = heart_states.healing
    self.state_start_time = current_time
    change_animation(self.entity, self.entity:get_tag(), self.state.name)
  end
end

function get_next_heart()
  player.current_heart = player.current_heart + 1
  if player.current_heart >= player.health.max_health then
    player.current_heart = player.current_heart % player.health.max_health
  end
end

function awake()
  local heart = Heart:new(nil, player.current_heart, this)
  player.hearts[player.current_heart] = heart
  get_next_heart()
end

function update()
  local current_time = get_ticks()
  heart = player.hearts[player.current_heart]
  
  if heart.state.name == heart_states.hurting.name or
    heart.state.name == heart_states.healing.name then

    if (current_time - heart.state_start_time) >= heart.state_duration then
      if heart.state.name == heart_states.hurting.name then
        heart.state = heart_states.hurted
      else
        heart.state = heart_states.healed
      end
      change_animation(this, this:get_tag(), heart.state.name)
    end
  end

  get_next_heart()
end