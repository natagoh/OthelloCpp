#include <SFML/Graphics.hpp>


int main()
{
    // create the window
    auto window = sf::RenderWindow{ { 1080u, 1080u }, "Othello" };
    window.setFramerateLimit(60);


    /*
    * + -- +
    * | XX |
    * | XX |
    * + -- +
    * 
    * There is going to be some buffer between the piece and the square containing it
    */
    const float buffer = 8.f;
    const float pieceRadius = 32.f;
    const float boardSquareSize = (pieceRadius + buffer) * 2;
    const float boardSize = 8 * boardSquareSize;

    // create a render texture for the board
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(boardSize, boardSize)) {
        printf("Error creating render texture\n");
    }

    // drawing uses the same functions
    renderTexture.clear();

    // draw board rectangle
    sf::RectangleShape boardRectangle(sf::Vector2f(boardSize, boardSize));
    sf::Color forestGreen = sf::Color(63, 90, 54);
    boardRectangle.setFillColor(forestGreen);
    renderTexture.draw(boardRectangle); 
    renderTexture.display();

    for (int i = 1; i < 8; i++) {
        // draw horizontal board lines
        sf::Vertex horizontalLine[] = {
            sf::Vertex(sf::Vector2f(0.f, boardSquareSize * i), sf::Color::Black),
            sf::Vertex(sf::Vector2f(boardSize, boardSquareSize * i), sf::Color::Black)
        };
        renderTexture.draw(horizontalLine, 2, sf::Lines);

        // draw vertical board lines
        sf::Vertex verticalLine[] = {
            sf::Vertex(sf::Vector2f(boardSquareSize * i, 0.f), sf::Color::Black),
            sf::Vertex(sf::Vector2f(boardSquareSize * i, boardSize), sf::Color::Black)
        };
        renderTexture.draw(verticalLine, 2, sf::Lines);
    }
  
    // get the target texture (where the stuff has been drawn)
    const sf::Texture& boardTexture = renderTexture.getTexture();



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

        // draw rectangle for game board
       // draw it to the window
        sf::Sprite sprite(boardTexture);
        window.draw(sprite);

        // draw a circle
        sf::CircleShape piece(pieceRadius);
        // set origin to be at center of circle
        piece.setOrigin(sf::Vector2f(pieceRadius, pieceRadius));
        piece.setPosition(sf::Vector2f(boardSquareSize / 2, boardSquareSize / 2));
        piece.setOutlineColor(sf::Color::Black);
        piece.setOutlineThickness(1);
        piece.setFillColor(sf::Color::White);
        window.draw(piece);

        // draw a circle at row=2, col=4 on the board
        const float rowPos = boardSquareSize / 2 + boardSquareSize * 2;
        const float colPos = boardSquareSize / 2 + boardSquareSize * 4;
        piece.setPosition(sf::Vector2f(colPos, rowPos));
        piece.setOutlineColor(sf::Color::White);
        piece.setOutlineThickness(1);
        piece.setFillColor(sf::Color::Black);
        window.draw(piece);


        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
    }

    return 0;
}