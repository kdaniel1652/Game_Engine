-- Level 01 elements table
scene = {
  -- Entities table
  entities = {
    [0] =
    {
      -- Text
      tag = "Text",
      components = {
        text = {
          assetId = "chinese_font",
          label = "我喜欢你，小文",
          r = 255,
          g = 255,
          b = 255,
          a = 255
        },

        transform = {
          position = {x = 20.0, y = 20.0},
          scale = {x = 4.0, y = 4.0},
          rotation = 0.0
        },

        cameraFollow = {}
      }
    }
  }
}