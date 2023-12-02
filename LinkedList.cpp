#include "LinkedList.h"
#include <stdexcept>

//Default Constructor
LinkedList::LinkedList() {

   this->head = nullptr;
   this->length = 0;
}

//De-constructor
LinkedList::~LinkedList() {
   clear();
}

//size(): returns the size of the LinkedList.
int LinkedList::size()
{
    return this->length; //calls the instance's length
}

//get(int index): returns the tile at the specified index.
Tile* LinkedList::get(int index){
   Node* currentNode = this->head; // sets the variable currentNode to the head of the list
   int n = 0;

   if(index < 0)    //if and else if check that the index is valid, returning exceptions if not valid.
   {
    //    throw std::out_of_range("Error: Index invalid (< 0)");
        std::cout<<"Error: Index invalid (< 0)"<<std::endl;
   }
   else if(index > this->size())
   {
    //    throw std::out_of_range("Error: Index invalid (> size)");
       std::cout<<"Error: Index invalid (> size)"<<std::endl;
   }

   while( currentNode != nullptr && n < index) //iterates to the i-th node
   {
       currentNode = currentNode->next;
       ++n;
   }
   return currentNode->tile; // returns the tile at the currentNode, which would now be the node at the index.
}


//clear(): 
void LinkedList::clear()
{
    while(head != nullptr) //call the removeFront() function for every element in the list.
    {
        removeFront();
    }
}

// removeFront(): removes the first (head) node of the linked list.
void LinkedList::removeFront()
{
     //if the head of the list does not equal a null, set a node to the head of the list, and the head to the next element
    if(head != nullptr)
    {
        Node* toDelete = head;
        head = head->next;
    //delete the tile and node associated with the head of the list.
        delete toDelete->tile;
        delete toDelete;
        this->length--;
    }
    else // if the list is empty, throw an error.
    {
        throw std::runtime_error("Nothing to remove");
    }
}

//removeAt(): delete node at index - ryan
void LinkedList::removeAt(int index)
{
    Node* currentNode = this->head;
    int n = 0;

    //throw range exception if index passed in is out of range
    if(index < 0 || index >this->size())
    {
        throw std::out_of_range("Error: invalid index");
    }
    else if(index == 0  ){
        // removeFront();
        Node* tempNode = this->head;
        this->head = this->head->next;
        delete tempNode;
        this->length = this->length-1;
    }
    else
    {
        
        //iterate through LinkedList while not at end of list or 
        //at the node to delete.
        while(currentNode != nullptr && n < index - 1)
        {
            
            currentNode = currentNode->next;
            n++;
        }   


        //set node to delete to node after current, set new next 
        //to node after node to delete
        Node* nodeToDelete = currentNode->next;
        currentNode->next = nodeToDelete->next;

        //delete node
        delete nodeToDelete->tile;
        delete nodeToDelete;
        

        // have a while loop that traveses to end of list

            while(currentNode->next != nullptr){

                currentNode = currentNode->next;
            }    
            this->tail = currentNode;

        

        this->length = this->length-1;
    }
}

// prints the entire linkedlist to the terminal
void LinkedList::printList(){
    Node* currentNode = this->head;

    while(currentNode!= nullptr){
        std::cout<< currentNode->tile->letter<<"-"<<currentNode->tile->value<<" "; // changed the print list function to print on only one line
        currentNode = currentNode->next;

    }
    std::cout<<std::endl;
}       

//returns a vector that contains all the tiles of the linkedlist in a form that can be saved
std::vector<std::string> LinkedList::printListToSave(){
    Node* currentNode = this->head;
    std::vector<std::string> vectorOfTiles;
    while(currentNode != nullptr){
        std::string line = "";
        std::string value_ish = std::to_string(currentNode->tile->value);
        line.push_back(currentNode->tile->letter);
        line.push_back('-');
        line.append(value_ish);
        line.push_back(',');

        vectorOfTiles.push_back(line);
        currentNode = currentNode->next;
    }
    //an empty element is stored in the list, so this removes said element
    vectorOfTiles.pop_back();

    return vectorOfTiles;
}
// function that properly adds in a new node, with the addition of a tail pointer
void LinkedList::addToList(Tile tile){
    Tile* newTile = new Tile(tile.letter, tile.value);
    Node* newNode = new Node(newTile, nullptr);
    Node* tempNode = this->head;
    
    if (tempNode == nullptr){
        this->head = newNode;
        this->tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    this->length+=1;
}
//
// int LinkedList::search(char l){
//     Node* currentNode = this->head;
//     int isFound = -1;
//     int current_index = 0;
//     while(currentNode != nullptr){
//         if(currentNode->tile->letter == l){
//             current_index = true;
//             isFound = current_index;
//         }
//         currentNode = currentNode->next;
//         current_index+=1;
//     }
//     return isFound;
// }
Node* LinkedList::getHead(){
    return this->head;
}


