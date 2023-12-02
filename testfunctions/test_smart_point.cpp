#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

#include <cstring>
#include <algorithm>
#include "Tile.h"
#include "TileBag.h"
#include "LinkedList.h"
#include "Board.h"
#include "Player.h"


//scuffed strat lol
int main ()
{
    std::vector<std::string> file_store;
    std::cout<<"test: 1"<<std::endl;
    std::string file = "save_name.save" ;
    // std::cin>> file;
    std::ifstream rfile(file);
    std::string line; 
    if(rfile.is_open()){
        while(!rfile.eof()){
            line = "";
            // std::cout<<"test: 1.5"<<std::endl;
            std::getline(rfile,line);
            file_store.push_back(line);
        }
        rfile.close();
    }
    // std::cout<<"test: 2"<<std::endl;
    // int size = file_store.size();
    // for(int i = 0; i<size; i++){
    //     std::cout<<file_store[i]<<std::endl;
    // }
    //player 1 testing
    std::string player_1_name =file_store[0];
    int player_1_point = std::stoi(file_store[1]);
    std::string player_1_hand = file_store[2];
    std::vector<std::string> word_store;

    std::string token;
    std::stringstream stream(player_1_hand);
    while(std::getline(stream, token, ',')){
        word_store.push_back(token);
    }


    std::shared_ptr<LinkedList> p1_hand  = std::make_shared<LinkedList>();

    int handSize = word_store.size();

    for( int i = 0; i<handSize; i++){
        char letter = word_store[i][0];
        int value = std::stoi(std::string(1,word_store[i][2]));
        Tile* newTile = new Tile(letter,value);
        p1_hand->addToList(*newTile);
        delete newTile;
    }
    int player_1_num = 1;
    Player* player1 = new Player(player_1_num, player_1_name, player_1_point,p1_hand);
    player1->printHand();

    // player 2 
    std::cout<<"player 2"<<std::endl;
    std::string player_2_name =file_store[3];
    int player_2_point = std::stoi(file_store[4]);
    std::string player_2_hand = file_store[5];
    std::vector<std::string> word_store2;



    std::stringstream stream2(player_2_hand);
    while(std::getline(stream2, token, ',')){
        word_store2.push_back(token);
    }


    LinkedList* p2_hand  = new LinkedList();

    int handSize2 = word_store2.size();

    for( int i = 0; i<handSize2; i++){
        char letter = word_store2[i][0];
        int value = std::stoi(std::string(1,word_store2[i][2]));
        Tile* newTile = new Tile(letter,value);
        p2_hand->addToList(*newTile);
        delete newTile;
    }
    int player_2_num = 2;
    Player* player2 = new Player(player_2_num, player_2_name, player_2_point,p2_hand);
    player2->printHand();

    // board load here



    // TileBag* bag = newTileBag();
    std::cout<<"tilebag"<<std::endl;
    std::string bag = file_store[7];
    // std::cout<<bag<<std::endl;
    std::vector<std::string> bag_store;

    std::stringstream bagstream(bag);

    while(std::getline(bagstream, token, ',')){
        bag_store.push_back(token);
    }
    int bagSize = bag_store.size();
    std::cout<<bagSize<<std::endl;
    std::vector<Tile*> bagVec;

    for( int i = 0; i<bagSize; i++){
        char letter = bag_store[i][0];
        int value = std::stoi(std::string(1,bag_store[i][2]));
        Tile* newTile = new Tile(letter,value);
        bagVec.push_back(newTile);
        // delete newTile;
    }
    TileBag* newBag = new TileBag(bagVec);
    newBag->printTiles();
    // std::cout<<file;

    Board* gameBoard = new Board();
    std::string boardPlacement = file_store[6];
    std::vector<std::string> board_store;

    std::stringstream boardstream(boardPlacement);

    while(std::getline(boardstream, token, ' ')){
        board_store.push_back(token);
    }
    for(int i = 0; i<board_store.size();i++){
        std::cout<<board_store[i]<<std::endl;
    }
    std::cout<<"test"<<std::endl;
    int board_size = board_store.size();
    for(int i = 0; i<board_size; i++){
        char boardletter = board_store[i][0];
        int x_pos = std::stoi(std::string(1,board_store[i][3]));
        char y_pos = board_store[i][2];
        std::cout<<"letter: "<<boardletter<<" xpos; "<<x_pos<<" ypos: "<<y_pos<<std::endl;
        gameBoard->addTileToBoard(boardletter,x_pos,y_pos);
    }
    return 0;
}