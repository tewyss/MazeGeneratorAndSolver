#include "EndScreen.h"
#include "FontManager.h"

EndScreenResult showEndScreen(sf::RenderWindow &window, const Maze &maze) {
  auto &font = FontManager::getFont();

  sf::Text title("PUZZLE SOLVED!", font, 20);
  title.setPosition(20.f, 20.f);

  std::vector<sf::Text> opts = {sf::Text("Re-configure", font, 16),
                                sf::Text("Exit", font, 16)};
  std::size_t selected = 0;
  const float startY = 80.f, spacing = 40.f;
  for (std::size_t i = 0; i < opts.size(); ++i) {
    opts[i].setPosition(20.f, startY + i * spacing);
  }

  while (window.isOpen()) {
    window.clear(sf::Color::Black);
    maze.draw(window);
    window.draw(title);
    for (std::size_t i = 0; i < opts.size(); ++i) {
      if (i == selected) {
        auto b = opts[i].getLocalBounds();
        sf::RectangleShape highLight({b.width + 10, b.height + 5});
        highLight.setPosition(opts[i].getPosition() - sf::Vector2f(5, 3));
        highLight.setFillColor({50, 50, 50, 150});
        window.draw(highLight);
      }
      opts[i].setFillColor(i == selected ? sf::Color::Yellow
                                         : sf::Color::White);
      window.draw(opts[i]);
    }
    window.display();

    sf::Event ev;
    while (window.pollEvent(ev)) {
      if (ev.type == sf::Event::Closed)
        return EndScreenResult::Exit;
      if (ev.type == sf::Event::KeyPressed) {
        switch (ev.key.code) {
        case sf::Keyboard::Up:
          selected = (selected + opts.size() - 1) % opts.size();
          break;
        case sf::Keyboard::Down:
          selected = (selected + 1) % opts.size();
          break;
        case sf::Keyboard::Enter:
          return (selected == 0) ? EndScreenResult::Reconfigure
                                 : EndScreenResult::Exit;
        default:
          break;
        }
      }
    }
  }

  return EndScreenResult::Exit;
}
