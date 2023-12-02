#ifndef ASSIGN_2_PLAYER
#define ASSIGN_2_PLAYER

#include <string>
#include "Node.h" 
#include "TileBag.h"
#include "Board.h" 
#include "LinkedList.h" 
#include <vector>
class Player{
    public:
    //constructor and de-constructor 
    Player(int playerNo,std::string playerName, int player_points, LinkedList* hand);
    // Player(Player &other); // unsure if we need to have a deep copy of player but its in here anyway
    ~Player();
    // this will create a new node and store it in the hand of player


    void setHand(TileBag* newHand);

    // this should access the current TileBag, and return a node to place into the hand, unsure how to implement, might need to change from void to Node::
    void drawTile(TileBag* tileBag);

    bool checkForTile(char tile); //checks the hand for a tile

    int getTile(char tile); //outputs integer of index of first instance of letter.

    void removeTile(char tile); //checks that the tile is in hand, then removes it.

    // this function should first check to see if the players hand contains the tile, then it should delete it
 

    void placeTile(char tile, Board* play, int x, char y);
    void replaceTile(char tile, TileBag* tileBag);

    void printHand();// make make a utils file to store this if needed

    void addPoints(int point);
    
    void getHandTest(std::vector<Tile*> startHand);
    
    std::string getName();
    int getSize();// outputs the size of the hand 
    int getPoint();
    int getPlayerNo();
    int getPass();
    void resetPass();
    void increasePass();

    std::vector<std::string> saveHand();
    // std::vector<Tile*> saveHand();

    

    private:
    int playerPoint; 
    std::string playerName;
    int playerNo;
    LinkedList* hand;
    // bool isCurrentPlayer;
    int playerPassCount;


};


#endif