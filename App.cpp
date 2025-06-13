#include "App.h"
// function for pause between generation, adding cycles and solving
void responsivePause(sf::RenderWindow &window, Maze &maze, float secs) {
  sf::Clock clock;
  while (clock.getElapsedTime().asSeconds() < secs and window.isOpen()) {
    sf::Event ev;
    while (window.pollEvent(ev))
      if (ev.type == sf::Event::Closed)
        window.close();

    window.clear(sf::Color::Black);
    maze.draw(window);
    window.display();
  }
}

bool runMenus(sf::RenderWindow &window, ConfigSettings &outCfg) {
  while (window.isOpen()) {
    if (showMainMenu(window) == MenuResult::Exit) {
      return false;
    }

    auto cfgRes = showConfigureMenu(window, outCfg);
    if (cfgRes == ConfigResult::Exit) {
      return false;
    }
    if (cfgRes == ConfigResult::Start) {
      return true;
    }
  }
  return false;
}

Maze buildAndGenerateMaze(sf::RenderWindow &window, const ConfigSettings &cfg) {
  Maze maze(cfg.rows, cfg.cols);
  switch (cfg.genAlgo) {
  case Generation::DFS:
    maze.generateDFSMaze(window);
    break;
  case Generation::Kruskal:
    maze.generateKruskalMaze(window);
    break;
  case Generation::Wilson:
    maze.generateWilsonMaze(window);
    break;
  }
  return maze;
}

void applyCycles(sf::RenderWindow &window, Maze &maze, double point) {
  if (point > 0.0) {
    maze.addRandomCycles(window, point);
  }
}

void solveMaze(sf::RenderWindow &window, Maze &maze,
               const ConfigSettings &cfg) {
  switch (cfg.solveAlgo) {
  case Solve::DFS:
    maze.solveDFSMaze(window);
    break;
  case Solve::BFS:
    maze.solveBFSMaze(window);
    break;
  case Solve::AStar:
    maze.solveAStarMaze(window);
    break;
  }
}

bool handleReconfigure(sf::RenderWindow &window, ConfigSettings &cfg) {
  while (window.isOpen()) {
    auto res = showConfigureMenu(window, cfg);
    if (res == ConfigResult::Start)
      return true;
    if (res == ConfigResult::Back)
      return false;
  }
  return false;
}

void runGenerationCycle(sf::RenderWindow &window, Maze &maze,
                        const ConfigSettings &cfg) {
  responsivePause(window, maze, 2.0f);
  applyCycles(window, maze, cfg.cycleProbability);
  responsivePause(window, maze, 2.0f);
  solveMaze(window, maze, cfg);
}

// handling what users chooses after solved maze
void runEndScreenLoop(sf::RenderWindow &window, Maze &maze,
                      ConfigSettings &cfg) {
  while (window.isOpen()) {
    auto choice = showEndScreen(window, maze);
    if (choice == EndScreenResult::Exit)
      break;

    if (choice == EndScreenResult::Reconfigure) {
      if (not handleReconfigure(window, cfg)) {
        continue;
      }
      maze = buildAndGenerateMaze(window, cfg);
      runGenerationCycle(window, maze, cfg);
    }
  }
}