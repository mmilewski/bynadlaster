#include "Lua.h"

Lua::Lua() {
  Init();
}

Lua::~Lua() {
  lua_close(m_lua_state);  
}

TexCoords Lua::GetPlayerSprite(PT::PlayerType type, Direction direction, bool is_dying, double duration) const {
  try {
    return luabind::call_function<TexCoords>(m_lua_state, "GetPlayerSprite", type, direction, is_dying, duration);
  }
  catch (luabind::error& e) {
    std::cerr << "An error occured while calling Lua::GetPlayerSprite: " << e.what() << "\n";
  }
  catch(luabind::cast_failed& e) {
    std::cerr << "An error occured while calling Lua::GetPlayerSprite: " << e.what() << "\n";
  }
  return TexCoords(0,0,0,0); // show nothing in case of errors
}

void Lua::Reset() {
  lua_close(m_lua_state);
  Init();
}

void Lua::Init() {
  m_lua_state = lua_open();

  luaopen_base(m_lua_state);
  luaopen_math(m_lua_state);
  
  luabind::open(m_lua_state);
  
  ExportModules();
  LoadTypes();
  LoadFiles();
}

void Lua::LoadFiles() {
  luaL_dofile(m_lua_state, "scripts/player.lua");
}

void Lua::ExportModules() {
  luabind::module(m_lua_state) [
				luabind::class_<TexCoords>("TexCoords")
				.def(luabind::constructor<double, double, double, double>())
				.def_readwrite("left", &TexCoords::left)
				.def_readwrite("bottom", &TexCoords::bottom)
				.def_readwrite("width", &TexCoords::width)
				.def_readwrite("height", &TexCoords::height)
				];

  luabind::module(m_lua_state) [
				luabind::class_<Direction>("Direction")
				.def(luabind::constructor<double, double>())
				.def("Set", &Direction::Set)
				.def("SetX", &Direction::SetX)
				.def("SetY", &Direction::SetY)
				.def("GetX", &Direction::GetX)
				.def("x", &Direction::x)
				.def("y", &Direction::y)
				];
}


void Lua::LoadTypes() {
  FT::RegisterInLua(m_lua_state);
  PT::RegisterInLua(m_lua_state);
  PA::RegisterInLua(m_lua_state);
}
