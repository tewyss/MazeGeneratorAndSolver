#include <SFML/Graphics.hpp>

sf::VideoMode getWindowVideoMode(float scale = 0.8f) {
  auto desktop = sf::VideoMode::getDesktopMode();
  unsigned int w = static_cast<unsigned int>(desktop.width * scale);
  unsigned int h = static_cast<unsigned int>(desktop.height * scale);
  return sf::VideoMode(w, h);
}

void configureWindow(sf::RenderWindow &window) {
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);
}
