#include "BomberBomb.h"
#include "ResourcePath.hpp"
#include <cmath>

const int GameSprite::bomb[FRAMES] = { 1,0,2 };


void BomberBomb::timer()
{
    bombTime = clock.getElapsedTime();
}

void BomberBomb::timeReset()
{
    clock.restart();
}
void BomberBomb::timeReset1()
{
    clock1.restart();
}

void BomberBomb::items(Map &map)
{
    rx = rand() % 25;
    ry = rand() % 21;
    
    dx = rand() % 25;
    dy = rand() % 21;
    
    if (map.getTile(ry, rx) == Map::Tile::TileColumnBlock || map.getTile(ry, rx) == Map::Tile::TileRowBlock)
    {
        itemx = rx;
        itemy = ry;
    }
    else{
        rx = rand() % 25;
        ry = rand() % 21;
    }
    if((map.getTile(dy, dx) == Map::Tile::TileColumnBlock || map.getTile(dy, dx) == Map::Tile::TileRowBlock) && (doorX != rx && doorY != ry))
    {
        doorX = dx;
        doorY = dy;
    }
    else{
        dx = rand() % 25;
        dy = rand() % 21;
    }
    
}

int BomberBomb::randomItems()
{
    int r[2] = {-1,0};
    
    int ri = rand() % 2;
    
    int i = r[ri];
    
    return i;
}



bool BomberBomb::explode(int row, int column,Map &map)
{
    
    if (map.getTile(row, column + 2) == Map::Tile::TileColumnBlock || map.getTile(row, column - 2) == Map::Tile::TileColumnBlock || map.getTile(row + 2, column) == Map::Tile::TileRowBlock|| map.getTile(row - 2, column) == Map::Tile::TileRowBlock)
    {   
        if (getRow() == row || y == row) {
            if (itemy == row && itemx - 2 == column && map.getTile(row, column + 2) == Map::Tile::TileColumnBlock) {
                map.DEFAULT_MAP[row][column + 1] = 3;
                map.DEFAULT_MAP[row][column + 2] = randomItems();
                map.DEFAULT_MAP[row][column + 3] = 3;
            }
            if (itemy == row && itemx + 2 == column && map.getTile(row, column - 2) == Map::Tile::TileColumnBlock) {
                map.DEFAULT_MAP[row][column - 1] = 3;
                map.DEFAULT_MAP[row][column - 2] = randomItems();
                map.DEFAULT_MAP[row][column - 3] = 3;
            }
            if (doorY == row && doorX - 2 == column && map.getTile(row, column + 2) == Map::Tile::TileColumnBlock) {
                map.DEFAULT_MAP[row][column + 1] = 3;
                map.DEFAULT_MAP[row][column + 2] = 9;
                map.DEFAULT_MAP[row][column + 3] = 3;
            }
            if (doorY == row && doorX + 2 == column && map.getTile(row, column - 2) == Map::Tile::TileColumnBlock) {
                map.DEFAULT_MAP[row][column - 1] = 3;
                map.DEFAULT_MAP[row][column - 2] = 9;
                map.DEFAULT_MAP[row][column - 3] = 3;
            }
            if (map.getTile(row, column + 2) == Map::Tile::TileColumnBlock)
            {
                map.DEFAULT_MAP[row][column + 1] = 3;
                map.DEFAULT_MAP[row][column + 2] = 3;
                map.DEFAULT_MAP[row][column + 3] = 3;
            }
            if (map.getTile(row, column - 2) == Map::Tile::TileColumnBlock)
            {
                map.DEFAULT_MAP[row][column - 1] = 3;
                map.DEFAULT_MAP[row][column - 2] = 3;
                map.DEFAULT_MAP[row][column - 3] = 3;
            }
            
        }
        if (getColumn() == column || x == column) {
            if (itemy == row - 2 && itemx == column && map.getTile(row + 2, column) == Map::Tile::TileRowBlock) {
                map.DEFAULT_MAP[row + 1][column] = 3;
                map.DEFAULT_MAP[row + 2][column] = randomItems();
                map.DEFAULT_MAP[row + 3][column] = 3;
            }
            if (itemy == row + 2 && itemx == column && map.getTile(row - 2, column) == Map::Tile::TileRowBlock) {
                map.DEFAULT_MAP[row - 1][column] = 3;
                map.DEFAULT_MAP[row - 2][column] = randomItems();
                map.DEFAULT_MAP[row - 3][column] = 3;
            }
            if (doorY == row - 2 && doorX == column && map.getTile(row + 2, column) == Map::Tile::TileRowBlock) {
                map.DEFAULT_MAP[row + 1][column] = 3;
                map.DEFAULT_MAP[row + 2][column] = 9;
                map.DEFAULT_MAP[row + 3][column] = 3;
            }
            if (doorY == row + 2 && doorX == column && map.getTile(row - 2, column) == Map::Tile::TileRowBlock) {
                map.DEFAULT_MAP[row - 1][column] = 3;
                map.DEFAULT_MAP[row - 2][column] = 9;
                map.DEFAULT_MAP[row - 3][column] = 3;
            }
            if (map.getTile(row + 2, column) == Map::Tile::TileRowBlock)
            {   
                map.DEFAULT_MAP[row + 1][column] = 3;
                map.DEFAULT_MAP[row + 2][column] = 3;
                map.DEFAULT_MAP[row + 3][column] = 3;
            }
            if (map.getTile(row - 2, column) == Map::Tile::TileRowBlock)
            {
                map.DEFAULT_MAP[row - 1][column] = 3;
                map.DEFAULT_MAP[row - 2][column] = 3;
                map.DEFAULT_MAP[row - 3][column] = 3;
            }
            
        }
        
        return true;
    }
    return false;
}

