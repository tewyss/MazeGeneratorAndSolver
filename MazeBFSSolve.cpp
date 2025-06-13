#include "Maze.h"

void Maze::solveBFSMaze(sf::RenderWindow &window) {
  const int ANIMATE_THRESHOLD = 101 * 101;
  bool animate = (width * height <= ANIMATE_THRESHOLD);

  resetMazePath();
  resetSolveVisited();

  std::queue<Point> frontier;
  frontier.push({1, 1});
  setSolveVisited(1, 1);

  if (animate) {
    window.clear(sf::Color::Black);
    draw(window);
    draw(window, {1, 1});
    window.display();
  }

  std::vector<std::vector<Point>> parents(height,
                                          std::vector<Point>(width, {-1, -1}));
  bool found = false;

  while (not frontier.empty() and window.isOpen()) {
    pollWindowEvents(window);

    Point cur = frontier.front();
    frontier.pop();

    if (animate) {
      window.clear(sf::Color::Black);
      draw(window);
      draw(window, cur);
      window.display();
      sf::sleep(sf::milliseconds(20));
    }

    if (isEnd(cur.col, cur.row)) {
      found = true;
      break;
    }

    for (auto &neighbor : getSolveNeighbors(cur.col, cur.row)) {
      if (not isSolveVisited(neighbor.col, neighbor.row)) {
        setSolveVisited(neighbor.col, neighbor.row);
        parents[neighbor.row][neighbor.col] = cur;
        frontier.push(neighbor);

        if (animate) {
          window.clear(sf::Color::Black);
          draw(window);
          draw(window, neighbor);
          window.display();
          sf::sleep(sf::milliseconds(5));
        }
      }
    }
  }

  if (found) {
    reconstructAndAnimatePath(window, Point{1, 1}, Point{width - 2, height - 2},
                              parents);
  } else {
    std::cout << "No path found.\n";
  }

  window.clear(sf::Color::Black);
  draw(window);
  window.display();
}