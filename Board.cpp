#include "Board.h" 



#define ROWS 15
#define COLS 15  // using hashdefine for these variables as it is not expected to change for the group task
//vectors
Board::Board()
{
    char val = ' '; //represents an empty space
    //dimensions of the board
    int rows = ROWS;
    int cols = COLS;
    //store values in a 2d vector of dimensions rows/cols and associate value of the rows to the letters
    std::vector<std::vector<char>> tempVec(rows, std::vector<char>(cols, val));
    this->board = tempVec;
    static char array[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
    this->boardElements = array;    
}

//deconstructor
Board::~Board(){
    
}

//used to dictate whether a tile is able to be legally placed in the position provided
bool Board::legalTilePlacement(int col, char rowChar)
{
    bool legalTilePlacement = false;
    int row = convCharToInt(rowChar); //converts from character to row
    // if the row is not empty
    if(isBoardEmpty()==false)
    {   
        if(this->board[row][col] != ' ') // if the row is equal, state error in input
        {
            std::cout << "This position already has a Tile on it." << std::endl;
        }
        else
        {   
            if(rowChar == 'A' || rowChar == 'O' || col == 0 || col == 14) //if the positions are along the edge of the board
            {
                if(rowChar == 'A')//upper edge, hence check only left, down or right
                {
                    if(this->board[row+1][col] != ' ' || this->board[row][col+1] != ' ' || this->board[row][col-1] != ' ' ) //if any of the edges are empty, return true
                    {
                        legalTilePlacement = true;
                    }
                    else
                    {
                    std::cout << "The tile is not adjacent to another tile and cannot be placed.";
                    }
                }
                else if(rowChar == 'P')//lower edge, check left, up and right.
                {
                    if(this->board[row-1][col] != ' ' || this->board[row][col+1] != ' ' || this->board[row][col-1] != ' ' )//if any of the edges are empty, return true
                    {
                        legalTilePlacement = true;
                    }
                    else
                    {
                    std::cout << "The tile is not adjacent to another tile and cannot be placed.";
                    }
                }
                else if(col == 0)//left edge, check up, right or down
                {
                    if(this->board[row+1][col] != ' ' || this->board[row-1][col] != ' ' || this->board[row][col+1] != ' ' )//if any of the edges are empty, return true
                    {
                        legalTilePlacement = true;
                    }
                    else
                    {
                        std::cout << "The tile is not adjacent to another tile and cannot be placed.";
                    }        
                }
                else if(col == 14)//right edge, check up, left or down.
                {
                    if(this->board[row+1][col] != ' ' || this->board[row-1][col] != ' ' || this->board[row][col+1] != ' ' )//if any of the edges are empty, return true
                    {
                        legalTilePlacement = true;
                    }
                    else
                    {
                        std::cout << "The tile is not adjacent to another tile and cannot be placed.";
                    }
                }
            }
            else //only reaches this point once it is known that neither dimension is located on the edge of the board.
            {
                if(this->board[row+1][col] != ' ' || this->board[row][col+1] != ' ' || this->board[row-1][col] != ' ' || this->board[row][col-1] != ' ')//if any of the edges are empty, return true
                {
                    legalTilePlacement = true;
                }
                else
                {
                    std::cout << "The tile is not adjacent to another tile and cannot be placed.";
                }
            }            
        }  
    }
    else //if the board is empty, return true
    {
        legalTilePlacement = true;
    }
    return legalTilePlacement;   
}
//addTileToBoard(): adds tile to board, takes in letter and row and col coords
void Board::addTileToBoard(char letter, int x_pos, char y_pos)
{
    int board_y= -1;
    //essentially checks, for every row, the char y_pos is equal to the ith board element.
    for(int i = 0; i<ROWS; i++)
    { 
        if(this->boardElements[i] == y_pos)
        {
            board_y = i;
        }
    }

    if (board_y != -1) //if the board row coord is valid 
    {   
        //check if the coords provided lead to an empty spot on the board.
        if(this->board[board_y][x_pos]== ' ')
        {
            this->board[board_y][x_pos] = letter;
        }
        else
        {
            
        }
    }
}

//convCharToInt(): associates board elements to boardRow integer for use in functions.
int Board::convCharToInt(char boardY)
{
    int intY = 0;
    //check every element of boardElements until equal to boardY
    while(boardY != boardElements[intY] && intY < 15)
    {
        intY++;
    }
    return intY;
}

//USED FOR TESTING
void Board::testPlacementNoPlayer(char letter, int x_pos, int y_pos){
    this->board[x_pos][y_pos] = letter;
}

//printBoard(): prints board to spec
void Board::printBoard()
{
    std::cout<<" ";
    for(int i = 0; i<10; i++)
    {
        std::cout<<"    "<<i; //prints blank spaces
    }
    for(int i = 0; i<5; i++)
    {
        std::cout<<"   "<<i+10; //prints blank spaces the the value of i+10
    }
    std::cout<<std::endl;
    std::cout<<"   ----------------------------------------------------------------------------"<<std::endl;
    for(int i  = 0; i<ROWS; i++){
        std::cout<<this->boardElements[i]<<" "; //prints board row characters
        for( int j = 0; j<COLS; j++)
        {
            std::cout<<" | "<<this->board[i][j]<<" "; //prints value at board[x][y]
            // std::cout<<"|";
        }
        std::cout<<" |"<<std::endl; //
    }
}
//isBoardEmpty(): iteratively checks that a spaces on the board are empty, returning false if at any point the board is not empty
bool Board::isBoardEmpty()
{
    bool isBoardEmpty = true;
    for(int i = 0; i < ROWS;i++) //for every row
    {
        for(int j = 0; j < COLS; j++) //for every column
        {
            // if(this->isEmpty(j,i) == false)
            // {
            //     isBoardEmpty = false;
            // }
            if(this->board[i][j]!=' ')
            {
                isBoardEmpty = false; // returns false if at any point the board is not empty
            }
        }
    }
    return isBoardEmpty;
}

//isEmpty(): 
bool Board::isEmpty(int x_pos, int y_pos){
    bool check = false;
    int board_ypos = -1;
    for(int i = 0; i<ROWS; i++){ // gotta change rows to a different #define
        if(this->boardElements[i] == y_pos){
            board_ypos = i;
        }
    }
    if(board_ypos == -1){
        check = false;
    }
    else if (this->board[board_ypos][x_pos] == ' '){
        check = true;
    }
    return check;
}

std::vector<std::string> Board::saveBoard(){
    std::vector<std::string> vectorOfTiles;
    std::string line = "";
    //this breaks when there is only one tile on the board for some reason
    
    // static const char boardLetterArray[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','O'};
    // need to find a way to make this a varaible every function can access


    // boardLetters();
    for (int i = 0; i< ROWS; i++ ){ 
        for (int j = 0; j<COLS;j++){ 
            // std::cout << *col; 
            // line.push_back
            
            if (this->board[i][j]!= ' '){
                char tile;
                char y_coord;
                std::string x_coord;
                tile = this->board[i][j];
                y_coord = this->boardElements[i];
                x_coord = std::to_string(j);
                line.push_back(tile);
                line.push_back('@');
                line.push_back(y_coord);
                line.append(x_coord);
                line.push_back(' ');
                vectorOfTiles.push_back(line);
            }
        } 
        
    
    } 
    //this is the reason
    // vectorOfTiles.pop_back();
    
    if (vectorOfTiles.size()>1){
        vectorOfTiles.erase(vectorOfTiles.begin());
    }
    return vectorOfTiles;

}
