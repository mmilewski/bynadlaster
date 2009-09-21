#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <boost/noncopyable.hpp>
#include "Lua.h"
#include "NonEntityFactory.h"
#include "Renderer.h"
#include "Config.h"


// This is due to problem /w using singletons. This class should be
// the only one Singleton in the game. All other "singletons" should
// be accessible through Engine (i.e. Engine::Scripts()).
//
// This allows to specify correct order of destruction
class Engine : boost::noncopyable {
public:
  void Init() {
    // The order is important. 
    m_lua.reset(new Lua()); // (!) THIS GOES FIRST (!)
    m_non_entity_factory.reset(new NonEntityFactory::NonEntityFactory());
    m_renderer.reset(new Renderer::Renderer());
    m_config.reset(new Config::Config());

    m_lua->Load();// (!) THIS GOES LAST (!)
  }
  

  
  ~Engine() {
    // Order of destruction is improtant (lua should be destroyed at
    // the end - we often create objects (prototypes) in scripts and
    // register it in factories. 

    m_non_entity_factory.reset();
    m_renderer.reset();
    m_config.reset();

    m_lua.reset(); // (!) THIS IS DESTROYED AT THE END (!)
  }

  static Engine& Get() {
    static Engine s_instance;
    return s_instance;
  }

  LuaPtr Scripts() { 
    return m_lua; 
  }

  NonEntityFactoryPtr NonEntityFactory() {
    return m_non_entity_factory;
  }

  RendererPtr Renderer() {
    return m_renderer;
  }

  ConfigPtr Config() {
    return m_config;
  }
  

public:
  static void RegisterInLua(lua_State* lua) {
    luabind::module(lua) [
			  luabind::class_<Engine>("Engine")
			  .scope [
				  luabind::def("Get", &Engine::Get)
				  ]
			  .def("NonEntityFactory", &Engine::NonEntityFactory)
			  .def("Renderer", &Engine::Renderer)
			  .def("Config", &Engine::Config)
			  ];
  }


private:
  LuaPtr m_lua;
  NonEntityFactoryPtr m_non_entity_factory;
  RendererPtr m_renderer;
  ConfigPtr m_config;

};


#endif
