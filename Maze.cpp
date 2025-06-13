#include "Maze.h"

const std::array<Point, 4> Maze::generateDirections = {Point(0, -2), // up
                                                       Point(0, 2),  // down
                                                       Point(-2, 0), // left
                                                       Point(2, 0)}; // right

const std::array<Point, 4> Maze::solveDirections = {Point(0, -1), // up
                                                    Point(0, 1),  // down
                                                    Point(-1, 0), // left
                                                    Point(1, 0)}; // right

// consructor
Maze::Maze(int width, int height) : width(width), height(height) {
  if (width < 5 or height < 5) {
    throw std::invalid_argument("Maze dimensions must be at least 5x5!");
  }
  maze.resize(height, std::vector<int>(width, 1));
  genVisited.resize(height, std::vector<bool>(width, false));
  solVisited.resize(height, std::vector<bool>(width, false));
}
