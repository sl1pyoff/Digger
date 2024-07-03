#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <list>
#include <ctime>
#include <cmath>


#include "headers/map.h"
#include "headers/view.h"
#include "headers/MainMenu.h"
#include "headers/Info.h"


using namespace sf;


class Entity {
public:
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life;
    Texture texture;
    Sprite sprite;
    String name;

    Entity(Image& image, String Name, float X, float Y, int W, int H) {
        x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
        speed = 0; health = 100; dx = 0; dy = 0;
        life = true;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }

    FloatRect getRect() {
        return FloatRect(x, y, w, h);
    }

    bool checkCollision(Entity& other) {
        return sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds());
    }
};

class Enemy : public Entity {
public:
    float frameTime;
    int currentFrame;

    Enemy(Image& image, String Name, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H) {
        frameTime = 0;
        currentFrame = 0;
        if (name == "EasyEnemy") {
            sprite.setTextureRect(IntRect(11, 6, w, h));
            dx = 0.1;
        }
    }

    void checkCollisionWithMap(float Dx, float Dy) {
    for (int i = y / 32; i < (y + h) / 32; i++) {
        for (int j = x / 32; j < (x + w) / 32; j++) {
            if (i >= 0 && i < HEIGHT_MAP && j >= 0 && j < WIDTH_MAP) {
                if (TileMap[i][j] == '0') {
                    if (Dy > 0) { y = i * 32 - h; }
                    if (Dy < 0) { y = i * 32 + 32; }
                    if (Dx > 0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }
                    if (Dx < 0) { x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }
                }
            } else {
                std::cerr << "Index out of bounds: i=" << i << ", j=" << j << std::endl;
            }
        }
    }
}
    void update(float time) {
        if (name == "EasyEnemy") {
            checkCollisionWithMap(dx, 0);
            x += dx * time;
            sprite.setPosition(x + w / 2, y + h / 2);
            animate(time);
            if (health <= 0) { life = false; }
        }
    }

    void animate(float time) {
        time = time / 800;
        static const float ANIMATION_SPEED = 0.2f;  
        frameTime += time;

        if (frameTime >= ANIMATION_SPEED) {
            frameTime = 0;
            currentFrame = (currentFrame + 1) % 3; 
        }

        if (dx > 0) {//rigth
            sprite.setTextureRect(IntRect(72 * currentFrame, 104, 62, 45));
        }
        else if (dx < 0) {//left
            sprite.setTextureRect(IntRect(72 * currentFrame, 104, 62, 45));
        }
    }
};

class Player : public Entity {
public:
    enum stateObjeckt { left, right, up, down, stay } state;
    int playerScore;
    float frameTime;
    int currentFrame;

    Player(Image& image, String Name, float X, float Y, int W, int H) : Entity(image, Name, X, Y, W, H) {
        playerScore = 0;
        state = stay;
        frameTime = 0;
        currentFrame = 0;
        if (name == "Player1") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
        }
    }

    void update(float time) {
        control();
        switch (state) {
        case right: dx = speed; dy = 0; break;
        case left: dx = -speed; dy = 0; break;
        case up: dx = 0; dy = -speed; break;
        case down: dx = 0; dy = speed; break;
        case stay: dx = 0; dy = 0; break;
        }

        x += dx * time;
        checkCollisionWithMap(dx, 0);
        y += dy * time;
        checkCollisionWithMap(0, dy);
        sprite.setPosition(x + w / 2, y + h / 2);
        if (life) { setPlayerCoordForView(x, y); }

        animate(time);
    }

    void control() {
        if (health <= 0) {
            state = stay;
            speed = 0;
            life = false;
            return;
        }

        float baseSpeed = 0.2f;
        float boostSpeed = 0.3f;
        float currentSpeed = (Keyboard::isKeyPressed(Keyboard::LShift) || Keyboard::isKeyPressed(Keyboard::RShift)) ? boostSpeed : baseSpeed;

        state = stay;
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            state = left;
        }
        else if (Keyboard::isKeyPressed(Keyboard::D)) {
            state = right;
        }
        else if (Keyboard::isKeyPressed(Keyboard::W)) {
            state = up;
        }
        else if (Keyboard::isKeyPressed(Keyboard::S)) {
            state = down;
        }

        if (state == left || state == right) {
            dy = 0;
        }
        if (state == up || state == down) {
            dx = 0;
        }

        speed = (state != stay) ? currentSpeed : 0.0f;
    }
    void animate(float time) {
        time = time / 800;
        static const float ANIMATION_SPEED = 0.1f;  // Adjust this value to control the speed of the animation
        frameTime += time;

        if (frameTime >= ANIMATION_SPEED) {
            frameTime = 0;
            currentFrame = (currentFrame + 1) % 3; // Assuming 3 frames for each direction
        }
        if (state == right) {
            sprite.setTextureRect(IntRect(50 * currentFrame, 0, 43, 55));
        }
        else if (state == left) {
            sprite.setTextureRect(IntRect(50 * currentFrame, 55, 45, 55));
        }
        else if (state == up) {
            sprite.setTextureRect(IntRect(50 * currentFrame, 166, 50, 55));
        }
        else if (state == down) {
            sprite.setTextureRect(IntRect(50 * currentFrame, 112, 50, 55));
        }
        else if (state == stay) {
            sprite.setTextureRect(IntRect(52, 111, w, h));
        }
    }


    void checkCollisionWithMap(float Dx, float Dy) {
        for (int i = y / 32; i < (y + h) / 32; i++) {
            for (int j = x / 32; j < (x + w) / 32; j++) {
                
                if (i >= 0 && i < HEIGHT_MAP && j >= 0 && j < WIDTH_MAP) {
                    if (TileMap[i][j] == '0') {
                        if (Dy > 0) { y = i * 32 - h; dy = 0; }
                        if (Dy < 0) { y = i * 32 + 32; dy = 0; }
                        if (Dx > 0) { x = j * 32 - w; dx = 0; }
                        if (Dx < 0) { x = j * 32 + 32; dx = 0; }
                    }

                    if (TileMap[i][j] == 's') {
                        playerScore += 100;
                        TileMap[i][j] = ' ';
                    }

                    if (TileMap[i][j] == 'h') {
                        health += 20;
                        playerScore += 25;
                        TileMap[i][j] = ' ';
                    }

                    if (TileMap[i][j] == 'f') {
                        health -= 50;
                        playerScore -= 50;
                        TileMap[i][j] = ' ';
                    }
                }
                else {
                    std::cerr << "Index out of bounds: i=" << i << ", j=" << j << std::endl;
                }
            }
        }
    }
};

