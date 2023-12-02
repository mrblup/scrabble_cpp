// contains all tiles that are currently not in board or player hand
#include "TileBag.h"

TileBag::TileBag(){
    this-> bag = new LinkedList();
}

TileBag::TileBag(std::vector<Tile*> starting_bag){
    this->bag = new LinkedList();
    //constructor of tile bag will take in already randomised vector of tiles,
    // then place them into bag through for loop
    int bagSize =starting_bag.size();
    for(int i = 0; i<bagSize; i++){
        Tile* tile = new Tile(*starting_bag[i]);
        this->bag->addToList(*tile);
    }
}

TileBag::~TileBag(){
    // should use the linked lists deconstructor
    this->bag->clear();
    delete this->bag;
}


std::vector<std::string> TileBag::saveBag(){
    std::vector<std::string> bagSave = this->bag->printListToSave();
    return bagSave;
}



//creates a new tile using the head of the tilebag and returns that
Tile* TileBag:: drawTileFromFront(){

    Tile* copiedTile = new Tile(); 
    char let = this->bag->get(0)->letter;
    int val = this->bag->get(0)->value;
    copiedTile->setValues(let, val);
    this->bag->removeFront();
    return copiedTile;
}


//uses the LinkedList method addToList() to place a tile into the bag
void TileBag::addTile(Tile newTile){
    this->bag->addToList(newTile);
}


int TileBag::getSize()
{
    return this->bag->size();
}

//prints out bag for testing
void TileBag::printTiles(){
    this->bag->printList();
}

