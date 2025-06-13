#pragma once

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

enum class ConfigResult { Back, Start, Exit };

enum class Generation { DFS, Kruskal, Wilson };
enum class Solve { DFS, BFS, AStar };

struct ConfigSettings {
  int rows = 21;
  int cols = 21;
  Generation genAlgo = Generation::DFS;
  Solve solveAlgo = Solve::BFS;
  double cycleProbability = 0.0;
};

ConfigResult showConfigureMenu(sf::RenderWindow &window, ConfigSettings &out);
