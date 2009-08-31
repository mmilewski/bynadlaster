#ifndef __LUA_H_INCLUDED__
#define __LUA_H_INCLUDED__

#include <boost/noncopyable.hpp>
#include "PlayerAction.h"
#include "StdAfx.h"

#include <lua5.1/lua.hpp>
#include <luabind/luabind.hpp>


class Lua : boost::noncopyable {
public:
  explicit Lua();
  ~Lua();

  static Lua& Get() {
    static Lua s_instance;
    return s_instance;    
  }

  TexCoords GetPlayerSprite(PT::PlayerType type, Direction direction, bool is_dying, double duration) const;
  void Reset();

protected:
  void Init();
  void Destroy();
  void LoadFiles();
  void ExportModules();
  void LoadTypes();

private:
  lua_State* m_lua_state;

};


#endif
