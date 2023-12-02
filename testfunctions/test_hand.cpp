#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <chrono>

#include <cstring>
#include <algorithm>
#include "Tile.h"
#include "TileBag.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
int myrandom (int i) { return std::rand()%i;}
int main(){
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
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();


    std::shuffle(allTiles.begin(), allTiles.end(),std::default_random_engine(seed));
    TileBag* tiles_ = new TileBag(allTiles);

    std::vector<Tile*> x = tiles_->createHand();
    for(int i = 0; i< x.size(); i++){
        std::cout<<x[i]->letter<<std::endl;
    } 




    return 0;
}