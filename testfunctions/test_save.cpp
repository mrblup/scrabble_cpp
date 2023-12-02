#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <cstring>
#include <algorithm>
#include "Tile.h"
#include "TileBag.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"

int main (){   
    
    std::cout<<"test 1"<<std::endl;
    //get tile bag
    std::vector<Tile*> allTiles;
    std::string file = "ScrabbleTiles.txt";
    std::ifstream fileToRead(file);
    std::string line;     
    if (fileToRead.is_open()){
        while(!fileToRead.eof()){
            line = "";
            //stores tile into string line
            std::getline(fileToRead, line);
                // as line is a character array, can simply take the character at placement 0 and 2 
                //as they contain the information
                char letter = line[0]; 
                char value = line[2];
                // need to convert value from character to string,
                // but since stoi only works with string, need to convert to string first, then to int
                int actualValue = std::stoi(std::string(1,value));
                Tile* newTile = new Tile(letter, actualValue);
                allTiles.push_back(newTile);
        
        }
        //as program reads in the last line from file, which is empty, we need to remove it from the vector
        allTiles.pop_back();
        fileToRead.close();
    std::random_shuffle(allTiles.begin(), allTiles.end());
    std::cout<<"test 2"<<std::endl;
    }   
    std::cout<<"test 3"<<std::endl;
    TileBag* tiles_ = new TileBag(allTiles);
    Board* gameBoard = new Board();
    //(int playerNo ,std::string playerName, int player_points, LinkedList* hand)
    int player1num = 1;
    int player2num = 2; 
    std::string play1name ="LEONARDO";
    std::string play2name ="MUFASA";
    LinkedList* hand1 = new LinkedList();
    LinkedList* hand2 = new LinkedList();
    Player* player1 = new Player(player1num,play1name,0,hand1);
    Player* player2 = new Player(player2num,play2name,0,hand2);
    
    player1->setHand(tiles_);
    std::cout<<"hand of player 1"<<std::endl;
    player1->printHand();
    std::cout<<"hand of player 2"<<std::endl;
    player2->setHand(tiles_);
    player2->printHand();
    std::cout<<"bag after hand"<<std::endl;
    tiles_->printTiles();

    player1->drawTile(tiles_);
    player1->printHand();
    tiles_->printTiles();


    // std::cout<<player1->checkForTile(x)<<std::endl;
    // gameBoard->testPlacementNoPlayer(' ', 1, 1);
    gameBoard->printBoard();
    std::cout<<"add test1"<<std::endl;
    player2->drawTile(tiles_);
    player2->printHand();
    std::cout<<"add test2"<<std::endl;
    player2->drawTile(tiles_);
     player2->printHand();
    std::cout<<"add test3"<<std::endl;
    player2->drawTile(tiles_);
    player2->printHand();
    // std::cout<<std::endl;
    player2->placeTile('A',gameBoard,2,'A');
    player2->printHand();
    // player2->placeTile('I',gameBoard,2,2);
    // gameBoard->printBoard();
    gameBoard->printBoard();
    char x;
    std::cout<<"select the letter to place onto the board: ";
    std::cin>>x;
    std::cout<<"test 4"<<std::endl;
    int x_pos;
    char y_pos;
    // int y_pos;
    std::cin>>x_pos;
    std::cin>>y_pos;
    std::cout<< x_pos<< " "<< y_pos<<std::endl;
    bool checkPlayer = player1->checkForTile(x);
    bool checkBoard =  gameBoard->isEmpty(x_pos,y_pos); 
    if ((checkPlayer == true)&&(checkBoard ==true)){
        std::cout<<"player 1 hand before placement: ";
        player1->printHand();
        std::cout<<"character to be placed: "<<x<<std::endl;
        player1->placeTile(x, gameBoard,x_pos,y_pos);
        // gameBoard->testPlacementNoPlayer(x,x_pos,y_pos);
        gameBoard->printBoard();
        std::cout<<"player1 hand after: ";
        player1->printHand();
    }
    else{
        std::cout<<"not a valid spot"<<std::endl;
    }
    player1->drawTile(tiles_);
    player1->printHand();

    // player2->drawTile(tiles_);
    // player2->drawTile(tiles_);
    // player2->drawTile(tiles_);
    player2->printHand();
    char replaceC;
    std::cin>> replaceC;
    player2->replaceTile(replaceC, tiles_);
    // player2->removeTile(replaceC);
    // player2->placeTile(replaceC, gameBoard, 9,'f');
    // player2->drawTile(tiles_);
    player2->printHand();
    
    // std::cout<<"select the letter to place onto the board: ";
    // std::cin>>x;
    
    // std::cin>>x_pos;
    // std::cin>>y_pos;
    //  checkPlayer = player1->checkForTile(x);
    //  checkBoard = gameBoard->isEmpty(x_pos,y_pos);
    // if ((checkPlayer == true)&&(checkBoard ==true)){
    //     std::cout<<"player 1 hand before placement: ";
    //     player1->printHand();
    //     std::cout<<"character to be placed: "<<x<<std::endl;
    //     player1->placeTile(x, gameBoard,x_pos,y_pos);
    //     // gameBoard->testPlacementNoPlayer(x,x_pos,y_pos);
    //     gameBoard->printBoard();
    //     std::cout<<"player1 hand after: ";
    //     player1->printHand();
    // }
    // else{
    //     std::cout<<"not a valid spot"<<std::endl;
    // }
    // std::vector<Tile*> player1_hand_save = player1->saveHand();
    // std::cout<<player1_hand_save.size()<<std::endl;
    // for(int i = 0; i<player1_hand_save.size(); i++){
    //     std::cout<<player1_hand_save[i]->letter<<std::endl;
    // }
    // std::vector<std::string> player1_hand_save = player1->saveHand();
    // std::cout<<player1_hand_save.size()<<std::endl;
    // for(int i = 0; i<player1_hand_save.size(); i++){
    //     std::cout<<player1_hand_save[i]<<std::endl;
    // }


    //start of saving
    std::ofstream saveFile("save_name.save");
    // std::cout<<"test 5"<<std::endl;

    //player1 save
    std::string test  = player1->getName();
    saveFile<<test;
    saveFile<<'\n';
    saveFile<<player1->getPoint();
    saveFile<<'\n';
    std::vector<std::string> player1_hand_save = player1->saveHand();
    for ( auto thingy  =  player1_hand_save.begin(); thingy != player1_hand_save.end(); ++thingy){
        saveFile<<*thingy;
    }
    saveFile<<'\n';
    // player 2 save
    saveFile<<player2->getName();
    saveFile<<'\n';
    saveFile<<player2->getPoint();
    saveFile<<'\n';
    std::vector<std::string> player2_hand_save = player2->saveHand();
    for ( auto thingy  =  player2_hand_save.begin(); thingy != player2_hand_save.end(); ++thingy){
        saveFile<<*thingy;
    }
    saveFile<<'\n';

    // board save
    std::vector<std::string> boardSave =gameBoard->saveBoard();
    for ( auto thingy  =  boardSave.begin(); thingy != boardSave.end(); ++thingy){
        saveFile<<*thingy;
    }
    saveFile<<'\n';

    //bagsave

    std::vector<std::string> bag_save = tiles_->saveBag();
    for ( auto thingy  =  bag_save.begin(); thingy != bag_save.end(); ++thingy){
        saveFile<<*thingy;
    }
    saveFile<<'\n';


    //current player save
    //itll; be like  saveFile<<currentplayer->getName();
    std::string currentPlayer = player1->getName(); // this is here for demonstration
    saveFile<<currentPlayer<<'\n';

    saveFile.close();



    //deleting test, some data lost within trading of tiles
    delete player1;
    delete tiles_;

    delete player2;
    delete gameBoard;
    

    return 0 ;
}