#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

// Constants
const unsigned int TILE_SIZE = 32; // Size of one tile
const unsigned int MAP_WIDTH = 20;  // Number of tiles in width
const unsigned int MAP_HEIGHT = 15; // Number of tiles in height

// Function prototypes
void draw_map_editor(sf::RenderWindow& window, const std::vector<std::vector<unsigned char>>& map, const sf::Texture& tileTexture);
void handle_input(sf::RenderWindow& window, std::vector<std::vector<unsigned char>>& map);
void save_map(const std::vector<std::vector<unsigned char>>& map, const std::string& filename);
void load_map(std::vector<std::vector<unsigned char>>& map, const std::string& filename);

int maisn() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Map Editor");
    window.setFramerateLimit(60);

    // Load the tileset texture
    sf::Texture tileTexture;
    if (!tileTexture.loadFromFile("D:/test3/img/Map-1.png")) {
        std::cerr << "Error loading tileset texture" << std::endl;
        return -1;
    }

    // Initialize map data
    std::vector<std::vector<unsigned char>> map(MAP_HEIGHT, std::vector<unsigned char>(MAP_WIDTH, 0));

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        handle_input(window, map);

        window.clear();
        draw_map_editor(window, map, tileTexture);
        window.display();
    }

    // Save the map before exiting
    save_map(map, "map.txt");

    return 0;
}

void draw_map_editor(sf::RenderWindow& window, const std::vector<std::vector<unsigned char>>& map, const sf::Texture& tileTexture) {
    sf::Sprite tileSprite(tileTexture);

    for (unsigned int y = 0; y < map.size(); ++y) {
        for (unsigned int x = 0; x < map[y].size(); ++x) {
            tileSprite.setTextureRect(sf::IntRect(map[y][x] * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
            tileSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(tileSprite);
        }
    }
}

void handle_input(sf::RenderWindow& window, std::vector<std::vector<unsigned char>>& map) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        unsigned int x = mousePos.x / TILE_SIZE;
        unsigned int y = mousePos.y / TILE_SIZE;

        if (x < map[0].size() && y < map.size()) {
            map[y][x] = (map[y][x] + 1) % 10; // Change tile type for testing
        }
    }
}

void save_map(const std::vector<std::vector<unsigned char>>& map, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for saving map" << std::endl;
        return;
    }

    for (const auto& row : map) {
        for (const auto& tile : row) {
            file << static_cast<int>(tile) << ' ';
        }
        file << '\n';
    }
}

void load_map(std::vector<std::vector<unsigned char>>& map, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for loading map" << std::endl;
        return;
    }

    for (auto& row : map) {
        for (auto& tile : row) {
            int tileType;
            file >> tileType;
            tile = static_cast<unsigned char>(tileType);
        }
    }
}
