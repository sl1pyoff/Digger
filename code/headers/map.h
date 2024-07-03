const int HEIGHT_MAP = 25;
const int WIDTH_MAP = 40;  

sf::String TileMap[HEIGHT_MAP] = {
    "0000000000000000000000000000000000000000",
    "0                          0           0",
    "0       f                  0           0",
    "0        f            000000     000   0",
    "0                          0           0",
    "0                          0           0",
    "000000000000               0      0    0",
    "0          0                      0    0",
    "0          0                    f 0    0",
    "0          0 f             f      0    0",
    "0          0                      0    0",
    "0        f 0       f              0    0",
    "0                                      0",
    "0                              f       0",
    "0                  h                   0",
    "0                                      0",
    "0     f                            ff  0",
    "0          00000000      000000000000000",
    "0                 0           0        0",
    "0        ff       0           0        0",
    "0      00000      0             f      0",
    "0        f                             0",
    "0                          0        f  0",
    "0                f      f  0           0",
    "0000000000000000000000000000000000000000",
};

void clearMap() {
    for (int i = 0; i < HEIGHT_MAP; ++i) {
        for (int j = 0; j < WIDTH_MAP; ++j) {
            if (TileMap[i][j] == 's' || TileMap[i][j] == 'h') {
                TileMap[i][j] = ' ';
            }
        }
    }
}

void randomMapGenerate(int countGold, int countPotions) {
    clearMap();

    int randomElementX = 0;
    int randomElementY = 0;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    while (countGold > 0) {
        randomElementX = 1 + std::rand() % (WIDTH_MAP - 2); 
        randomElementY = 1 + std::rand() % (HEIGHT_MAP - 2); 

        if (TileMap[randomElementY][randomElementX] == ' ') {
            TileMap[randomElementY][randomElementX] = 's';
            countGold--;
        }
    }

    while (countPotions > 0) {
        randomElementX = 1 + std::rand() % (WIDTH_MAP - 2); 
        randomElementY = 1 + std::rand() % (HEIGHT_MAP - 2); 

        if (TileMap[randomElementY][randomElementX] == ' ') {
            TileMap[randomElementY][randomElementX] = 'h';
            countPotions--;
        }
    }
}

void drawMap(sf::RenderWindow& i_window) {
    sf::Image map_image;
    map_image.loadFromFile("resources/images/map_new2.png");
    sf::Texture map;
    map.loadFromImage(map_image);
    sf::Sprite s_map;
    s_map.setTexture(map);
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (TileMap[i][j] == ' ') s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
            if (TileMap[i][j] == 's') s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
            if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
            if (TileMap[i][j] == 'f') s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
            if (TileMap[i][j] == 'h') s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));

            s_map.setPosition(j * 32, i * 32);
            i_window.draw(s_map);
        }
    }
}
