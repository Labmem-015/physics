#pragma once

namespace phys {

struct Config {
  std::string title = "Physics";
  int screen_width = 800;
  int screen_height = 600;
  int fps = 60;
};

extern Config config;

} // namespace phys