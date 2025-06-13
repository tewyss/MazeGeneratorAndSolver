#include "EnumUtilities.h"
#include "Maze.h"

int Maze::manhattanDistance(const Point &first, const Point &second) const {
  return std::abs(first.row - second.row) + std::abs(first.col - second.col);
}

void Maze::solveAStarMaze(sf::RenderWindow &window) {
  const int ANIMATE_THRESHOLD = 101 * 101;
  bool animate = (width * height <= ANIMATE_THRESHOLD);

  resetMazePath();
  resetSolveVisited();

  const Point start{1, 1};
  const Point goal{width - 2, height - 2};
  const int infinity = std::numeric_limits<int>::max();

  std::priority_queue<AStarNode> prioQu;
  std::vector<std::vector<int>> costFromStart(
      height, std::vector<int>(width, infinity));
  std::vector<std::vector<Point>> cameFrom(height,
                                           std::vector<Point>(width, {-1, -1}));

  costFromStart[start.row][start.col] = 0;
  int initEstimatedCost = manhattanDistance(start, goal);
  prioQu.emplace(start, 0, initEstimatedCost);

  while (not prioQu.empty() and window.isOpen()) {
    pollWindowEvents(window);

    AStarNode currentNode = prioQu.top();
    prioQu.pop();
    Point current = currentNode.position;
    setSolveVisited(current.col, current.row);

    if (current == goal) {
      break;
    }

    for (auto &neighbor : getSolveNeighbors(current.col, current.row)) {
      int indicativeCost = costFromStart[current.row][current.col] + 1;
      if (indicativeCost < costFromStart[neighbor.row][neighbor.col]) {
        costFromStart[neighbor.row][neighbor.col] = indicativeCost;
        cameFrom[neighbor.row][neighbor.col] = current;

        int estimatedCost = indicativeCost + manhattanDistance(neighbor, goal);
        prioQu.emplace(neighbor, indicativeCost, estimatedCost);
      }
    }
    if (animate) {
      pollWindowEvents(window);
      window.clear(sf::Color::Black);
      draw(window);
      draw(window, current);
      window.display();
      sf::sleep(sf::milliseconds(20));
    }
  }

  reconstructAndAnimatePath(window, start, goal, cameFrom);

  if (window.isOpen()) {
    window.clear(sf::Color::Black);
    draw(window);
    window.display();
  }
}
