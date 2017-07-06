#include "Monster.h"
#include "ResourcePath.hpp"

void Monster::walk(Map map, int x, int y)
{
	int distY = y - getRow();
	int distX = x - getColumn();
	
	sf::Vector2f pos = sprite.getPosition();

	if (map.isTileIntersection(getRow(), getColumn()) && rowBoundary() && columnBoundary())
	{
		if (distX < 0)
		{
			moveLEFT(pos);
		}
		else if (distX >0)
		{
			moveRIGHT(pos);
		}
		else if (distY < 0)
		{
			moveUP(pos);
		}
		else if (distY >0)
		{
			moveDOWN(pos);
		}
	}
	else if (facing == UP)
	{
		moveUP(pos);
	}
	else if (facing == DOWN)
	{
		moveDOWN(pos);
	}
	else if (facing == LEFT)
	{
		moveLEFT(pos);
	}
	else if (facing == RIGHT)
	{
		moveRIGHT(pos);
	}

	sprite.setPosition(pos);
	frame = (frame + 1) % 3;
}

bool Monster::boyDead(BomberBoy &bomberBoy)
{
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f boyPos = bomberBoy.getSprite().getPosition();

    
    if (pos == boyPos) {
        return true;
    }
    
    return false;
    
}


void Monster::walk(Map & map)
{
    sf::Vector2f pos = sprite.getPosition();
    
    if (columnBoundary())
    {
        if (facing == DOWN) {
            
            if (!map.isCollision(getRow() + 1, getColumn()) || !rowBoundary())
            {
                setFacing(GameSprite::DOWN);
                moveDOWN(pos);
            }
            else{
                if (map.isTileIntersection(getRow(), getColumn()) || map.isTileIntersection(getRow(), getColumn() + 1) || map.isTileIntersection(getRow(), getColumn() - 1) || map.isTileIntersection(getRow() + 1, getColumn()) || map.isTileIntersection(getRow() - 1, getColumn())){
                    if (!map.isCollision(getRow(), getColumn() - 1)) {
                        setFacing(GameSprite::LEFT);
                    }
                    if (!map.isCollision(getRow(), getColumn() + 1)) {
                        setFacing(GameSprite::RIGHT);
                    }
                    if (!map.isCollision(getRow() - 1, getColumn()) && facing == DOWN) {
                        setFacing(GameSprite::UP);
                    }
                }
    
            }
            
        }
    }
    
    if (columnBoundary())
    {
        if (facing == UP) {
            
            if (!map.isCollision(getRow() - 1, getColumn()) || !rowBoundary())
            {
                setFacing(GameSprite::UP);
                moveUP(pos);
                
            }
            else{
                if (map.isTileIntersection(getRow(), getColumn()) || map.isTileIntersection(getRow(), getColumn() + 1) || map.isTileIntersection(getRow(), getColumn() - 1) || map.isTileIntersection(getRow() + 1, getColumn()) || map.isTileIntersection(getRow() - 1, getColumn())){
                    if (!map.isCollision(getRow(), getColumn() - 1)) {
                        setFacing(GameSprite::LEFT);
                    }
                    if (!map.isCollision(getRow(), getColumn() + 1)) {
                        setFacing(GameSprite::RIGHT);
                    }
                    if (!map.isCollision(getRow() + 1, getColumn()) && facing == UP) {
                        setFacing(GameSprite::DOWN);
                    }
                }
            }
        }
    }
    
    if (rowBoundary())
    {
        if (facing == LEFT) {
            if (!map.isCollision(getRow(), getColumn() - 1) || !columnBoundary())
            {
                setFacing(GameSprite::LEFT);
                moveLEFT(pos);
            }
            else{
                if (map.isTileIntersection(getRow(), getColumn()) || map.isTileIntersection(getRow(), getColumn() + 1) || map.isTileIntersection(getRow(), getColumn() - 1) || map.isTileIntersection(getRow() + 1, getColumn()) || map.isTileIntersection(getRow() - 1, getColumn())){
                    if (!map.isCollision(getRow() - 1, getColumn())) {
                        setFacing(GameSprite::UP);
                    }
                    if (!map.isCollision(getRow() + 1, getColumn())) {
                        setFacing(GameSprite::DOWN);
                    }
                    if (!map.isCollision(getRow(), getColumn() + 1) && facing == LEFT) {
                        setFacing(GameSprite::RIGHT);
                    }
                }
            }
            
        }
    }
    
    if (rowBoundary())
    {
        if (facing == RIGHT) {
                
            if (!map.isCollision(getRow(), getColumn() + 1) || !columnBoundary())
            {
                setFacing(GameSprite::RIGHT);
                moveRIGHT(pos);
            }
            else{
                if (map.isTileIntersection(getRow(), getColumn()) || map.isTileIntersection(getRow(), getColumn() + 1) || map.isTileIntersection(getRow(), getColumn() - 1) || map.isTileIntersection(getRow() + 1, getColumn()) || map.isTileIntersection(getRow() - 1, getColumn())){
                    if (!map.isCollision(getRow() - 1, getColumn())) {
                        setFacing(GameSprite::UP);
                    }
                    if (!map.isCollision(getRow() + 1, getColumn())) {
                        setFacing(GameSprite::DOWN);
                    }
                    if (!map.isCollision(getRow(), getColumn() - 1) && facing == RIGHT) {
                        setFacing(GameSprite::LEFT);
                    }
                }
            }
        }
    }
    sprite.setPosition(pos);
}

