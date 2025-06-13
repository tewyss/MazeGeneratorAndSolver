#include "Maze.h"

std::vector<Point> Maze::getGenerateNeighbors(int col, int row) const {
  std::vector<Point> neighbors;

  for (const auto &dir : generateDirections) {
    int newCol = col + dir.col;
    int newRow = row + dir.row;

    if (isValidGenerateMove(newCol, newRow)) {
      neighbors.emplace_back(newCol, newRow);
    }
  }
  return neighbors;
}

std::vector<Point> Maze::getSolveNeighbors(int col, int row) const {
  std::vector<Point> neighbors;

  for (const auto &dir : solveDirections) {
    int newCol = col + dir.col;
    int newRow = row + dir.row;

    if (isValidSolveMove(newCol, newRow)) {
      neighbors.emplace_back(newCol, newRow);
    }
  }
  return neighbors;
}

std::vector<Point> Maze::getWilsonNeighbors(int col, int row) const {
  std::vector<Point> neighbors;

  for (const auto &dir : generateDirections) {
    int newCol = col + dir.col;
    int newRow = row + dir.row;

    if (newRow >= 1 and newRow < height - 1 and newCol >= 1 and
        newCol < width - 1) {
      neighbors.emplace_back(newCol, newRow);
    }
  }
  return neighbors;
}
