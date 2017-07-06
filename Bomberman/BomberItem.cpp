#include "BomberItem.h"
#include "ResourcePath.hpp"
#include <cmath>

const int GameSprite::item[FRAMES] = { 3,4,5 };

void BomberItem::items(sf::RenderWindow &window,Map &map)
{
    // Create a texture
    sf::Texture block;
    // Load image file into that texture
    block.loadFromFile(resourcePath() + "BombermanItem.png");
    
    std::vector<sf::Sprite> blocks(131, sf::Sprite(block));
    for (int row = 0; row < map.COLUMN_COUNT; row++)
    {
        for (int col = 0; col < map.ROW_COUNT; col++)
        {
            Map::Tile tile = map.getTile(col, row);
            // Loop over the elements of the vector of sprites
            for (int i = 0; i < blocks.size(); i++)
            {
                blocks[i].setScale(4,4);
                blocks[i].setOrigin(2,3.5);
                blocks[i].setTextureRect(sf::IntRect(59, 0, 16, 16));
                
                if (tile == Map::Tile::TileRowBlock || tile == Map::Tile::TileColumnBlock)
                {
                    blocks[i].setPosition((row + 1) * 32,(col + 1) * 32);
                    window.draw(blocks[i]);
                }
                if (tile == Map::Tile::TilePowerUp)
                {
                    blocks[i].setPosition((row + 1) * 32,(col + 1) * 32);
                    blocks[i].setTextureRect(sf::IntRect(299, 0, 16, 16));
                    window.draw(blocks[i]);
                }
                if (tile == Map::Tile::TileMultiBomb)
                {
                    
                    blocks[i].setPosition((row + 1) * 32,(col + 1) * 32);
                    blocks[i].setTextureRect(sf::IntRect(329, 0, 16, 16));
                    window.draw(blocks[i]);
                }
                if (tile == Map::Tile::TileDoor)
                {
                    blocks[i].setPosition((row + 1) * 32,(col + 1) * 32);
                    blocks[i].setScale(4.35,4.3);
                    blocks[i].setTextureRect(sf::IntRect(0, 0, 16, 16));
                    window.draw(blocks[i]);
                }
                /*if (tile == Map::Tile::TileMultiBomb)
                {
                    blocks[i].setPosition((row + 1) * 32,(col + 1) * 32);
                    blocks[i].setTextureRect(sf::IntRect(388, 0, 16, 16));
                    window.draw(blocks[i]);
                }*/
            }
        }
    }
}

BomberItem::BomberItem()
{
    if (!texture.loadFromFile(resourcePath() + "BombermanItem.png")) {
        std::cout << "Error loading resource BombermanItem.png" << std::endl;
        return EXIT_FAILURE;
    }

	sf::Image bomberItemImage = texture.copyToImage();

	if (!texture.loadFromImage(bomberItemImage))
	{
		std::cout << "Error masking image resource pacman.png" << std::endl;
	}

	this->sprite.setTexture(texture);
	this->sprite.setScale(4,3);
    this->sprite.setOrigin(3, 8);
	
	this->sprite.setTextureRect(sf::IntRect(58, 0, 16, 16));
}




BomberItem::~BomberItem()
{
}