bool checkWinCondition() {
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (TileMap[i][j] == 's') {
                return false; // There are still 's' elements left
            }
        }
    }
    return true;
}

bool startGame(int numEnemies, int numGold, int numPotions) {
    bool won = false;
    RenderWindow gameWindow(VideoMode(1290, 960), "Digger", Style::Default);
    view.reset(FloatRect(500, 500, 920, 720));

    Font fontForHud;
    fontForHud.loadFromFile("resources/fonts/SecondFont.otf");
    Font fontForEnd;
    fontForEnd.loadFromFile("resources/fonts/MainFont.otf");

    Text text("", fontForHud, 17);
    text.setFillColor(Color::Yellow);

    Text gameOverText(" You Lost\nPress tab", fontForEnd, 100);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);

    Text winText("\tYou Win\nPress Escape", fontForEnd, 100);
    winText.setFillColor(Color::Yellow);
    winText.setStyle(Text::Bold);

    Image enemyImage;
    enemyImage.loadFromFile("resources/images/enemy.png");

    Image heroImage;
    heroImage.loadFromFile("resources/images/hero.png");

    Player player(heroImage, "Player1", 250, 250, 43, 55);

    std::list<Enemy*> enemies;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const float minDistance = 200.0f;
    const float minEnemyDistance = 100.0f; // Minimum distance between enemies
    std::vector<Vector2f> enemyPositions;  // Store the positions of enemies

    for (int i = 0; i < numEnemies; ++i) {
        float randomX, randomY;
        bool validPosition;
        do {
            randomX = static_cast<float>(std::rand() % 800 + 100);
            randomY = static_cast<float>(std::rand() % 600 + 100);
            validPosition = true;

            // Перевірка на вихід за межі масиву TileMap
            int tileX = static_cast<int>(randomX / 32);
            int tileY = static_cast<int>(randomY / 32);
            if (tileX < 0 || tileX >= WIDTH_MAP || tileY < 0 || tileY >= HEIGHT_MAP) {
                validPosition = false;
            }

            
            if (std::sqrt(std::pow(randomX - player.x, 2) + std::pow(randomY - player.y, 2)) < minDistance) {
                validPosition = false;
            }

            
            for (const auto& pos : enemyPositions) {
                if (std::sqrt(std::pow(randomX - pos.x, 2) + std::pow(randomY - pos.y, 2)) < minEnemyDistance) {
                    validPosition = false;
                    break;
                }
            }

        } while (!validPosition);

        enemies.push_back(new Enemy(enemyImage, "EasyEnemy", randomX, randomY, 72, 66));
        enemyPositions.emplace_back(randomX, randomY); 
    }

    Clock clock;
    Clock gameTimeClock;
    int gameTime = 0;

    randomMapGenerate(numGold, numPotions);

    while (gameWindow.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        if (player.life && !won) {
            gameTime = gameTimeClock.getElapsedTime().asSeconds();
        }

        Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                gameWindow.close();
                return false; 
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    gameWindow.close();
                    return false; 
                }
            }
        }

        if (player.life && !won) {
            player.update(time);
            for (auto enemy : enemies) {
                enemy->update(time);
                if (player.checkCollision(*enemy)) {
                    player.health -= 100;
                    enemy->life = false;
                    if (player.health <= 0) {
                        player.life = false;
                    }
                }
            }
            won = checkWinCondition();
        }

        gameWindow.setView(view);
        gameWindow.clear();

        if (player.life && !won) {
            drawMap(gameWindow);

            std::ostringstream scoreString, healthString, gameTimeString;
            healthString << player.health;
            scoreString << player.playerScore;
            gameTimeString << gameTime;

            text.setString("Health: " + healthString.str() + "\tScore: " + scoreString.str() + "\tTime in game: " + gameTimeString.str() + " sec");
            text.setPosition(view.getCenter().x - 450, view.getCenter().y - 350);
            gameWindow.draw(text);

            gameWindow.draw(player.sprite);
            for (auto enemy : enemies) {
                if (enemy->life) {
                    gameWindow.draw(enemy->sprite);
                }
            }
        }
        else if (!player.life) {
            RectangleShape background(Vector2f(1024, 860));
            background.setFillColor(Color::Black);
            gameWindow.draw(background);

            FloatRect textRect = gameOverText.getLocalBounds();
            gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            gameOverText.setPosition(view.getCenter().x, view.getCenter().y);
            gameWindow.draw(gameOverText);
            if (Keyboard::isKeyPressed(Keyboard::Tab)) {
                return true;
            }
        }
        else if (won) {
            RectangleShape background(Vector2f(1024, 860));
            background.setFillColor(Color::Black);
            gameWindow.draw(background);

            FloatRect textRect = winText.getLocalBounds();
            winText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            winText.setPosition(view.getCenter().x, view.getCenter().y);
            gameWindow.draw(winText);
        }

        gameWindow.display();
    }

    for (auto enemy : enemies) {
        delete enemy;
    }
}

