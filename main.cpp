#include "App.h"
#include "EndScreen.h"

sf::VideoMode getWindowVideoMode(float scale);
void configureWindow(sf::RenderWindow &window);

int main() {
  sf::VideoMode mode = getWindowVideoMode(0.8f);
  sf::RenderWindow window(mode, "Maze Generator and Solver",
                          sf::Style::Default);
  configureWindow(window);

  ConfigSettings cfg;
  if (not runMenus(window, cfg)) {
    return 0;
  }

  Maze maze = buildAndGenerateMaze(window, cfg);
  runGenerationCycle(window, maze, cfg);
  runEndScreenLoop(window, maze, cfg);

  return 0;
}
