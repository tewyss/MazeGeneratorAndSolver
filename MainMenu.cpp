#include "MainMenu.h"
#include "FontManager.h"

static sf::Texture mazeTexture;
static bool imageLoaded = false;

static void loadResources() {
  if (not imageLoaded) {
    if (not mazeTexture.loadFromFile("assets/images/mazeMenuPicture.png")) {
      throw std::runtime_error("Failed to load font");
    }
    imageLoaded = true;
  }
}

static void setupUI(sf::RenderWindow &window, sf::Sprite &mazeSprite,
                    sf::Text &title, std::vector<sf::Text> &options,
                    std::size_t &selectedIndex, float &optionsY) {
  auto &font = FontManager::getFont();

  title = sf::Text("MAZE GENERATOR AND SOLVER", font, 32);
  auto tBounds = title.getLocalBounds();
  title.setPosition((window.getSize().x - tBounds.width) / 2.f, 50.f);

  // textures and ther positions
  optionsY = 150.f;
  if (imageLoaded) {
    mazeSprite.setTexture(mazeTexture);
    auto sBounds = mazeSprite.getLocalBounds();
    mazeSprite.setPosition((window.getSize().x - sBounds.width) / 2.f,
                           title.getPosition().y + tBounds.height + 20.f);
    optionsY = mazeSprite.getPosition().y + sBounds.height + 20.f;
  }

  options.clear();
  options.emplace_back("Configure", font, 26);
  options.emplace_back("Exit", font, 26);

  const float spacing = 60.f;
  selectedIndex = 0;

  for (std::size_t i = 0; i < options.size(); ++i) {
    auto oBounds = options[i].getLocalBounds();
    options[i].setPosition((window.getSize().x - oBounds.width) / 2.f,
                           optionsY + i * spacing);
  }
}

static void updateSelection(std::size_t &selectedIndex, std::size_t optionCount,
                            int delta) {
  selectedIndex = (selectedIndex + optionCount + delta) % optionCount;
}

static void render(sf::RenderWindow &window, const sf::Text &title,
                   const sf::Sprite &mazeSprite, std::vector<sf::Text> &options,
                   std::size_t selectedIndex) {
  window.clear(sf::Color::Black);

  window.draw(title);
  if (imageLoaded) {
    window.draw(mazeSprite);
  }

  // drawing options
  for (std::size_t i = 0; i < options.size(); ++i) {
    if (i == selectedIndex) {
      auto bounds = options[i].getLocalBounds();
      sf::RectangleShape highlight;
      highlight.setSize({bounds.width + 20.f, bounds.height + 10.f});
      highlight.setPosition(options[i].getPosition() - sf::Vector2f(10.f, 5.f));
      highlight.setFillColor(sf::Color(50, 50, 50, 150));
      window.draw(highlight);
    }

    options[i].setFillColor(i == selectedIndex ? sf::Color::Yellow
                                               : sf::Color::White);
    window.draw(options[i]);
  }

  window.display();
}

MenuResult showMainMenu(sf::RenderWindow &window) {
  loadResources();

  sf::Sprite mazeSprite;
  sf::Text title;
  std::vector<sf::Text> options;
  std::size_t selectedIndex;
  float optionsY;

  setupUI(window, mazeSprite, title, options, selectedIndex, optionsY);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return MenuResult::Exit;
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
          updateSelection(selectedIndex, options.size(), -1);
        } else if (event.key.code == sf::Keyboard::Down) {
          updateSelection(selectedIndex, options.size(), 1);
        } else if (event.key.code == sf::Keyboard::Enter) {
          return (selectedIndex == 0) ? MenuResult::Configure
                                      : MenuResult::Exit;
        }
      }
    }

    render(window, title, mazeSprite, options, selectedIndex);
  }

  return MenuResult::Exit;
}