void gameRunning(int numEnemies, int numGold, int numPotions) {
    while (startGame(numEnemies, numGold, numPotions)) {}
}


int WinMain() {
    sf::RenderWindow window(sf::VideoMode(1290, 960), "Underground Adventure", sf::Style::Default);
    MainMenu mainMenu(window.getSize().x, window.getSize().y);
    Info info("Underground Adventure", "Bogdan Kanava", "It's a game inspired \n\nof an original \"Digger\"", "v. 1.0\n\nPress ESCAPE to go back");
    Info howToPlay;


    sf::Texture mainMenuTexture;
    sf::Texture playTexture;
    sf::Texture optionsTexture;
    sf::Texture aboutTexture;

    mainMenuTexture.loadFromFile("resources/images/MainMenuback.png");
    playTexture.loadFromFile("resources/images/MainMenuback.png");
    optionsTexture.loadFromFile("resources/images/MainMenuback.png");
    aboutTexture.loadFromFile("resources/images/MainMenuback.png");

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(1290, 960));
    background.setTexture(&mainMenuTexture);

    sf::Event event;
    bool inMainMenu = true;
    bool inPlay = false;
    bool inHowtoPlay = false;
    bool inAbout = false;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up && inMainMenu) {
                    mainMenu.MoveUp();
                }
                if (event.key.code == sf::Keyboard::Down && inMainMenu) {
                    mainMenu.MoveDown();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    int x = mainMenu.MainMenuPressed();
                    if (x == 0) {
                        inMainMenu = false;
                        inPlay = true;
                    }
                    if (x == 1) {
                        inMainMenu = false;
                        inHowtoPlay = true;
                    }
                    if (x == 2) {
                        inMainMenu = false;
                        inAbout = true;
                    }
                    if (x == 3) {
                        window.close();
                    }
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    if (inPlay || inHowtoPlay || inAbout) {
                        inMainMenu = true;
                        inPlay = false;
                        inHowtoPlay = false;
                        inAbout = false;
                    }
                }
            }
        }

        if (inMainMenu) {
            window.clear();
            window.draw(background);
            mainMenu.draw(window);
            window.display();
        }
        if (inPlay) {
            window.clear();
            background.setTexture(&playTexture);
            window.draw(background);
            window.display();
            gameRunning(4, 5, 5);
            inMainMenu = true;
            inPlay = false;
        }
        if (inHowtoPlay) {
            window.clear();
            background.setTexture(&optionsTexture);
            window.draw(background);
            howToPlay.draw(window);
            window.display();
        }
        if (inAbout) {
            window.clear();
            background.setTexture(&aboutTexture);
            window.draw(background);
            info.draw(window);
            window.display();
        }
    }

    return 0;
}