void Monster::walk(Map & map,sf::RenderWindow &window)
{
    // Create a texture
    sf::Texture monster2;
    // Load image file into that texture
    monster2.loadFromFile(resourcePath() + "BomberBoy.png");
    
    sf::Sprite monster;
    
    this->f = UP;
    
    monster.setTexture(monster2);
    monster.setScale(2.5,2.5);
    monster.setOrigin(-12,-12);
    monster.setPosition(32* 25, 32* 21);
    monster.setTextureRect(sf::IntRect(0, 120, 16, 24));
    
    sf::Vector2f pos = monster.getPosition();
    
    int getRow = monster.getPosition().y / 32;
    
    int getColumn = monster.getPosition().x / 32;
    
    if (columnBoundary())
    {
        if (f == DOWN) {
            
            if (!map.isCollision(getRow + 1, getColumn) || !rowBoundary())
            {
                setFacing(GameSprite::DOWN);
                moveDOWN(pos);
            }
            else{
                if (map.isTileIntersection(getRow, getColumn) || map.isTileIntersection(getRow, getColumn + 1) || map.isTileIntersection(getRow, getColumn - 1) || map.isTileIntersection(getRow + 1, getColumn) || map.isTileIntersection(getRow - 1, getColumn)){
                    if (!map.isCollision(getRow, getColumn - 1)) {
                        setFacing(GameSprite::LEFT);
                    }
                    if (!map.isCollision(getRow, getColumn + 1)) {
                        setFacing(GameSprite::RIGHT);
                    }
                    if (!map.isCollision(getRow - 1, getColumn) && f == DOWN) {
                        setFacing(GameSprite::UP);
                    }
                }
                
            }
            
        }
    }
    
   
        if (f == UP) {
            
            if (!map.isCollision(getRow - 1, getColumn) || !rowBoundary())
            {
                setFacing(GameSprite::UP);
                moveUP(pos);
                
            }
            else{
                if (map.isTileIntersection(getRow, getColumn) || map.isTileIntersection(getRow, getColumn + 1) || map.isTileIntersection(getRow, getColumn - 1) || map.isTileIntersection(getRow + 1, getColumn) || map.isTileIntersection(getRow - 1, getColumn)){
                    if (!map.isCollision(getRow, getColumn - 1)) {
                        setFacing(GameSprite::LEFT);
                    }
                    if (!map.isCollision(getRow, getColumn + 1)) {
                        setFacing(GameSprite::RIGHT);
                    }
                    if (!map.isCollision(getRow + 1, getColumn) && f == UP) {
                        setFacing(GameSprite::DOWN);
                    }
                }
            }
        }
    
    
    if (rowBoundary())
    {
        if (f == LEFT) {
            if (!map.isCollision(getRow, getColumn - 1) || !columnBoundary())
            {
                setFacing(GameSprite::LEFT);
                moveLEFT(pos);
            }
            else{
                if (map.isTileIntersection(getRow, getColumn) || map.isTileIntersection(getRow, getColumn + 1) || map.isTileIntersection(getRow, getColumn - 1) || map.isTileIntersection(getRow + 1, getColumn) || map.isTileIntersection(getRow - 1, getColumn)){
                    if (!map.isCollision(getRow - 1, getColumn)) {
                        setFacing(GameSprite::UP);
                    }
                    if (!map.isCollision(getRow + 1, getColumn)) {
                        setFacing(GameSprite::DOWN);
                    }
                    if (!map.isCollision(getRow, getColumn + 1) && f == LEFT) {
                        setFacing(GameSprite::RIGHT);
                    }
                }
            }
            
        }
    }
    
    if (rowBoundary())
    {
        if (f == RIGHT) {
            
            if (!map.isCollision(getRow, getColumn + 1) || !columnBoundary())
            {
                setFacing(GameSprite::RIGHT);
                moveRIGHT(pos);
            }
            else{
                if (map.isTileIntersection(getRow, getColumn) || map.isTileIntersection(getRow, getColumn + 1) || map.isTileIntersection(getRow, getColumn - 1) || map.isTileIntersection(getRow + 1, getColumn) || map.isTileIntersection(getRow - 1, getColumn)){
                    if (!map.isCollision(getRow - 1, getColumn)) {
                        setFacing(GameSprite::UP);
                    }
                    if (!map.isCollision(getRow + 1, getColumn)) {
                        setFacing(GameSprite::DOWN);
                    }
                    if (!map.isCollision(getRow, getColumn - 1) && f == RIGHT) {
                        setFacing(GameSprite::LEFT);
                    }
                }
            }
        }
    }
    monster.setPosition(pos);
    
    window.draw(monster);
}

