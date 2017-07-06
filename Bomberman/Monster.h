#include "GameSprite.h"
#include "BomberBoy.h"

#pragma once
class Monster : public GameSprite
{
	public:
		void walk(Map map, int x, int y);
		void walk(Map &map);
        void walk(Map &map,sf::RenderWindow &window);
        bool boyDead(BomberBoy &bomberBoy);
       
		void moveRIGHT(sf::Vector2f &pos);
		void moveLEFT(sf::Vector2f &pos);
		void moveDOWN(sf::Vector2f &pos);
		void moveUP(sf::Vector2f &pos);
    
        void aiWin(sf::RenderWindow &window);
    
        int monsterCount = 1;
        bool drawMonster = true;
        bool drawMonster2 = true;
		Monster(BomberBoy *bomberBoy);
		~Monster();

	private:
		BomberBoy *bomberBoy;
};

