#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;

int main() {

    ifstream inputFile;

    // open the input file
    inputFile.open("resources/usa13509.txt");
    if (!inputFile) {
        cout << "Can't open the input US map file resources/usa13509.txt\n";
        return -1;
    }
    unsigned w,h;
    inputFile >> w >> h;    // get dimension

    // create Canvas and put Red marker to each city read from inputFile
    sf::Image us_map;
    us_map.create(w,h,sf::Color::Black);
    double dx,dy;
    while (inputFile >> dx >> dy) {
        unsigned x = static_cast<unsigned>(dx);
        unsigned y = static_cast<unsigned>(dy);
        sf::Color color = us_map.getPixel(x,h-y);
        color = sf::Color::Red;
        us_map.setPixel(x,h-y,color);
    }
    // close inputFile when you done
    inputFile.close();

    // draw Canvas to the window!
    sf::RenderWindow window(sf::VideoMode(w,h,32), "US Map");
    sf::Texture texture;
    texture.loadFromImage(us_map);
    sf::Sprite sprite;
    sprite.setTexture(texture, true);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}