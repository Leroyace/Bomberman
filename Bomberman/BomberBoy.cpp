#include "BomberBoy.h"
#include "ResourcePath.hpp"
#include <cmath>

const int GameSprite::left[FRAMES] = { 6,7,8 };
const int GameSprite::right[FRAMES] = { 3,4,5 };
const int GameSprite::down[FRAMES] = { 0,1,2 };
const int GameSprite::up[FRAMES] = { 9,10,11 };


void BomberBoy::playerWin(sf::RenderWindow &window)
{
    // Create a texture
    sf::Texture win;
    // Load image file into that texture
    win.loadFromFile(resourcePath() + "bombermanp1w.png");
    
    sf::Sprite playerWin;
    
    playerWin.setTexture(win);
    playerWin.setScale(0.94, 1.04);
    window.draw(playerWin);
    
}

bool BomberBoy::powerUp(int row, int column,Map &map)
{
    if (map.getTile(row,column) == Map::Tile::TilePowerUp) {
        map.DEFAULT_MAP[row][column] = 3;
        return true;
    }
    return false;
}

bool BomberBoy::multiBomb(int row, int column,Map &map)
{
    if (map.getTile(row,column) == Map::Tile::TileMultiBomb) {
        map.DEFAULT_MAP[row][column] = 3;
        return true;
    }
    return false;
}

void BomberBoy::walk(Map &map)
{
	sf::Vector2f pos = sprite.getPosition();
    
	if (facing == RIGHT)
	{
		pos.x += speed;
		this->sprite.setTextureRect(sf::IntRect(right[frame] * 32, 0, 32, 32));
	}
	else if (facing == LEFT)
	{
		pos.x -= speed;
		this->sprite.setTextureRect(sf::IntRect(left[frame] * 32, 0, 32, 32));
	}
	else if (facing == DOWN)
	{
		pos.y += speed;
		this->sprite.setTextureRect(sf::IntRect(down[frame] * 32, 0, 32, 32));
	}
	else if (facing == UP)
	{
		pos.y -= speed;
		this->sprite.setTextureRect(sf::IntRect(up[frame] * 32, 0, 32, 32));
	}
	sprite.setPosition(pos);
	frame = (frame + 1) % 2;
}

BomberBoy::BomberBoy()
{
    if (!texture.loadFromFile(resourcePath() + "BomberBoyWhiteSprite.bmp")) {
        std::cout << "Error loading resource pacman.png" << std::endl;
        return EXIT_FAILURE;
    }

	sf::Image bomberBoyImage = texture.copyToImage();
	bomberBoyImage.createMaskFromColor(sf::Color(0, 0, 0), 0);

	if (!texture.loadFromImage(bomberBoyImage))
	{
		std::cout << "Error masking image resource pacman.png" << std::endl;
	}

	this->sprite.setTexture(texture);
	this->sprite.setScale(2.4,2);
	this->sprite.setOrigin(-6,-7);
	
	this->facing = DOWN;

	this->sprite.setTextureRect(sf::IntRect(down[frame]* 32, 0, 32, 32));
}




BomberBoy::~BomberBoy()
{
}
