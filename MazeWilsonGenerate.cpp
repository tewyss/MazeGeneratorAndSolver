#include "EnumUtilities.h"
#include "Maze.h"

static void loopErase(std::vector<Point> &path, const Point &point) {
  auto loop = std::find(path.begin(), path.end(), point);
  if (loop not_eq path.end()) {
    path.erase(loop + 1, path.end());
  }
}

void Maze::generateWilsonMaze(sf::RenderWindow &window) {
  const int ANIMATE_THRESHOLD = 101 * 101;
  bool animate = (width * height < ANIMATE_THRESHOLD);

  resetMazeToWalls();
  resetGenerateVisited();
  auto &engine = obtainEngine();

  auto seeds = seedOddPoints();
  std::shuffle(seeds.begin(), seeds.end(), engine);

  Point initial = seeds.front();
  seeds.erase(seeds.begin());
  setGenerateVisited(initial.col, initial.row);
  maze[initial.row][initial.col] = toUnderlying(CellType::PATH);

  for (auto &start : seeds) {
    if (not window.isOpen() or isGenerateVisited(start.col, start.row)) {
      continue;
    }

    std::vector<Point> walk{start};
    while (not isGenerateVisited(walk.back().col, walk.back().row) and
           window.isOpen()) {
      pollWindowEvents(window);
      auto neighbors = getWilsonNeighbors(walk.back().col, walk.back().row);
      std::uniform_int_distribution<size_t> dist(0, neighbors.size() - 1);
      Point next = neighbors[dist(engine)];

      loopErase(walk, next);
      walk.emplace_back(next);

      if (animate) {
        window.clear(sf::Color::Black);
        draw(window);
        drawTempPath(window, walk);
        window.display();
        sf::sleep(sf::milliseconds(20));
      }
    }

    setGenerateVisited(walk[0].col, walk[0].row);
    maze[walk[0].row][walk[0].col] = toUnderlying(CellType::PATH);

    for (size_t i = 1; i < walk.size(); ++i) {
      const auto &first = walk[i - 1];
      const auto &second = walk[i];

      removeWallBetween(first.col, first.row, second.col, second.row);
      setGenerateVisited(second.col, second.row);

      maze[second.row][second.col] = toUnderlying(CellType::PATH);

      if (animate) {
        window.clear(sf::Color::Black);
        draw(window);
        drawTempPath(window, walk);
        draw(window, second);
        window.display();
        sf::sleep(sf::milliseconds(20));
      }
    }
  }

  if (window.isOpen()) {
    window.clear(sf::Color::Black);
    draw(window);
    window.display();
  }
}