
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <list>
#include <queue>

#include "Map.h"
#include "BomberBoy.h"
#include "BomberItem.h"
#include "BomberBomb.h"
#include "Monster.h"
#include "ResourcePath.hpp"


int main(int, char const**)
{
    bool debug = true;
    bool drawGridCells = false;
    bool drawEmptyPath = false;
    bool drawItem = true;
    bool drawBomb = false;
    bool drawBombs = false;
    bool timeStart = false;
    bool drop = false;
    bool drop1 = false;
    bool playerWin = false;
    bool aiWin = false;
    
    int row,col;
    Map map;
    BomberBoy bomberBoy;
    BomberItem bomberItem;
    BomberBomb bomberBomb;
    Monster monster (&bomberBoy);
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(950, 805), "BomberMan");
    window.setFramerateLimit(100);
   
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
   
    map.printAdjacencyList();
    
    bomberBoy.setPosition(1,1);
    
    monster.setPosition(1,21);
    
    // Load a music to play
    sf::Music music,bomb;
    if (!music.openFromFile(resourcePath() + "bomberman_orchestra.wav")) {
        return EXIT_FAILURE;
    }
    bomb.openFromFile(resourcePath() + "bomb.wav");
    // Play the music
    music.play();
    
    // Start the game loop
    while (window.isOpen())
    {
        bomberBomb.items(map);
        
        if (monster.boyDead(bomberBoy)) {
            bomberBoy.drawBomberBoy = false;
            aiWin = true;
        }

        if (bomberBomb.time > 4) {
            bomberBomb.timeReset();
            drawBomb = false;
            drop = false;
        }
        if(bomberBomb.time1 > 4){
            bomberBomb.timeReset1();
            drawBombs = false;
            drop1 = false;
        }
        if (bomberBoy.powerUp(bomberBoy.getRow(), bomberBoy.getColumn(), map) && bomberBomb.range <= 8) {
            bomberBomb.range += 2;
        }
        if (bomberBoy.multiBomb(bomberBoy.getRow(), bomberBoy.getColumn(), map) && bomberBomb.bombCount <= 4) {
            bomberBomb.bombCount += 1;
        }
        if (map.getTile(bomberBoy.getRow(), bomberBoy.getColumn()) == Map::Tile::TileDoor && monster.monsterCount == 0) {
            playerWin = true;
            map.reload();
            monster.drawMonster = true;
            monster.setPosition(25,21);
            bomberBoy.setPosition(1,1);
        }
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            //
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (!drop) {
                    bomberBomb.timeReset();
                    drawBomb = true;
                    row = bomberBoy.getRow();
                    col = bomberBoy.getColumn();
                    bomberBomb.setPosition(bomberBoy.getColumn(),bomberBoy.getRow());
                }
                if(drop && !drawBombs && bomberBomb.bombCount > 1){
                    drawBombs = true;
                    bomberBomb.timeReset1();
                    bomberBomb.x = bomberBoy.getSprite().getPosition().x;
                    bomberBomb.y = bomberBoy.getSprite().getPosition().y;
                }
            }
            //
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if (bomberBoy.columnBoundary())
                {
                    if (!map.isCollision(bomberBoy.getRow() + 1, bomberBoy.getColumn()) || !bomberBoy.rowBoundary())
                    {
                         if (music.getStatus() == sf::SoundSource::Status::Stopped)
                         {
                            music.play();
                         }
                        bomberBoy.setFacing(GameSprite::DOWN);
                        bomberBoy.walk(map);
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                
                if (bomberBoy.columnBoundary())
                {
                    if (!map.isCollision(bomberBoy.getRow() - 1, bomberBoy.getColumn()) || !bomberBoy.rowBoundary())
                    {
                        bomberBoy.setFacing(GameSprite::UP);
                        bomberBoy.walk(map);
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (bomberBoy.rowBoundary())
                {
                    if (!map.isCollision(bomberBoy.getRow(), bomberBoy.getColumn() - 1) || !bomberBoy.columnBoundary())
                    {
                        bomberBoy.setFacing(GameSprite::LEFT);
                        bomberBoy.walk(map);
                    }
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (bomberBoy.rowBoundary())
                {
                    if (!map.isCollision(bomberBoy.getRow(), bomberBoy.getColumn() + 1) || !bomberBoy.columnBoundary())
                    {
                        bomberBoy.setFacing(GameSprite::RIGHT);
                        bomberBoy.walk(map);
                    }
                }
            }
        }

        // Clear screen
        window.clear();
        if (debug)
        {
            std::cout << "actual position: (" << bomberBoy.getSprite().getPosition().x << ", " << bomberBoy.getSprite().getPosition().y << ")" << std::endl;
            std::cout << "grid position: (" << bomberBoy.getRow() << "," << bomberBoy.getColumn() << ")" << std::endl;
            
            std::cout << "map tile: " << map.getTile(bomberBoy.getRow(), bomberBoy.getColumn()) << std::endl;
        }
        
        
        // Draw the sprite
       
        window.draw(map.getSprite());
        if (playerWin)
        {
            drawItem = false;
            bomberBoy.drawBomberBoy = false;
            monster.drawMonster = false;
            drawBomb = false;
            drawBombs = false;
            bomberBoy.playerWin(window);
        }
        if ((aiWin || !bomberBoy.drawBomberBoy) && !playerWin)
        {
            drawItem = false;
            monster.drawMonster = false;
            drawBomb = false;
            drawBombs = false;
            monster.aiWin(window);
        }
        if (bomberBoy.drawBomberBoy)
        {
            window.draw(bomberBoy.getSprite());
        }
        if (monster.drawMonster) {
            monster.walk(map);
            window.draw(monster.getSprite());
        }
        /*if (monster.drawMonster2) {
            monster.walk(map,window);
        }*/
        if (drawItem)
        {
            bomberItem.items(window, map);
        }
        if (drawBomb)
        {
            drop = true;
            bomberBomb.bomb(row,col,map);
            bomberBomb.blow(window,map,row,col,monster,bomberBoy);
            window.draw(bomberBomb.getSprite());
        }
        if (drawBombs && bomberBomb.bombCount > 1) {
            drop1 = true;
            bomberBomb.bombs(window,map,bomberBomb.x,bomberBomb.y);
        }
        
        if (bomberBomb.time == 3 || bomberBomb.time1 == 3) {
            bomb.play();
        }
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}




