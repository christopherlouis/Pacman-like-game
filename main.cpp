#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "game");
    std::srand(std::sin(std::time(nullptr)) * 1000);
    int timer = 0;
    int moveTimer = 500;

    bool updatePath = true;
    int orderedSet[25 * 25];
    int path[100];
    int pathSize = 0;
    int pathPos = 0;

    sf::Vector2i player = sf::Vector2i(13, 13);
    sf::Texture playerTex;
    playerTex.loadFromFile("player.png");
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTex);
    playerSprite.setPosition(player.x * 40.f, player.y * 40.f);

    sf::Texture playerTex2;
    playerTex2.loadFromFile("player2.png");

    sf::Vector2i opponent = sf::Vector2i(1, 1);
    sf::Texture opponentTex;
    opponentTex.loadFromFile("enemy (2).png");
    sf::Sprite opponentSprite;
    opponentSprite.setTexture(opponentTex);
    opponentSprite.setPosition(opponent.x * 40.f, opponent.y * 40.f);

    sf::Texture wallTex;
    wallTex.loadFromFile("wall.png");

    sf::Texture roadTex;
    roadTex.loadFromFile("road.png");

    sf::Texture gateTex;
    gateTex.loadFromFile("gate.png");

    sf::Texture coinTex;
    coinTex.loadFromFile("coin.png");
    sf::Sprite coins[10];
    int numCoins = 0;
    int score = 0;

    int gameMap[25 * 25];
    sf::RectangleShape displayRects[25 * 25];

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            displayRects[i + j * 25].setPosition(i * 40.f, j * 40.f);
            displayRects[i + j * 25].setSize(sf::Vector2f(40.f, 40.f));
            /*displayRects[i + j * 25].setOutlineThickness(1.f);
            displayRects[i + j * 25].setOutlineColor(sf::Color(0, 0, 0));*/
            displayRects[i + j * 25].setTexture(&roadTex);

            if (!(i == opponent.x && j == opponent.y) && !(i == player.x && j == player.y)) {
                if (i == 0 || j == 0 || i == 24 || j == 24 || ((i >= 4 && i <= 8) && j == 2) || ((j >= 2 && j <= 4) && i == 10) || ((j >= 1 && j <= 6) && i == 12) || (i == 13 && j == 4)
                    || ((j >= 2 && j <= 4) && i == 2) || ((i >= 3 && i <= 4) && j == 4) || ((j >= 5 && j <= 6) && i == 4) || ((i >= 1 && i <= 2) && j == 6) || ((i >= 1 && i <= 6) && j == 8)
                    || ((j >= 4 && j <= 8) && i == 6) || ((j >= 4 && j <= 6) && i == 8) || ((i >= 9 && i <= 10) && j == 6) || ((j >= 10 && j <= 15) && i == 2) || ((i >= 3 && i <= 4) && j == 15)
                    || ((j >= 14 && j <= 16) && i == 5) || ((i >= 6 && i <= 9) && j == 14) || ((j >= 14 && j <= 15) && i == 10) || ((j >= 10 && j <= 12) && i == 5) || ((i >= 6 && i <= 7) && j == 10)
                    || ((j >= 9 && j <= 11) && i == 8) || ((j >= 8 && j <= 12) && i == 10) || ((j >= 17 && j <= 18) && i == 3) || ((i >= 1 && i <= 2) && j == 17) || ((i >= 7 && i <= 8) && j == 16)
                    || (i == 7 && j == 17) || ((j >= 18 && j <= 19) && i == 5) || (i == 6 && j == 19) || ((j >= 20 && j <= 22) && i == 2) || ((j >= 21 && j <= 22) && i == 3) || ((i >= 4 && i <= 7) && j == 21)
                    || ((i >= 7 && i <= 8) && j == 22) || ((i >= 10 && i <= 11) && j == 17) || ((j >= 17 && j <= 18) && i == 12) || ((i >= 8 && i <= 9) && j == 19) || ((i >= 9 && i <= 12) && j == 20)
                    || ((j >= 21 && j <= 22) && i == 12) || (i == 5 && j == 23) || (i == 10 && j == 23) || (i == 17 && j == 23) || (i == 18 && j == 1) || ((i >= 14 && i <= 15) && j == 2)
                    || ((j >= 2 && j <= 3) && i == 16) || ((i >= 15 && i <= 16) && j == 4) || ((i >= 18 && i <= 19) && j == 3) || ((j >= 2 && j <= 3) && i == 20) || ((j >= 2 && j <= 4) && i == 22)
                    || ((j >= 6 && j <= 7) && i == 19) || ((i >= 18 && i <= 22) && j == 5) || ((i >= 21 && i <= 23) && j == 7) || ((j >= 6 && j <= 7) && i == 14) || ((i >= 15 && i <= 16) && j == 6)
                    || ((j >= 7 && j <= 9) && i == 16) || ((i >= 17 && i <= 18) && j == 9) || ((j >= 10 && j <= 11) && i == 17) || ((i >= 20 && i <= 22) && j == 9) || ((j >= 10 && j <= 11) && i == 22)
                    || ((j >= 9 && j <= 11) && i == 12) || ((j >= 9 && j <= 11) && i == 14) || (i == 13 && j == 9) || ((j >= 13 && j <= 15) && i == 12) || ((j >= 13 && j <= 15) && i == 14) || (i == 13 && j == 15)
                    || ((i >= 16 && i <= 17) && j == 13) || ((j >= 14 && j <= 16) && i == 17) || ((i >= 14 && i <= 18) && j == 17) || ((j >= 16 && j <= 17) && i == 19) || ((j >= 18 && j <= 19) && i == 14)
                    || ((j >= 12 && j <= 14) && i == 20) || (i == 21 && j == 13) || ((i >= 22 && i <= 23) && j == 21) || ((i >= 21 && i <= 22) && j == 22) || ((i >= 22 && i <= 23) && j == 15) || ((i >= 21 && i <= 22) && j == 16)
                    || ((j >= 22 && j <= 23) && i == 14) || ((j >= 21 && j <= 22) && i == 15) || ((j >= 19 && j <= 21) && i == 16) || ((i >= 21 && i <= 22) && j == 18) || ((i >= 20 && i <= 22) && j == 19)
                    || ((i >= 18 && i <= 20) && j == 20) || ((j >= 21 && j <= 22) && i == 19)) {
                    gameMap[i + j * 25] = 1;

                    displayRects[i + j * 25].setTexture(&wallTex);
                }
            }
        }
    }

    

    while (numCoins < 10) {
        int col = (std::rand() / (float)RAND_MAX) * 25.f;
        int row = (std::rand() / (float)RAND_MAX) * 25.f;
        if (col != 23 && row != 23) {
            if (gameMap[col + row * 25] < 1) {
                gameMap[col + row * 25] = 2;
                coins[numCoins].setTexture(coinTex);
                coins[numCoins].setPosition(col * 40.f, row * 40.f);
                numCoins += 1;
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    if (gameMap[player.x + (player.y - 1) * 25] != 1) player.y -= 1;
                    break;
                case sf::Keyboard::S:
                    if (gameMap[player.x + (player.y + 1) * 25] != 1) player.y += 1;
                    break;
                case sf::Keyboard::D:
                    if (gameMap[(player.x + 1) + player.y * 25] != 1) player.x += 1;
                    playerSprite.setTexture(playerTex2);
                    break;
                case sf::Keyboard::A:
                    if (gameMap[(player.x - 1) + player.y * 25] != 1) player.x -= 1;
                    playerSprite.setTexture(playerTex);
                    break;
                }
            }

            updatePath = true;
            pathSize = 0;
            pathPos = 0;
            playerSprite.setPosition(player.x * 40.f, player.y * 40.f);
        }
        

        window.clear(sf::Color(255, 255, 255));

        for (int i = 0; i < 25 * 25; i++) {
            window.draw(displayRects[i]);
        }

        for (int i = 0; i < numCoins; i++) {
            window.draw(coins[i]);
        }

        if (updatePath == true) {
            int counter = 0;

            int fullSet[2000];
            int fullSetSize = 0;

            int openSet[100];
            int openSetSize = 2;
            openSet[0] = player.x + player.y * 25;
            openSet[1] = counter;

            int currentIndex = player.x + player.y * 25;

            while (currentIndex != opponent.x + opponent.y * 25) {
                currentIndex = openSet[0];
                counter = openSet[1] + 1;
                int neighbors[4];

                neighbors[0] = currentIndex - 1;
                neighbors[1] = currentIndex + 1;
                neighbors[2] = currentIndex - 25;
                neighbors[3] = currentIndex + 25;

                for (int i = 0; i < 8; i += 2) {
                    bool alreadyExists = false;

                    for (int j = 0; j < fullSetSize; j += 2) {
                        if (neighbors[i / 2] == fullSet[j]) {
                            alreadyExists = true;
                            break;
                        }
                    }

                    if (alreadyExists == false) {
                        if (gameMap[neighbors[i / 2]] != 1) {
                            fullSet[fullSetSize] = neighbors[i / 2];
                            fullSet[fullSetSize + 1] = counter;
                            fullSetSize += 2;

                            openSet[openSetSize] = neighbors[i / 2];
                            openSet[openSetSize + 1] = counter;
                            openSetSize += 2;
                        }
                        else {
                            fullSet[fullSetSize] = neighbors[i / 2];
                            fullSet[fullSetSize + 1] = 100000;
                            fullSetSize += 2;
                        }
                    }
                }

                for (int i = 0; i < openSetSize; i++) {
                    openSet[i] = openSet[i + 2];
                }

                openSetSize -= 2;
            }

            for (int i = 0; i < 25 * 25; i++) {
                orderedSet[i] = 100000;
            }

            for (int i = 0; i < fullSetSize; i += 2) {
                orderedSet[fullSet[i]] = fullSet[i + 1];
            }

            orderedSet[player.x + player.y * 25] = 0;

            int pathIndex = opponent.x + opponent.y * 25;

            while (pathIndex != player.x + player.y * 25) {
                int neighbors[4];

                neighbors[0] = pathIndex - 1;
                neighbors[1] = pathIndex + 1;
                neighbors[2] = pathIndex - 25;
                neighbors[3] = pathIndex + 25;

                int lowest[2]{ 0, 100000 };
                for (int i = 0; i < 4; i++) {
                    if (orderedSet[neighbors[i]] < lowest[1]) {
                        lowest[0] = i;
                        lowest[1] = orderedSet[neighbors[i]];
                    }
                }

                pathIndex = neighbors[lowest[0]];

                path[pathSize] = pathIndex;

                pathSize += 1;
            }

            updatePath = false;
        }

        if (timer % moveTimer == 0) {
            opponent.x = path[pathPos] % 25;
            opponent.y = std::floor(path[pathPos] / 25);
            opponentSprite.setPosition(opponent.x * 40.f, opponent.y * 40.f);
            pathPos += 1;

        
        }

        window.draw(playerSprite);
        window.draw(opponentSprite);

        window.display();

        if (gameMap[player.x + player.y * 25] == 2) {
            gameMap[player.x + player.y * 25] = 0;

            int coinIndex = -1;
            for (int i = 0; i < numCoins; i++) {
                if (coins[i].getPosition().x / 40 == player.x && coins[i].getPosition().y / 40 == player.y) {
                    coinIndex = i;
                }
            }

            if (coinIndex != numCoins - 1) {
                coins[coinIndex] = coins[numCoins - 1];
            }

            score += 1;
            numCoins -= 1;
        }
        if (numCoins == 0)
        {
            displayRects[25 * 23 + 23].setTexture(&gateTex);
        }


        if (player.x == 23 && player.y == 23) {
            if (numCoins == 0) {
                std::cout << "~~~~~ YOU WIN ~~~~~" << score << std::endl;
                return 0;
            }
            else {

            }
        }

        timer += 6;

        if (player == opponent) {
            std::cout << "~~~~~ YOU LOSE ~~~~~" << score << std::endl;
            return 0;
        }
    }
    return 0;
}
