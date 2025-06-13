#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <stack>
#include <stdexcept>
#include <vector>

struct Viewport {
  float cell; // side‐length of each square cell
  float offX;
  float offY;
};

struct Point {
  int col; // horizontal index (from left to right)
  int row; // vertcal index (from top to bottom)

  Point(int c = 0, int r = 0) : col(c), row(r) {
  }
  bool operator==(const Point &other) const {
    return col == other.col and row == other.row;
  }
};

struct Wall {
  Point firstCell;  // representing the first cell of the wall
  Point secondCell; // representing the second cell of the wall
};

struct AStarNode {
  Point position;
  int costFromStart;
  int estimatedCost;
  AStarNode(const Point &pos, int cost, int estimate)
      : position(pos), costFromStart(cost), estimatedCost(estimate) {
  }

  // inverted operator for A* since prio_que by default arrange elems by largest but we waant elems to be arranged by smallest
  bool operator<(AStarNode const &other) const {
    return estimatedCost > other.estimatedCost;
  }
};

enum class CellType { PATH = 0, WALL = 1, SOLUTION = 2 };

class Maze {
private:
  int width = 0;
  int height = 0;

  std::vector<std::vector<int>> maze;
  std::vector<std::vector<bool>> genVisited;
  std::vector<std::vector<bool>> solVisited;

  static const std::array<Point, 4> generateDirections;
  static const std::array<Point, 4> solveDirections;

  std::vector<Wall> walls;

public:
  Maze(int width, int height);

  void generateDFSMaze(sf::RenderWindow &window);
  void generateKruskalMaze(sf::RenderWindow &window);
  void generateWilsonMaze(sf::RenderWindow &window);

  void solveBFSMaze(sf::RenderWindow &window);
  void solveDFSMaze(sf::RenderWindow &window);
  void solveAStarMaze(sf::RenderWindow &window);

  void addRandomCycles(sf::RenderWindow &window, double probability);
  void resetMazePath();
  void resetMazeToWalls();

  void draw(sf::RenderWindow &window, const Point &current) const;
  void drawTempPath(sf::RenderWindow &window,
                    const std::vector<Point> &walk) const;
  void draw(sf::RenderWindow &window) const;

private:
  std::vector<Wall> createWalls() const;

  bool isValidGenerateMove(int x, int y) const;
  bool isValidSolveMove(int x, int y) const;

  std::vector<Point> getGenerateNeighbors(int x, int y) const;
  std::vector<Point> getSolveNeighbors(int x, int y) const;
  std::vector<Point> getWilsonNeighbors(int col, int row) const;

  void setGenerateVisited(int x, int y);
  bool isGenerateVisited(int x, int y) const;

  void setSolveVisited(int x, int y);
  bool isSolveVisited(int x, int y) const;

  void resetSolveVisited();
  void resetGenerateVisited();

  void removeWallBetween(int x1, int y1, int x2, int y2);

  std::mt19937 &obtainEngine();

  bool isEnd(int x, int y) const;

  int getId(const Point &point) const;

  Viewport computeViewport(const sf::RenderWindow &window) const;

  void buildVA(const sf::RenderWindow &window, sf::VertexArray &out) const;

  sf::Color cellColor(int col, int row) const;

  void pollWindowEvents(sf::RenderWindow &window);

  std::vector<Point> seedOddPoints() const;

  int manhattanDistance(const Point &first, const Point &second) const;

  void
  reconstructAndAnimatePath(sf::RenderWindow &window, const Point &start,
                            const Point &goal,
                            const std::vector<std::vector<Point>> &cameFrom);
};
