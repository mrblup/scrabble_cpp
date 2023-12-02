// contains hand
//contains scoregetTIl~
//words created by player

#include "Player.h"
#define SIZE_OF_HAND 7

//new game for making the player class
Player::Player(int playerNo ,std::string playerName, int player_points, LinkedList* hand)
{
    this->playerNo = playerNo;
    this->playerName = playerName;
    this->playerPoint = player_points;
    this->hand = hand;
    this->playerPassCount =0;
    // this->isCurrentPlayer = true; //player2 would be constructed to have this set to false
}

void Player::setHand(TileBag* tileBag)
{
    for(int i = 0; i < SIZE_OF_HAND; i++)
    {
        //assumes that the hand is empty, takes the first tile of the tilebag, removes it from the tilebag, 
        //passes it into the player's hand as the first tile.
        
        Tile* addingTile = new Tile();
        // Tile* frontTile = new Tile();
        addingTile = tileBag->drawTileFromFront();
        // frontTile = tileBag->drawFrontTest();
        // addingTile->setValues(frontTile->letter,frontTile->value);
        
        // char let = addingTile->letter;
        // int val = addingTile->value;
        // this->hand->addToList((tileBag->drawTileFromFront()));

        this->hand->addToList(*addingTile);
    }
}

int Player::getPlayerNo(){
    return this->playerNo;
}


//drawTile(): takes first tile of tileBag, places it in the end of the player's hand
void Player::drawTile(TileBag* tileBag)
{
    //tried setting a new tile to see if that would work, it doesn;t- roy
    Tile* addingTile = new Tile();
    addingTile = tileBag->drawTileFromFront();
    // Tile* addingTile = &(tileBag->drawTileFromFront());
    // this->hand->addToList(*addingTile);
    this->hand->addToList(*addingTile);
}


//used to check whether a tile is in a hand
bool Player::checkForTile(char tileToCheck)
{
    bool isInHand = false;  
    Node* currentNode = this->hand->getHead();
    //for every node of the linkedList, check whether the value of the currentNode's letter is that of the tile to check.
    while((isInHand == false)&& currentNode!= nullptr){
        if (currentNode->tile->letter == tileToCheck){
            isInHand = true; //if equal, return true.
        }
        currentNode = currentNode->next;
    }
    return isInHand;
}

//getTile() - returns the index of the tile passed into the function, returns the first instance of the tile.
int Player::getTile(char tile)
{
    int indexTile = -1;
    for(int i = 0; i < hand->size(); i++)
    {
        Tile* currentTile = hand->get(i); // access and assign the ith tile in the hand to currentTile
        char currentLetter = currentTile->letter;
        if(currentLetter == tile)
        {
            indexTile = i;
            //returns i, which if tile parameter is equal to currentLetter, i will be greater than 0.
        }
    }
    if(indexTile == -1)
    {
        std::cout << "Cannot get Tile." << std::endl; //states error should tile not be in hand 
    }
    return indexTile;
}

//removeTile(): removes a tile from a player's hand - would be called upon placement of a tile from a player's hand
void Player::removeTile(char tile)
{   
    int check = getTile(tile); //returns index of tile 

    if(check != -1){
        
        hand->removeAt(check); //uses LinkedList::removeAt() to remove tile from hand
    }
    else{
        std::cout << "Cannot get Tile." << std::endl; //states error if tile not in hand
    }
}

// function used to add in number of points 
void Player::addPoints(int point)
{
    this->playerPoint+=point; //offsets playerPoint by value 'point'
}



//placeTile(): places a tile on to the board given, adds the points from the tile used and deletes said tile
void Player::placeTile(char tile, Board* play, int x, char y)
{

    if(checkForTile(tile) == true) //if tile is in hand
    {
        (*play).addTileToBoard(tile, x,y); 
        //finds the index of the tile and adds the tiles point to the players point total
        int index = getTile(tile);
        int point = hand->get(index)->value;
        this->playerPoint+= point;
        //deletes tile from players hand
        removeTile(tile);

    }
    else
    {
        std::cout << "Tile not in hand." << std::endl;
    }
}

//replaceTile(): Finds the tile the user wants to replace, adds a tile from the tilebag, places the replacing tile into the tilebag and removes the tile from users hand
void Player::replaceTile(char tile, TileBag* tileBag)
{
    if(checkForTile(tile) == true) //checks if tile is in hand, throws exception else
    {
     
        
        int check = getTile(tile);
        Tile* newTile = new Tile(hand->get(check)->letter, hand->get(check)->value);;
        tileBag->addTile(*newTile);
        removeTile(tile); //remove tile from hand

        this->drawTile(tileBag); //draw new tile from tileBag.

    }
    else
    {
        std::cout << "Tile not in hand." << std::endl;
    }
}


//simply uses LinkedList::printList() to print hand 
void Player::printHand(){
    this->hand->printList(); 
}

// uses LinkedLists method to return a vector that can be used to save the game
std::vector<std::string> Player::saveHand(){
    std::vector<std::string> handSave = this->hand->printListToSave(); //saves hand to save file spec
    return handSave;
}

//SERIES OF GET FUNCTIONS TO ACCESS size, name, point and pass respectively
int Player::getSize(){
    return this->hand->size();
}

std::string Player::getName(){
    return this->playerName;
}
int Player::getPoint(){
    return this->playerPoint;
}

int Player::getPass(){
    return this->playerPassCount;
}
//resets player.pass to 0
void Player::resetPass(){
    this->playerPassCount =0;
}
//increments player.pass
void Player::increasePass(){
    this->playerPassCount+=1;
}

//player deconstructor
Player::~Player(){
    this->hand->clear();
    delete this->hand;
}




//placeTile(): calls checkForTile() and removeTile(tile) to to check if the tile is in the player hand, then calls 
//the board's placeTile equivalent, then places it on the board
// void Player::placeTile(char tile)
// {
//     if(checkForTile(tile) == true)
//     {
//         removeTile(tile);
//         //call board placeTile();
//     }
//     else
//     {
//         throw std::runtime_error("Tile not in hand.");
//     }
// }