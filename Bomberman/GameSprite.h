#pragma once
#include "Map.h"
const int FRAMES = 3;

class GameSprite
{
public:
	enum Facing
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
        L,
        R,
        U,
        D
        
	};

	bool rowBoundary();
	bool columnBoundary();

	int getColumn();
	int getRow();
    
	//virtual void walk(Map &map) = 0;

	GameSprite();
	~GameSprite();

	sf::Sprite getSprite();
	void setFacing(Facing facing);
	void setPosition(int row, int column);

	protected:
		Facing facing,f;
    
		int frame = 0;

		static const int left[FRAMES];
		static const int right[FRAMES];
		static const int down[FRAMES];
		static const int up[FRAMES];
    
        static const int item[FRAMES];
    
        static const int bomb[FRAMES];
        static const int fire[FRAMES];
    
		sf::Sprite sprite;
		sf::Texture texture;
        sf::Clock clock,clock1,clock2,clock3,clock4;
        sf::Time bombTime,bombTime1,bombTime2,bombTime3,bombTime4;

};

