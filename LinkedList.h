#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H
 
#include "Tile.h"
#include "Node.h"
#include <string>
#include<vector>
 // should be a single linked list
class LinkedList {
public:

   LinkedList();
   
   ~LinkedList();

   int size();

   Tile* get(int index);
   void removeFront();
   void addToList(Tile letter);

   void removeAt(int index); 
   
   //printing list for testing
   void printList();
   std::vector<std::string> printListToSave();
   void addTest(Tile letter);
   int search(char l);
   Node* getHead();

   void clear();

   // int getPoint(int index);
   




private:
   Node* head;
   Node* tail;
   int length;
};

#endif // ASSIGN2_LINKEDLIST_H
