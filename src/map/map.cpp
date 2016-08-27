#include <fstream>

#include "map.hpp"
#include "../constants.hpp"

// public
Map::Map(std::string path) : tileset_path {"assets/tileset.png"}, map_width(16), map_height(8)
{
    this->map_data_path = path;

    /*std::ifstream config_doc(this->map_data_path, std::ifstream::binary);
    config_doc >> this->root;

    this->map_width = this->root["width"].asInt();
    this->map_height = this->root["height"].asInt();
    std::vector<int> loaded_map;
    for (int i=0; i < this->root["level"].size(); ++i)
        loaded_map.push_back(this->root["level"][i].asInt());
    this->level = loaded_map;*/
}

int Map::load()
{
    if (this->tmap.load(this->tileset_path, sf::Vector2u(TILE_SIZE_IN_TILESET, TILE_SIZE_IN_TILESET), this->level, this->map_width, this->map_height))
        return 1;
    return 0;
}

void Map::render(sf::RenderWindow& window)
{
    window.draw(this->tmap);
}

void Map::update(sf::RenderWindow& window, sf::Time elapsed)
{

}