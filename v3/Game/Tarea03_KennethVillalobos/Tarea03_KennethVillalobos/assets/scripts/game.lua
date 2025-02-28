game = {
	scenes = {
		[0] =
		{id = "level_01",	path = "./assets/scripts/test.lua"}
	},

	assets = {
		[0] =
		{type = "texture",	id = "terrain_img",		path = "./assets/img/terrain.png"},
		{type = "texture",	id = "mask_idle",			path = "./assets/img/mask_idle.png"},
		{type = "texture",	id = "mask_run",			path = "./assets/img/mask_run.png"},
		{type = "texture",	id = "mask_jump",			path = "./assets/img/mask_jump.png"},
		{type = "texture",	id = "mask_djump",		path = "./assets/img/mask_djump.png"},
		{type = "texture",	id = "mask_fall",			path = "./assets/img/mask_fall.png"},
		{type = "texture",	id = "mask_wall",			path = "./assets/img/mask_wall.png"},
		{type = "texture",	id = "mask_dash",			path = "./assets/img/mask_dash.png"},
		{type = "texture",	id = "mask_attack",		path = "./assets/img/mask_attack.png"},
		{type = "texture",	id = "mask_hit",			path = "./assets/img/mask_hit.png"},
		{type = "texture",	id = "heart_full",		path = "./assets/img/heart_full.png"},
		{type = "texture",	id = "heart_empty",		path = "./assets/img/heart_empty.png"},
		{type = "texture",	id = "heart_healing",	path = "./assets/img/heart_healing.png"},
		{type = "texture",	id = "heart_hurting",	path = "./assets/img/heart_hurting.png"},
		{type = "texture",	id = "rino_run",			path = "./assets/img/rino_run.png"},
		{type = "texture",	id = "rino_hit",			path = "./assets/img/rino_hit.png"},
		{type = "texture",	id = "bird_run",			path = "./assets/img/bird_run.png"},
		{type = "texture",	id = "bird_hit",			path = "./assets/img/bird_hit.png"},
		{type = "texture",	id = "bunny_run",			path = "./assets/img/bunny_run.png"},
		{type = "texture",	id = "bunny_jump",		path = "./assets/img/bunny_jump.png"},
		{type = "texture",	id = "bunny_fall",		path = "./assets/img/bunny_fall.png"},
		{type = "texture",	id = "bunny_hit",			path = "./assets/img/bunny_hit.png"},
		{type = "texture",	id = "bat_run",				path = "./assets/img/bat_run.png"},
		{type = "texture",	id = "bat_hit",				path = "./assets/img/bat_hit.png"},
		{type = "texture",	id = "saw_run",				path = "./assets/img/saw.png"},
		{type = "font",			id = "game_font",			path = "./assets/fonts/game_font.ttf",										size = 20},
		{type = "font",			id = "chinese_font",	path = "./assets/fonts/zpix.ttf",													size = 12},
		{type = "song",			id = "main_song",			path = "./assets/songs/I_Like_The_Way_You_Kiss_Me.mp3",		volume = 60},
		{type = "song",			id = "end_song",			path = "./assets/songs/Saturday_In_The_Park.mp3",					volume = 60},
		{type = "sound",		id = "enemy_hit_1",		path = "./assets/sounds/enemy_killed_01.wav",							volume = 100},
		{type = "sound",		id = "enemy_hit_2",		path = "./assets/sounds/enemy_killed_02.wav",							volume = 100},
		{type = "sound",		id = "enemy_hit_3",		path = "./assets/sounds/enemy_killed_03.wav",							volume = 100}
  }
}

constants = {
	pixels_per_meter = 64
}