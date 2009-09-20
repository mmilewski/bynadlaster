#ifndef __ANIMATED_TEXT_H_INCLUDED__
#define __ANIMATED_TEXT_H_INCLUDED__

#include "StdAfx.h"
#include "NonEntity.h"


class AnimatedText : public NonEntity {
public:
  virtual ~AnimatedText() { }

  void SetText(const std::string& text) {
    m_text = text;
  }

  const std::string& Text() const {
    return m_text;
  }


public:
  virtual void DoDraw() const  { }
  virtual void DoUpdate(double /* dt */) { }

private:
  std::string m_text;
};

typedef boost::shared_ptr<AnimatedText> AnimatedTextPtr;



// needed if we want to subclass AnimatedText in LUA
class AnimatedText_BaseWrapper : public AnimatedText, public luabind::wrap_base {
public:
  void DoDraw() const {
    call<void>("Draw");
  }

  static void default_DoDraw(AnimatedText* base) {
    base->AnimatedText::DoDraw();
  }


  void DoUpdate(double dt) {
    call<void>("Update", dt);
  }

  static void default_DoUpdate(AnimatedText* base, double dt) {
    base->AnimatedText::DoUpdate(dt);
  }


  static void RegisterInLua(lua_State* lua) {
    luabind::module(lua) [
			  luabind::class_<AnimatedText, AnimatedText_BaseWrapper, AnimatedTextPtr>("AnimatedText")
			  .def(luabind::constructor<>())
			  .def("Draw", &AnimatedText::DoDraw, &AnimatedText_BaseWrapper::default_DoDraw)
			  .def("Update", &AnimatedText::DoUpdate, &AnimatedText_BaseWrapper::default_DoUpdate)
			  ];
  }

};




#endif
