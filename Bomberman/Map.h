#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Map
{
public:
	static const int ROW_COUNT = 23;
	static const int COLUMN_COUNT = 27;
    static int DEFAULT_MAP[ROW_COUNT][COLUMN_COUNT];
    static const int RE_DEFAULT_MAP[ROW_COUNT][COLUMN_COUNT];
    
	enum Tile {
        TileMultiBomb = -1,
		TilePowerUp = 0,
		TileWall = 1,
		TileBlock = 2,
		TileEmpty = 3,
		TileColumnBlock = 4,
		TileBomberBoy = 5,
		TileRowBlock = 6,
        TileBomb = 7,
		TileIntersectionBlock = 8,
		TileDoor = 9,
		TileIntersection = 10
	};

	Tile getTile(int row, int column);
	bool isTileIntersection(int row, int column);
	bool isCollision(int row, int column);
	sf::Sprite getSprite();
    
	void printAdjacencyList();
    
    void reload();
    Tile getReTile(int row, int column);

	Map();
	~Map();

	private:
		sf::Texture texture;
		sf::Sprite sprite;
		
		static const int INTERSECTION_MAP[ROW_COUNT][COLUMN_COUNT];
};

