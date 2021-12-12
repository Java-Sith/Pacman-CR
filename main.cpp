#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    // Create the main window
    //auto fullScreenModes = sf::VideoMode::getFullscreenModes();
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML window");
    /*for (auto & VideoMode: fullScreenModes) {
        std::cout << "Size: " << VideoMode.width << " & " << VideoMode.height << "BPP: " << VideoMode.bitsPerPixel << std::endl;
    }*/
    //Testing some SFML shapes
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(200, 100));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color::Red);
    sf::CircleShape circle;
    circle.setRadius(20);
    circle.setFillColor(sf::Color::Blue);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(sf::Color::Yellow);
    sf::ConvexShape convex;
    convex.setPointCount(3);
    convex.setPoint(0, sf::Vector2f(0, 0));
    convex.setPoint(1, sf::Vector2f(150, 30));
    convex.setPoint(2, sf::Vector2f(0, 60));
    convex.setFillColor(sf::Color::Magenta);
    rectangle.setPosition(10, 10);
    circle.setPosition(400, 50);
    convex.setPosition(250, 250);
    //Load some textures
    sf::Image image;
    image.loadFromFile("../assets/IronManSprite.png"); //Saved in system memory
    sf::Texture texture;
    texture.loadFromImage(image); //Saved in graphics memory
    sf::Sprite sprite(texture);
    sprite.setPosition(300, 300);
    sprite.setRotation(45);
    sf::Font font;
    font.loadFromFile("../assets/Georgina.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World!");
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(200, 200);
    text.setCharacterSize(42);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Left Button" << std::endl;
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                std::cout << "Right Button" << std::endl;
            }
        }
        // Update the window
        window.clear();
        window.draw(rectangle);
        window.draw(circle);
        window.draw(convex);
        window.draw(sprite);
        window.draw(text);
        window.display();
        window.setFramerateLimit(60);
        sf::sleep(sf::seconds(1.f/60.f));
    }
    return EXIT_SUCCESS;
}