void BomberBomb::kill(int x,int y, Monster & monster,BomberBoy &bomberBoy)
{
    sf::Vector2f monsterPos = monster.getSprite().getPosition();
    sf::Vector2f playerPos = bomberBoy.getSprite().getPosition();
    
    if (x == monsterPos.x && y == monsterPos.y && x == playerPos.x && y == playerPos.y) {
        monster.drawMonster = false;
        bomberBoy.drawBomberBoy = false;
        monster.monsterCount -= 1;
    }
    if (x == monsterPos.x && y == monsterPos.y) {
        monster.monsterCount -= 1;
        monster.drawMonster = false;
        monster.setPosition(0, 0);
    }
    if (x == playerPos.x && y == playerPos.y) {
        bomberBoy.drawBomberBoy = false;
    }

}



void BomberBomb::blow(sf::RenderWindow &window,Map &map,int row, int column,Monster &monster,BomberBoy &bomberBoy)
{
    sf::Vector2f right = sprite.getPosition();
    sf::Vector2f left = sprite.getPosition();
    sf::Vector2f up = sprite.getPosition();
    sf::Vector2f down = sprite.getPosition();
    
    // Create a texture
    sf::Texture fire;
    // Load image file into that texture
    fire.loadFromFile(resourcePath() + "bomberman_bomb_sheet.png");
    
    std::vector<sf::Sprite> bomb(20, sf::Sprite(fire));
    
    setRange(range);
    rangeRight = 0;
    rangeUp = 0;
    rangeDown = 0;
    rangeLeft = 0;
    
    // Loop over the elements of the vector of sprites
    for (int i = 0; i < bomb.size(); i++) {
        bomb[i].setScale(2.5,2.4);
        bomb[i].setOrigin(-14,-12);
        if (time > 3)
        {
            map.DEFAULT_MAP[row][column] = 3;
            if (i == range + 1 && !map.isCollision(right.y / 32, right.x / 32 + 1)) {
                right.x += 32;
                bomb[i].setPosition(right.x,right.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 30, 16, 16));
                window.draw(bomb[i]);
                rangeRight = i;
            }
            if (i <= range && !map.isCollision(right.y / 32, right.x / 32 + 1)) {
                right.x += 32;
                bomb[i].setPosition(right.x,right.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 60, 16, 16));
                window.draw(bomb[i]);
            }
            if (i == range + 1 && !map.isCollision(left.y / 32, left.x / 32 - 1)) {
                left.x -= 32;
                bomb[i].setPosition(left.x,left.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 210, 30, 16, 16));
                window.draw(bomb[i]);
                rangeLeft = i;
            }
            if (i <= range && !map.isCollision(left.y / 32, left.x / 32 - 1)) {
                left.x -= 32;
                bomb[i].setPosition(left.x,left.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 60, 16, 16));
                window.draw(bomb[i]);
            }
            if (i == range + 1 && !map.isCollision(down.y / 32 + 1, down.x / 32)) {
                down.y += 32;
                bomb[i].setPosition(down.x,down.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 240, 60, 16, 16));
                window.draw(bomb[i]);
                rangeDown = i;
            }
            if (i <= range && !map.isCollision(down.y / 32 + 1, down.x / 32)) {
                down.y += 32;
                bomb[i].setPosition(down.x,down.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 0, 16, 16));
                window.draw(bomb[i]);
            }
            if (i == range + 1 && !map.isCollision(up.y / 32 - 1, up.x / 32)) {
                up.y -= 32;
                bomb[i].setPosition(up.x,up.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 240, 0, 16, 16));
                window.draw(bomb[i]);
                rangeUp = i;
            }
            if (i <= range && !map.isCollision(up.y / 32 - 1, up.x / 32)) {
                up.y -= 32;
                bomb[i].setPosition(up.x,up.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 0, 16, 16));
                window.draw(bomb[i]);
                
            }
            kill(right.x, right.y, monster,bomberBoy);
            kill(left.x, left.y, monster,bomberBoy);
            kill(down.x, down.y, monster,bomberBoy);
            kill(up.x, up.y, monster,bomberBoy);
        }
        
    }
    if (time > 4)
    {
        if (rangeRight != range + 1) {
            explode(right.y / 32, right.x /32, map);
        }
        if (rangeLeft != range + 1) {
            explode(left.y / 32, left.x /32, map);
        }
        if (rangeDown != range + 1 ) {
            explode(down.y / 32, down.x /32, map);
        }
        if (rangeUp != range + 1) {
            explode(up.y / 32, up.x /32, map);
        }
    }
}


