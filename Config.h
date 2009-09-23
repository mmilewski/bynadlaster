#ifndef __CONFIG_H_INCLUDED_H__
#define __CONFIG_H_INCLUDED_H__

#include "StdAfx.h"


class Config {
public:
  explicit Config() {
    Update();
  }

  bool Boolean(const std::string& var_name);
  int Int(const std::string& var_name);
  double Double(const std::string& var_name);
  std::string String(const std::string& var_name);
  void Update();

  static void RegisterInLua(lua_State* lua) {
    luabind::module(lua) [
			  luabind::class_<Config>("Config")
			  .def(luabind::constructor<>())
			  .def("Boolean", &Config::Boolean)
			  .def("Int", &Config::Int)
			  .def("Double", &Config::Double)
			  .def("String", &Config::String)
			  ];
  }


protected:
  void UpdateGlobalConstants();


};

typedef boost::shared_ptr<Config> ConfigPtr;

#endif
