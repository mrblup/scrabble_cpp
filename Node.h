
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:
   Node(Tile* tile);
   Node(Tile* tile, Node* next); 
   Node(Node& other);


   void setNext(Node* node);
   Node getNext();
 
   Tile*    tile;
   Node*    next;
};

#endif // ASSIGN2_NODE_H
