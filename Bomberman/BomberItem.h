#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "GameSprite.h"



class BomberItem : public GameSprite
{
    public:
        void items(sf::RenderWindow &window,Map &map);
    
        BomberItem();
        ~BomberItem();
    private:
    
    
};

