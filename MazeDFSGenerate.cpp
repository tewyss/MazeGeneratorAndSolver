#include "EnumUtilities.h"
#include "Maze.h"

// generate using iterative DFS
void Maze::generateDFSMaze(sf::RenderWindow &window) {
  const int ANIMATE_THRESHOLD = 101 * 101;
  bool animate = (width * height <= ANIMATE_THRESHOLD);

  resetGenerateVisited();
  std::stack<Point> stack;
  stack.push({1, 1});
  setGenerateVisited(1, 1);
  maze[1][1] = toUnderlying(CellType::PATH);

  auto &engine = obtainEngine();

  while (not stack.empty() and window.isOpen()) {
    pollWindowEvents(window);

    auto [col, row] = stack.top();
    auto neighbors = getGenerateNeighbors(col, row);
    std::shuffle(neighbors.begin(), neighbors.end(), engine);

    bool moved = false;
    for (auto &neighbor : neighbors) {
      if (not isGenerateVisited(neighbor.col, neighbor.row)) {
        removeWallBetween(col, row, neighbor.col, neighbor.row);
        stack.push(neighbor);
        setGenerateVisited(neighbor.col, neighbor.row);
        maze[neighbor.row][neighbor.col] = toUnderlying(CellType::PATH);
        moved = true;

        if (animate) {
          window.clear(sf::Color::Black);
          draw(window, neighbor);
          window.display();
          sf::sleep(sf::milliseconds(20));
        }
        break;
      }
    }

    if (not moved) {
      stack.pop();
      if (animate and not stack.empty()) {
        window.clear(sf::Color::Black);
        draw(window, stack.top());
        window.display();
        sf::sleep(sf::milliseconds(20));
      }
    }
  }

  window.clear(sf::Color::Black);
  draw(window);
  window.display();
}