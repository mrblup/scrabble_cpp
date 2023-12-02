#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Tile.h"
#include <cstring>
#include <algorithm>
#include "TileBag.h"
#include "LinkedList.h"
#include "Board.h"

int main ()
{
    std::string file = "ScrabbleTiles.txt";
    std::ifstream fileToRead(file);
    std::string line;       
    // std::vector <std::string> tokens;
    std::vector<Tile*> allTiles;

    if (fileToRead.is_open()){
        // std::string bruh ="";
        // reads in tile line by line
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
        //testing the size of vector, should print 98
        std::cout<<allTiles.size()<<std::endl;
        
        
        fileToRead.close();
    //testing if vector properly stores tiles
    for(int i = 0; i<allTiles.size(); i++){
            std::cout<<(*allTiles[i]).letter<<" " <<(*allTiles[i]).value<<std::endl;
        }
    std::random_shuffle(allTiles.begin(), allTiles.end());
    std::cout<<"random"<<std::endl;
    //testing if vector sorts
    for(int i = 0; i<allTiles.size(); i++){
            std::cout<<(*allTiles[i]).letter<<" " <<(*allTiles[i]).value<<std::endl;
        }
    }

    std::cout<<"test tilebag"<<std::endl;
    // TileBag* testList  =new TileBag();
    TileBag* testList  =new TileBag(allTiles);

    // for( int i = 0; i <allTiles.size(); i++){
    //     std::cout<< i<< " point"<<std::endl;
    //     testList->addTile(*allTiles[i]);
    //     std::cout<<i<<" "<< allTiles.size()<<std::endl;
    // }
    testList->printTiles();
    Board* gameBoard = new Board();
    // //(int playerNo ,std::string playerName, int player_points, LinkedList* hand)
    // int player1num = 1;
    // int player2num = 2; 
    // std::string play1name ="BALLS";
    // std::string play2name ="BALLS2";
    // LinkedList* hand1 = new LinkedList();
    // LinkedList* hand2 = new LinkedList();
    // Player* player1 = new Player(player1num,play1name,0,hand1);
    // Player* player2 = new Player(player2num,play2name,0,hand2);
    //player1->setHand(tiles_);
    
    std::cout << "TESTING BOARD" << std::endl;
    std::cout <<"A :" << gameBoard->getRowPosition('A') << std::endl;
    std::cout <<"F :" << gameBoard->getRowPosition('F') << std::endl;
    std::cout <<"B :" << gameBoard->getRowPosition('B') << std::endl;
    std::cout <<"I :" << gameBoard->getRowPosition('I') << std::endl;


    std::cout << "A:" << gameBoard->A << std::endl;
    return 0;
}
