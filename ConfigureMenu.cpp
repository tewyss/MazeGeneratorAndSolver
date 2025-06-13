#include "ConfigureMenu.h"
#include "FontManager.h"

std::vector<sf::Text> makeMenuItems(const sf::Font &font);
void positionMenuItems(std::vector<sf::Text> &items, sf::RenderWindow &window,
                       float startY, float spacing, float footerGap);
void drawMenu(sf::RenderWindow &window, std::vector<sf::Text> &items,
              size_t selected, sf::Text &title, sf::Text &warning,
              bool showWarning);
std::string genName(Generation generate);
std::string solveName(Solve solve);
void refreshMenuTexts(std::vector<sf::Text> &items, const ConfigSettings &out);

ConfigResult showConfigureMenu(sf::RenderWindow &window, ConfigSettings &out) {
  const int ANIMATE_THRESHOLD = 101 * 101;
  const auto &font = FontManager::getFont();

  sf::Text title("CONFIGURE MAZE", font, 32);
  {
    auto bounds = title.getLocalBounds();
    title.setPosition((window.getSize().x - bounds.width) / 2.f, 50);
  }

  auto items = makeMenuItems(font);
  sf::Text warning("Warning: animation disabled for large mazes!", font, 20);
  warning.setFillColor(sf::Color::Red);

  refreshMenuTexts(items, out);

  const float spacing = 50.f;
  const float footerGap = 100.f;
  float startY = 150.f;

  positionMenuItems(items, window, startY, spacing, footerGap);
  warning.setPosition((window.getSize().x - warning.getLocalBounds().width) /
                          2.f,
                      items[4].getPosition().y + spacing);

  std::size_t selected = 0;
  while (window.isOpen()) {
    sf::Event ev;
    while (window.pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) {
        window.close();
        return ConfigResult::Exit;
      }

      // handling settings of maze in the menu
      if (ev.type == sf::Event::KeyPressed) {
        switch (ev.key.code) {
        case sf::Keyboard::Up:
          selected = (selected + items.size() - 1) % items.size();
          break;
        case sf::Keyboard::Down:
          selected = (selected + 1) % items.size();
          break;

        case sf::Keyboard::Left:
        case sf::Keyboard::Right: {
          bool right = (ev.key.code == sf::Keyboard::Right);
          int deltaInt = right ? +2 : -2;
          double deltaP = right ? +0.05 : -0.05;

          switch (selected) {
          case 0:
            out.rows = std::clamp(out.rows + deltaInt, 5, 999);
            break;
          case 1:
            out.cols = std::clamp(out.cols + deltaInt, 5, 999);
            break;
          case 2: {
            if (right) {
              switch (out.genAlgo) {
              case Generation::DFS:
                out.genAlgo = Generation::Kruskal;
                break;
              case Generation::Kruskal:
                out.genAlgo = Generation::Wilson;
                break;
              case Generation::Wilson:
                out.genAlgo = Generation::DFS;
                break;
              }
            } else {
              switch (out.genAlgo) {
              case Generation::DFS:
                out.genAlgo = Generation::Wilson;
                break;
              case Generation::Wilson:
                out.genAlgo = Generation::Kruskal;
                break;
              case Generation::Kruskal:
                out.genAlgo = Generation::DFS;
                break;
              }
            }
          } break;
          case 3: {
            if (right) {
              switch (out.solveAlgo) {
              case Solve::DFS:
                out.solveAlgo = Solve::BFS;
                break;
              case Solve::BFS:
                out.solveAlgo = Solve::AStar;
                break;
              case Solve::AStar:
                out.solveAlgo = Solve::DFS;
                break;
              }
            } else {
              switch (out.solveAlgo) {
              case Solve::DFS:
                out.solveAlgo = Solve::AStar;
                break;
              case Solve::AStar:
                out.solveAlgo = Solve::BFS;
                break;
              case Solve::BFS:
                out.solveAlgo = Solve::DFS;
                break;
              }
            }
          } break;
          case 4:
            out.cycleProbability =
                std::clamp(out.cycleProbability + deltaP, 0.0, 1.0);
            break;
          default:
            break;
          }
          refreshMenuTexts(items, out);
        } break;

        case sf::Keyboard::Enter:
          if (selected == 5)
            return ConfigResult::Start;
          if (selected == 6)
            return ConfigResult::Back;
          break;

        default:
          break;
        }
      }
    }

    bool showWarning = (out.rows * out.cols > ANIMATE_THRESHOLD);
    drawMenu(window, items, selected, title, warning, showWarning);
  }
  return ConfigResult::Back;
}
