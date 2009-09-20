#ifndef __NON_ENTITY_FACTOR_H_INCLUDED__
#define __NON_ENTITY_FACTOR_H_INCLUDED__

#include "StdAfx.h"
#include "NonEntity.h"
#include "AnimatedText.h"


class NonEntityFactory {
public:
  static NonEntityFactory Get() {
    static NonEntityFactory s_instance;
    return s_instance;
  }

  
  static void RegisterInLua(lua_State* lua) {
    AnimatedText_BaseWrapper::RegisterInLua(lua);

    luabind::module(lua) [
			  luabind::class_<NonEntityFactory, boost::shared_ptr<NonEntityFactory> >("NonEntityFactory")
			  .scope [
				  luabind::def("Get", &NonEntityFactory::Get)
				  ]
			  .def("RegisterAnimatedText", &NonEntityFactory::RegisterAnimatedText)
			  .def("AnimatedTextByName", &NonEntityFactory::AnimatedTextByName)
			  ];

    luaL_dofile(lua, "scripts/animated_text.lua");
  }


  void RegisterAnimatedText(const std::string& name, AnimatedTextPtr prototype) {
    m_animated_text_prototypes.insert(std::make_pair(name, prototype));
  }


  AnimatedTextPtr AnimatedTextByName(const std::string& name) const {
    std::map<std::string, AnimatedTextPtr>::const_iterator i = m_animated_text_prototypes.find(name);
    if (i == m_animated_text_prototypes.end()) {
      throw ExceptionNotFound("Can't find AnimatedText prototype by name '" + name + "'");
    }
    return i->second;
  }


private:
  std::map<std::string, AnimatedTextPtr> m_animated_text_prototypes;

};

typedef boost::shared_ptr<NonEntityFactory> NonEntityFactoryPtr;


#endif