void BomberBomb::bomb(int row, int column,Map &map)
{
    timer();
    setBomberTime(bombTime.asSeconds(),0,0,0,0);
    
    map.DEFAULT_MAP[row][column] = 7;
    
    if (time == 0 || time == 2)
    {
        this->sprite.setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 0, 30 ,16, 16));
    }
    else if (time == 1  || time == 3)
    {
        this->sprite.setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 0, 0, 16, 16));
    }
    if (time > 3)
    {
        this->sprite.setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 240, 30, 16, 16));
    }
}

void BomberBomb::bombs(sf::RenderWindow &window,Map &map,int x , int y)
{
    // Create a texture
    sf::Texture fire;
    sf::Sprite bombs;
    fire.loadFromFile(resourcePath() + "bomberman_bomb_sheet.png");
    b bomb(40, sf::Sprite(fire));
    // Load image file into that texture
    
    bombs.setTexture(fire);
  
    
    setRange(range);
    
    setBombQuantity(bombCount);
    
    bombTime1 = clock1.getElapsedTime();
    
    setBomberTime(time,bombTime1.asSeconds(),0,0,0);
    
    rangeRight = 0;
    rangeUp = 0;
    rangeDown = 0;
    rangeLeft = 0;
    
    bombs.setPosition(x,y);
  
    sf::Vector2f right = bombs.getPosition();
    sf::Vector2f left = bombs.getPosition();
    sf::Vector2f up = bombs.getPosition();
    sf::Vector2f down = bombs.getPosition();
    bombs.setScale(2.5,2.4);
    bombs.setOrigin(-14,-12);
   
    map.DEFAULT_MAP[y/32][x/32] = 7;
    if (time1 == 0 || time1 == 2)
    {
        bombs.setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 0, 30 ,16, 16));
        
    }
    else if (time1 == 1  || time1 == 3)
    {
        bombs.setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 0, 0, 16, 16));
        
    }
    if (time1 > 3)
    {
        bombs.setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 240, 30, 16, 16));
      
    }
    window.draw(bombs);

    // Loop over the elements of the vector of sprites
    for (int i = 0; i < bombCount + range + 1; i++) {
        bomb[i].setScale(2.5,2.4);
        bomb[i].setOrigin(-14,-12);
        
        if (time1 > 3)
        {
            map.DEFAULT_MAP[y/32][x/32] = 3;
            if (i == range + 1 && !map.isCollision(right.y / 32, right.x / 32 + 1)) {
                right.x += 32;
                bomb[i].setPosition(right.x,right.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 30, 16, 16));
                window.draw(bomb[i]);
                rangeRight = i;
            }
            if (i <= range && !map.isCollision(right.y / 32, right.x / 32 + 1)) {
                right.x += 32;
                bomb[i].setPosition(right.x,right.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 60, 16, 16));
                window.draw(bomb[i]);
            }
            if (i == range + 1 && !map.isCollision(left.y / 32, left.x / 32 - 1)) {
                left.x -= 32;
                bomb[i].setPosition(left.x,left.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 210, 30, 16, 16));
                window.draw(bomb[i]);
                rangeLeft = i;
                
            }
            if (i <= range && !map.isCollision(left.y / 32, left.x / 32 - 1)) {
                left.x -= 32;
                bomb[i].setPosition(left.x,left.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 60, 16, 16));
                window.draw(bomb[i]);
                
            }
            if (i == range + 1 && !map.isCollision(down.y / 32 + 1, down.x / 32)) {
                down.y += 32;
                bomb[i].setPosition(down.x,down.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 240, 60, 16, 16));
                window.draw(bomb[i]);
                rangeDown = i;
            }
            if (i <= range && !map.isCollision(down.y / 32 + 1, down.x / 32)) {
                down.y += 32;
                bomb[i].setPosition(down.x,down.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 0, 16, 16));
                window.draw(bomb[i]);
            }
            if (i == range + 1 && !map.isCollision(up.y / 32 - 1, up.x / 32)) {
                up.y -= 32;
                bomb[i].setPosition(up.x,up.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 240, 0, 16, 16));
                window.draw(bomb[i]);
                rangeUp = i;
            }
            if (i <= range && !map.isCollision(up.y / 32 - 1, up.x / 32)) {
                up.y -= 32;
                bomb[i].setPosition(up.x,up.y);
                bomb[i].setTextureRect(sf::IntRect(GameSprite::bomb[frame] * 270, 0, 16, 16));
                window.draw(bomb[i]);
            }
        }
    }
    if (time1 > 4)
    {   setPos(bombs.getPosition().x, bombs.getPosition().y);
        if (rangeRight != range + 1) {
            explode(right.y / 32, right.x /32, map);
        }
        if (rangeLeft != range + 1) {
            explode(left.y / 32, left.x /32, map);
        }
        if (rangeDown != range + 1 ) {
            explode(down.y / 32, down.x /32, map);
        }
        if (rangeUp != range + 1) {
            explode(up.y / 32, up.x /32, map);
        }
    }
}



