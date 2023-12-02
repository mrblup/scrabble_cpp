#include "Node.h"

//basic constructor
Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

//Copy Constructor (Shallow Copy) ;rl
Node::Node(Node& other)
{
   // TODO
   this->tile = other.tile;
   this->next = other.next;
}

//Setter for next Node ;rl
void Node::setNext(Node* node)
{
   this->next = node;
}
