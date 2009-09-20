#include "Engine.h"
#include "App.h"

int main() {
  try {
    Engine::Get().Init();
    App app;
    app.Run();
  }
  catch (std::exception& e) {
    std::cout << e.what() << "\n";
  }
  catch (...) {
    std::cout << "Unknown error\n";
  }

}
