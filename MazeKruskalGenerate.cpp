#include "DisjointSetUnion.h"
#include "EnumUtilities.h"
#include "Maze.h"

void Maze::generateKruskalMaze(sf::RenderWindow &window) {
  const int ANIMATE_THRESHOLD = 101 * 101;
  bool animate = (width * height <= ANIMATE_THRESHOLD);

  resetGenerateVisited();
  walls = createWalls();

  DisjointSetUnion dsu(width * height);
  auto &engine = obtainEngine();
  std::shuffle(walls.begin(), walls.end(), engine);

  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      maze[row][col] = toUnderlying(CellType::WALL);
    }
  }

  for (int row = 1; row < height; row += 2)
    for (int col = 1; col < width; col += 2)
      maze[row][col] = toUnderlying(CellType::PATH);

  for (const Wall &wall : walls) {
    pollWindowEvents(window);

    int first = getId(wall.firstCell);
    int second = getId(wall.secondCell);
    if (dsu.findSet(first) not_eq dsu.findSet(second)) {
      dsu.unionSets(first, second);
      removeWallBetween(wall.firstCell.col, wall.firstCell.row,
                        wall.secondCell.col, wall.secondCell.row);

      if (animate) {
        window.clear(sf::Color::Black);
        draw(window, wall.firstCell);
        window.display();
        sf::sleep(sf::milliseconds(40));
      }
    }
  }

  window.clear(sf::Color::Black);
  draw(window);
  window.display();
}