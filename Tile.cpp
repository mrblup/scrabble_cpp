
#include "Tile.h"

Tile::Tile(){

}

Tile::Tile(char _letter, int _value){
    this->letter = _letter;
    this->value = _value;

}
Tile::Tile(Tile& other){
    letter = other.letter;
    value = other.value;
}

Tile::~Tile(){
// values in tile are 'simple' data types, thus do not need a deconstructor

}
// for testing the values
void Tile::printData(){
    std::cout<<"letter: "<<this->letter<<", value: "<< this->value<<std::endl;
}

//used in player Class to printHand()
void Tile::printTile()
{
    std::cout<< this->letter << "-"<< this->value << ",";
}

void Tile::setValues(char l, int v){
    this->letter =l;
    this->value = v;
}
