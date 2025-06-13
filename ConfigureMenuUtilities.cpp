#include "ConfigureMenu.h"
#include "FontManager.h"

std::vector<sf::Text> makeMenuItems(const sf::Font &font) {
  return {
      sf::Text("", font, 24),     sf::Text("", font, 24),
      sf::Text("", font, 24),     sf::Text("", font, 24),
      sf::Text("", font, 24),     sf::Text("Start", font, 24),
      sf::Text("Back", font, 24),
  };
}

void positionMenuItems(std::vector<sf::Text> &items, sf::RenderWindow &window,
                       float startY, float spacing, float footerGap) {
  for (size_t i = 0; i < items.size(); ++i) {
    auto bounds = items[i].getLocalBounds();
    float x = (window.getSize().x - bounds.width) / 2.f;
    float y = startY + i * spacing + (i >= 5 ? footerGap : 0);
    items[i].setPosition(x, y);
  }
}

void drawMenu(sf::RenderWindow &window, std::vector<sf::Text> &items,
              size_t selected, sf::Text &title, sf::Text &warning,
              bool showWarning) {
  window.clear(sf::Color::Black);
  window.draw(title);
  for (size_t i = 0; i < items.size(); ++i) {
    if (i == selected) {
      auto bounds = items[i].getLocalBounds();
      sf::RectangleShape hl({bounds.width + 20, bounds.height + 10});
      hl.setPosition(items[i].getPosition() - sf::Vector2f(10, 5));
      hl.setFillColor({50, 50, 50, 150});
      window.draw(hl);
    }
    items[i].setFillColor(i == selected ? sf::Color::Yellow : sf::Color::White);
    window.draw(items[i]);
  }
  if (showWarning) {
    window.draw(warning);
  }
  window.display();
}

std::string genName(Generation generate) {
  switch (generate) {
  case Generation::DFS:
    return "DFS";
  case Generation::Kruskal:
    return "Kruskal";
  case Generation::Wilson:
    return "Wilson";
  }
  return "";
}

std::string solveName(Solve solve) {
  switch (solve) {
  case Solve::DFS:
    return "DFS";
  case Solve::BFS:
    return "BFS";
  case Solve::AStar:
    return "A*";
  }
  return "";
}

void refreshMenuTexts(std::vector<sf::Text> &items, const ConfigSettings &out) {
  items[0].setString("Rows: " + std::to_string(out.rows));
  items[1].setString("Cols: " + std::to_string(out.cols));
  items[2].setString("Gen: " + genName(out.genAlgo));
  items[3].setString("Solve: " + solveName(out.solveAlgo));

  std::ostringstream ss;
  ss << std::fixed << std::setprecision(2) << out.cycleProbability;
  items[4].setString("Cycles: " + ss.str());
}