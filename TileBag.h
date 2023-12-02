#ifndef ASSIGN2_TILE_BAG_H
#define ASSIGN2_TILE_BAG_H

#include "Node.h"
#include "Tile.h"
#include "LinkedList.h"
#include <vector>
class TileBag{
    public:
    TileBag(); // set an empty tile bag so the player class can be instantiated with an empty hand- roy
    TileBag(std::vector<Tile*> starting_bag); // minor change to make constructor of tilebag take innt vector of tile pointers- roy
    ~TileBag();

    void printTiles();
    // void randomize();

    std::vector<Tile*> createHand();
    tilePtr drawTileFromFront();
    void addTile(Tile newTile);
    std::vector<std::string> saveBag();
    int getSize();
    // tilePtr drawFrontTest();
    
    private:
    //upon initialisation, program should read in everything from ScrabbleTiles.txt and add it to the private variable 'bag'
    LinkedList* bag;
    

};


#endif