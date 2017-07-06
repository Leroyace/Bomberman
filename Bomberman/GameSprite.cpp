#include "GameSprite.h"

bool GameSprite::rowBoundary()
{
	return ((int)sprite.getPosition().y % 32 == 0);
}
bool GameSprite::columnBoundary()
{
	return ((int)sprite.getPosition().x % 32 == 0);
}
int GameSprite::getColumn()
{
	return sprite.getPosition().x / 32;
}

int GameSprite::getRow()
{
    return sprite.getPosition().y / 32;
}


sf::Sprite GameSprite::getSprite()
{
	return sprite;
}

void GameSprite::setFacing(Facing facing)
{
	this->facing = facing;
}

void GameSprite::setPosition(int row, int column)
{
	sprite.setPosition(row * 32, column * 32);
}


GameSprite::GameSprite()
{
}


GameSprite::~GameSprite()
{
}
