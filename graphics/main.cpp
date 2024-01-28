#include <SFML/Graphics.hpp>


int main()
{
    // create the window
    auto window = sf::RenderWindow{ { 1080u, 1080u }, "Othello" };
    window.setFramerateLimit(60);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        sf::CircleShape shape(48.f);

        // set the shape color to green
        shape.setFillColor(sf::Color::White);

        window.draw(shape);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}