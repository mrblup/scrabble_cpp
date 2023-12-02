#ifndef ASSIGN_2_BOARD
#define ASSIGN_2_BOARD

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Tile.h"
#include "Node.h"
// #include "Player.h"
//15x15 matrix or something
// extern const char boardElements[15];
class Board{

    public:
    Board();
    ~Board();


    // place holder functions that will likely be changed

    //unsure if this should go here, as the player also needs to remove their tile from hand
    // void addTileToBoard(Player player, Tile letter, int x_position, int y_position);
    bool legalTilePlacement(int col, char rowChar);
    //this one is for testing
    void addTileToBoard( char letter, int x_position, int y_position);
    //this one will be used in program
    void addTileToBoard( char letter, int x_position, char y_position);

    // void replaceTile(Player player, Tile letter, int x_position, int y_position);
    void printBoard();
    bool CheckForNeighbour(int x_pos, int y_pos);
    void replaceTile(char letter, int x_pos, int y_pos);
    bool isBoardEmpty();
    bool isEmpty(int x_pos, int y_pos);
    int getRowPosition(char boardRow);    
    int convCharToInt(char boardY);
    std::vector<std::string> saveBoard();
    enum boardLetters{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O};
    void testPlacementNoPlayer(char letter, int x_pos, int y_pos);
    void printElementsTest();
    
    
    private:
    //a vector that stores the current state of the board, 
    // this should make it 2d
    //std::vector<std::vector<Node*>> currentState;
    // std::vector<std::vector<Tile*>> board;

    // AS WE DO NOT COUNT THE POINTS OF THE TILES ON THE BOARD WHEN A PLAYER PLACES A TILE,
    //  WE COULD STORE THE BOARD AS A VECTOR OF CHARACTERS INSTEAD, WHICH WILL MAKE ADDING TO THE BOARD EASIER
    std::vector<std::vector<char>> board;
    char* boardElements;
    // std::string* boardElements;
    // char x = *(board[1][1].letter);
    int ROWS = 15;
    int COLS = 15;

};

#endif