#include "EnumUtilities.h"
#include "Maze.h"

static const int ANIMATE_THRESHOLD = 101 * 101;

void Maze::pollWindowEvents(sf::RenderWindow &window) {
  sf::Event ev;
  while (window.pollEvent(ev)) {
    if (ev.type == sf::Event::Closed)
      window.close();
  }
}

bool Maze::isValidGenerateMove(int col, int row) const {
  return col > 0 and col < width and row > 0 and row < height and
         maze[row][col] == toUnderlying(CellType::WALL);
}

bool Maze::isValidSolveMove(int col, int row) const {
  return col > 0 and col < width and row > 0 and row < height and
         maze[row][col] == toUnderlying(CellType::PATH);
}

void Maze::setGenerateVisited(int col, int row) {
  genVisited[row][col] = true;
}

bool Maze::isGenerateVisited(int col, int row) const {
  return genVisited[row][col];
}

void Maze::setSolveVisited(int col, int row) {
  solVisited[row][col] = true;
}

bool Maze::isSolveVisited(int col, int row) const {
  return solVisited[row][col];
}

std::mt19937 &Maze::obtainEngine() {
  static std::random_device randDev;
  static std::mt19937 engine(randDev());
  return engine;
}

bool Maze::isEnd(int col, int row) const {
  return (col == width - 2 and row == height - 2);
}

void Maze::resetSolveVisited() {
  for (auto &row : solVisited) {
    std::fill(row.begin(), row.end(), false);
  }
}

void Maze::resetGenerateVisited() {
  for (auto &row : genVisited) {
    std::fill(row.begin(), row.end(), false);
  }
}

void Maze::resetMazePath() {
  for (auto &row : maze) {
    for (auto &cell : row) {
      if (cell == toUnderlying(CellType::SOLUTION)) {
        cell = toUnderlying(CellType::PATH);
      }
    }
  }
}

void Maze::resetMazeToWalls() {
  for (auto &row : maze) {
    for (auto &cell : row) {
      cell = toUnderlying(CellType::WALL);
    }
  }
}

void Maze::removeWallBetween(int colCord1, int rowCord1, int colCord2,
                             int rowCord2) {
  int wallcol = colCord1 + (colCord2 - colCord1) / 2;
  int wallrow = rowCord1 + (rowCord2 - rowCord1) / 2;

  maze[wallrow][wallcol] = toUnderlying(CellType::PATH);
}

void Maze::addRandomCycles(sf::RenderWindow &window, double probability) {
  if (probability < 0.0 or probability > 1.0)
    throw std::invalid_argument("Probability must be between 0 and 1.");

  auto &engine = obtainEngine();
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  bool animate = (width * height <= ANIMATE_THRESHOLD);

  for (int row = 1; row < height - 1; ++row) {
    for (int col = 1; col < width - 1; ++col) {
      pollWindowEvents(window);

      if (maze[row][col] == int(CellType::WALL)) {
        bool horiz = (maze[row][col - 1] == toUnderlying(CellType::PATH) and
                      maze[row][col + 1] == toUnderlying(CellType::PATH));
        bool vert = (maze[row - 1][col] == toUnderlying(CellType::PATH) and
                     maze[row + 1][col] == toUnderlying(CellType::PATH));

        if ((horiz or vert) and dist(engine) < probability) {
          maze[row][col] = toUnderlying(CellType::PATH);

          if (animate and window.isOpen()) {
            window.clear(sf::Color::Black);
            draw(window, {col, row});
            window.display();
            sf::sleep(sf::milliseconds(10));
          }
        }
      }
    }
  }

  if (window.isOpen()) {
    window.clear(sf::Color::Black);
    draw(window);
    window.display();
  }
}

int Maze::getId(const Point &p) const {
  return p.row * width + p.col;
}

// for kruskal algortihm
std::vector<Wall> Maze::createWalls() const {
  std::vector<Wall> result;
  for (int row = 1; row < height - 1; row += 2) {
    for (int col = 1; col < width - 1; col += 2) {
      Point current(col, row);

      if (col + 2 < width - 1) {
        result.emplace_back(Wall{current, Point(col + 2, row)});
      }
      if (row + 2 < height - 1) {
        result.emplace_back(Wall{current, Point(col, row + 2)});
      }
    }
  }
  return result;
}

// used to seed points for Wilsons algortihm
std::vector<Point> Maze::seedOddPoints() const {
  std::vector<Point> seeds;
  for (int row = 1; row < height - 1; row += 2) {
    for (int col = 1; col < width - 1; col += 2) {
      if (not isGenerateVisited(col, row))
        seeds.emplace_back(col, row);
    }
  }
  return seeds;
}

void Maze::reconstructAndAnimatePath(
    sf::RenderWindow &window, const Point &start, const Point &goal,
    const std::vector<std::vector<Point>> &cameFrom) {
  const bool animate = (width * height <= ANIMATE_THRESHOLD);
  int col = goal.col;
  int row = goal.row;

  while (not(col == start.col and row == start.row) and window.isOpen()) {
    pollWindowEvents(window);
    maze[row][col] = toUnderlying(CellType::SOLUTION);

    if (animate) {
      window.clear(sf::Color::Black);
      draw(window);
      draw(window, {col, row});
      window.display();
      sf::sleep(sf::milliseconds(30));
    }

    Point parent = cameFrom[row][col];
    col = parent.col;
    row = parent.row;
  }

  maze[row][col] = toUnderlying(CellType::SOLUTION);
  if (animate) {
    pollWindowEvents(window);
    window.clear(sf::Color::Black);
    draw(window);
    draw(window, {col, row});
    window.display();
    sf::sleep(sf::milliseconds(50));
  }
}
