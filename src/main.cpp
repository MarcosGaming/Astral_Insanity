#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <iomanip>  // std::setprecision
#include <iostream> // std::cout, std::fixed
#include <sstream>
#include <string>

using namespace sf;
using namespace std;

template <typename T>
std::string toStrDecPt(const uint16_t& dp, const T& i) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(dp) << i;
  return stream.str();
}

Texture texture;
Sprite sprite;
RenderWindow* _window;
void Load() {
  if (!texture.loadFromFile("res/img/spaceship1.png")) {
    throw std::invalid_argument("Loading error!");
  }
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Update() {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();

  {
    frametimes[++ftc] = dt;
    static string avg = " Astral Insanity FPS:";
    if (ftc % 60 == 0) {
      double davg = 0;
      for (const auto t : frametimes) {
        davg += t;
      }
      davg = 1.0 / (davg / 255.0);
      _window->setTitle(avg + toStrDecPt(2, davg));
    }
  }

  Vector2f move;
  if (Keyboard::isKeyPressed(Keyboard::Left)) {
    move.x--;
  }
  if (Keyboard::isKeyPressed(Keyboard::Right)) {
    move.x++;
  }
  sprite.move(move*300.0f*dt);
}

void Render(RenderWindow &window) { window.draw(sprite); }

int main() {
  RenderWindow window(VideoMode(400, 400), "SFML works!");
  _window = &window;
  window.setVerticalSyncEnabled(true);
  try {
    Load();
  } catch (const std::exception &) {
    std::cerr << "Load error" << std::endl;
    return 1;
  }

  sprite.setTexture(texture);
  sprite.setScale(Vector2f(2.f, 2.f));

  while (window.isOpen()) {

    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    window.clear();
    Update();
    Render(window);
    window.display();
  }

  return 0;
}