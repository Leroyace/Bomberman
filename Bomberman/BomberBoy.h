#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "GameSprite.h"



class BomberBoy : public GameSprite
{
	public:
        void walk(Map &map);
        bool powerUp(int row, int column,Map &map);
        bool multiBomb(int row, int column,Map &map);
        void playerWin(sf::RenderWindow &window);
        int speed = 16;
        bool drawBomberBoy = true;
		BomberBoy();
		~BomberBoy();
    
	private:


};


