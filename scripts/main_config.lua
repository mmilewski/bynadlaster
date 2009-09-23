print('main_config.lua: [ LOADING ]');

-- All global configuration goes here. This should be a list of global
-- variables.

CONFIG_TilesOnScreenInX = 23; -- at least 6 (border)
CONFIG_TilesOnScreenInY = 23; -- at least 4 (border)

CONFIG_MaxMapWidth  = CONFIG_TilesOnScreenInX - 6;
CONFIG_MaxMapHeight = CONFIG_TilesOnScreenInY - 4;

CONFIG_MaxPlayers = 2;

CONFIG_BombPlayerHasAtStart = 3;
CONFIG_FireRangePlayerHasAtStart = 2;

CONFIG_BombTimeToLive = 1.0;  -- (in seconds)

CONFIG_RenderAABBs = true;   -- whether or not to render aabbs

print('main_config.lua: [ LOADED ]');
