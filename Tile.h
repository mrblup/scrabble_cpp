
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <iostream>
// Define a Letter type
typedef char Letter;

// Define a Value type
typedef int Value;

class Tile {
public:
   Letter letter;
   Value  value;
   Tile();
   Tile(char _letter, int _value);
   ~Tile();
   // deep copy for setting hand of player
   Tile(Tile& other);
   
   //prints letter and value for testing
   void printData();

   //used in Player class to print hand 
   void printTile();
   void setValues(char l, int v);
};
typedef Tile* tilePtr;

#endif // ASSIGN2_TILE_H
