#ifndef __LUA_H_INCLUDED__
#define __LUA_H_INCLUDED__

#include "PlayerAction.h"
#include "StdAfx.h"

#include <lua5.1/lua.hpp>
#include <luabind/luabind.hpp>


class Lua {
public:
  explicit Lua();
  ~Lua();

  TexCoords GetPlayerSprite(PT::PlayerType type, Direction direction, bool is_dying, double duration) const;
  void Reset();

  void Export();
  void Load();

protected:
  void Init();
  void Destroy();
  void ExportModules();
  void ExportTypes();
  void LoadFiles();
  void LoadFactories();

private:
  lua_State* m_lua_state;

};

typedef boost::shared_ptr<Lua> LuaPtr;


#endif
