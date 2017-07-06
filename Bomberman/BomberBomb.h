#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "GameSprite.h"
#include "BomberBoy.h"
#include "Monster.h"

class BomberBomb : public GameSprite
{
	public:
        int time,time1,time2,time3,time4;
        int range,rangeUp,rangeLeft,rangeRight,rangeDown;
        int bombCount = 1;
        int door = 0;
        int x,y;
        int itemx,itemy,rx,ry,doorX,doorY,dx,dy;
      
    
        void kill(int x,int y, Monster & monster,BomberBoy &bomberBoy);
        void bomb(int row, int column,Map &map);
        void timer();
        void setBomberTime(int time,int time1,int time2,int time3,int time4);
        void timeReset();
        void timeReset1();
        void blow(sf::RenderWindow &window,Map &map,int row,int column,Monster &monster,BomberBoy &bomberBoy);
        void setRange(int range);
        void setBombQuantity(int bombCount);
        bool explode(int row,int column,Map &map);
        void bombs(sf::RenderWindow &window,Map &map,int x,int y);
        void setPos(int x, int y);
        void items(Map &map);
        int randomItems();
    
        typedef std::vector<sf::Sprite> b;
    
		BomberBomb();
		~BomberBomb();
    
	private:


};


