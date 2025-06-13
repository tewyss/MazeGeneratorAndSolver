#include "EnumUtilities.h"
#include "Maze.h"

Viewport Maze::computeViewport(const sf::RenderWindow &window) const {
  auto wSize = window.getSize();
  float cWidth = float(wSize.x) / width;
  float cHeight = float(wSize.y) / height;
  float cell = std::min(cWidth, cHeight);
  float totalW = cell * width;
  float totalH = cell * height;
  float offX = (wSize.x - totalW) / 2.f;
  float offY = (wSize.y - totalH) / 2.f;

  return {cell, offX, offY};
}

sf::Color Maze::cellColor(int col, int row) const {
  int v = maze[row][col];
  if (v == toUnderlying(CellType::WALL)) {
    return sf::Color::Black;
  } else if (v == toUnderlying(CellType::SOLUTION)) {
    return sf::Color::Green;
  } else if (solVisited[row][col]) {
    return sf::Color(100, 100, 100);
  } else {
    return sf::Color::White;
  }
}

// allocates vertexes and then only call draw so we dont have to call draw on
// every vertex
void Maze::buildVA(const sf::RenderWindow &window,
                   sf::VertexArray &verArr) const {
  verArr = sf::VertexArray(sf::Quads, width * height * 4);
  std::size_t idx = 0;

  auto viewport = computeViewport(window);

  for (int row = 0; row < height; ++row) {
    for (int col = 0; col < width; ++col) {
      sf::Color color = cellColor(col, row);

      // computes coordints of 4 vertex
      sf::Vector2f p0(viewport.offX + col * viewport.cell,
                      viewport.offY + row * viewport.cell); // left up
      sf::Vector2f p1(viewport.offX + (col + 1) * viewport.cell,
                      viewport.offY + row * viewport.cell); // right up
      sf::Vector2f p2(viewport.offX + (col + 1) * viewport.cell,
                      viewport.offY + (row + 1) * viewport.cell); // right down
      sf::Vector2f p3(viewport.offX + col * viewport.cell,
                      viewport.offY + (row + 1) * viewport.cell); // left down

      // filling it up
      verArr[idx + 0] = sf::Vertex(p0, color);
      verArr[idx + 1] = sf::Vertex(p1, color);
      verArr[idx + 2] = sf::Vertex(p2, color);
      verArr[idx + 3] = sf::Vertex(p3, color);
      idx += 4;
    }
  }
}
void Maze::draw(sf::RenderWindow &window, const Point &current) const {
  draw(window);

  if (current.col >= 0 and current.col < width and current.row >= 0 and
      current.row < height) {
    auto viewport = computeViewport(window);

    sf::RectangleShape hl({viewport.cell, viewport.cell});
    hl.setPosition(viewport.offX + current.col * viewport.cell,
                   viewport.offY + current.row * viewport.cell);
    hl.setFillColor(sf::Color::Red);
    window.draw(hl);
  }
}
// temporary path for Wilson algorithm
void Maze::drawTempPath(sf::RenderWindow &window,
                        const std::vector<Point> &walk) const {
  auto vp = computeViewport(window);
  sf::RectangleShape cell({vp.cell, vp.cell});
  cell.setFillColor(sf::Color(200, 50, 50, 150));

  for (auto &p : walk) {
    cell.setPosition(vp.offX + p.col * vp.cell, vp.offY + p.row * vp.cell);
    window.draw(cell);
  }
}

void Maze::draw(sf::RenderWindow &window) const {
  sf::VertexArray verArr;
  buildVA(window, verArr);
  window.draw(verArr);
}