BomberBomb::BomberBomb()
{
    if (!texture.loadFromFile(resourcePath() + "bomberman_bomb_sheet.png")) {
        std::cout << "Error loading resource bomberman_bomb_sheet.png" << std::endl;
        return EXIT_FAILURE;
    }

	sf::Image bomberBombImage = texture.copyToImage();

	if (!texture.loadFromImage(bomberBombImage))
	{
		std::cout << "Error masking image resource bomberman_bomb_sheet.png" << std::endl;
	}
    
    this->sprite.setTexture(texture);
	this->sprite.setScale(2.5,2.4);
	this->sprite.setOrigin(-14,-12);
    
	this->sprite.setTextureRect(sf::IntRect(0, 30, 16, 16));
}

void BomberBomb::setBomberTime(int time,int time1,int time2,int time3,int time4)
{
    this->time = time;
    this->time1 = time1;
    this->time2 = time2;
    this->time3 = time3;
    this->time4 = time4;
}

void BomberBomb::setRange(int range)
{
    this->range = range;
}

void BomberBomb::setBombQuantity(int bombCount)
{
    this->bombCount = bombCount;
}

void BomberBomb::setPos(int x, int y)
{
    this->x = x / 32;
    this->y = y / 32;
}

BomberBomb::~BomberBomb()
{
    
}
