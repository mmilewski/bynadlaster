#include "Engine.h"
#include "Config.h"


int Config::Int(const std::string& var_name) {
  lua_State* lua = Engine::Get().Scripts()->LuaState();
  lua_getglobal(lua, ("CONFIG_" + var_name).c_str());
  if (!lua_isnumber(lua, -1)) {
    std::cerr << std::string("Config::Int expected integer value when fetchign variable ") + "CONFIG_" + var_name + "\n";
    return 0;
  }
  return lua_tointeger(lua, -1);
}


double Config::Double(const std::string& var_name) {
  lua_State* lua = Engine::Get().Scripts()->LuaState();
  lua_getglobal(lua, ("CONFIG_" + var_name).c_str());
  if (!lua_isnumber(lua, -1)) {
    std::cerr << std::string("Config::Int expected integer value when fetchign variable ") + "CONFIG_" + var_name + "\n";
    return 0;
  }
  return lua_tonumber(lua, -1);
}


std::string Config::String(const std::string& var_name) {
  lua_State* lua = Engine::Get().Scripts()->LuaState();
  lua_getglobal(lua, ("CONFIG_" + var_name).c_str());
  if (!lua_isstring(lua, -1)) {
    std::cerr << std::string("Config::Int expected integer value when fetchign variable ") + "CONFIG_" + var_name + "\n";
    return 0;
  }
  return lua_tostring(lua, -1);
}


void Config::Update() {
  luaL_dofile(Engine::Get().Scripts()->LuaState(), "scripts/main_config.lua");
  UpdateGlobalConstants();
}


// configuration in lua was coded later, so we have some global vars
// to update (Constants.h)
void Config::UpdateGlobalConstants() {
  g_tiles_on_screen_in_x = Config::Int("TilesOnScreenInX");
  g_tiles_on_screen_in_y = Config::Int("TilesOnScreenInY");
  g_max_map_width  = Config::Int("MaxMapWidth");
  g_max_map_height = Config::Int("MaxMapHeight");
  g_max_players = Config::Int("MaxPlayers");
  g_bomb_player_has_at_start = Config::Int("BombPlayerHasAtStart");
  g_fire_range_player_has_at_start = Config::Int("FireRangePlayerHasAtStart");
  g_bomb_time_to_live = Config::Double("BombTimeToLive");
}