void Monster::moveRIGHT(sf::Vector2f &pos)
{
	f = RIGHT;
	pos.x = pos.x + 1;
	//this->sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
}

void Monster::moveLEFT(sf::Vector2f &pos)
{
	f = LEFT;

	pos.x = pos.x - 1;
	//this->sprite.setTextureRect(sf::IntRect(left[frame] * 16, 0, 16, 16));
}

void Monster::moveDOWN(sf::Vector2f &pos)
{
	f = DOWN;

	pos.y = pos.y + 1;
	//this->sprite.setTextureRect(sf::IntRect(down[frame] * 16, 0, 16, 16));
}

void Monster::moveUP(sf::Vector2f &pos)
{
	f = UP;
	pos.y = pos.y - 1;

	//this->sprite.setTextureRect(sf::IntRect(up[frame] * 16, 0, 16, 16));
}


void Monster::aiWin(sf::RenderWindow &window)
{
    
    // Create a texture
    sf::Texture win;
    // Load image file into that texture
    win.loadFromFile(resourcePath() + "bomberman_ia.png");
    
    sf::Sprite aiWin;
    
    aiWin.setTexture(win);
    aiWin.setScale(0.94, 1.04);
    window.draw(aiWin);
    
}


Monster::Monster(BomberBoy *bomberBoy)
{
	this->bomberBoy = bomberBoy;

	if (!texture.loadFromFile(resourcePath() + "BomberBoy.png"))
	{
		std::cout << "Error loading resource BomberBoy.png" << std::endl;
	}

	sf::Image monsterImage = texture.copyToImage();
	
	if (!texture.loadFromImage(monsterImage))
	{
		std::cout << "Error masking image resource BomberBoy.png" << std::endl;
	}

	this->sprite.setTexture(texture);
    this->sprite.setScale(2.5,2.5);
    this->sprite.setOrigin(-12,-12);

	this->facing = UP;

	this->sprite.setTextureRect(sf::IntRect(0, 120, 16, 24));
}


Monster::~Monster()
{
}
