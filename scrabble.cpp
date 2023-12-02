
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>
#include <chrono>

#include "Player.h"
#include "Tile.h"
#include "TileBag.h"
#include "LinkedList.h"
#include "Board.h"

// these variables are used to aquire the data for tiles
#define LETTER_PLACEMENT 0
#define VALUE_PLACEMENT 2
#define SECOND_DIGIT_VALUE 3

#define STARTSCORE 0 
#define PLAYER1_NUM 1
#define PLAYER2_NUM 2

//loading number defines
#define LOAD_LINE_0 0
#define LOAD_LINE_1 1
#define LOAD_LINE_2 2
#define LOAD_LINE_3 3
#define LOAD_LINE_4 4
#define LOAD_LINE_5 5
#define LOAD_LINE_6 6
#define LOAD_LINE_7 7


#define END_OF_WORD 4
#define X_POS 3
#define Y_POS 2

#define STRING_LENGTH 1

#define PLAYER_ACTION 0
#define PLAYER_LETTER 1
#define BINGO_NUMBER 50
#define LUCKY_NUMBER 7
#define LETTER_POS 2


#define EXIT_SUCCESS 0
void mainMenu();
void newGame();
void newGame_extra_player();
void loadGame();
void loadGame_extra_player();
void saveGame(Player* player1, Player* player2, TileBag* tiles_,Board*board,std::string currentPlay, std::string fileName); // might need finetuning
void saveGame(std::vector<Player*> vec_players, TileBag* tiles_,Board*board,std::string currentPlay, std::string fileName); // might need finetuning
void playGame(Player* player1, Player* player2, TileBag* tiles_,Board*board, std::string curentPlayer);
void playGame(std::vector<Player*> vec_players, TileBag* tiles_,Board* board, std::string curentPlayer);
bool doesGameEnd(Player* player1, Player* player2, Board* gameboard, TileBag*tilebag);
void takeTurn(Player* currentPlayer,Player* p1, Player* p2, TileBag* tilebag, Board* gameboard);
void takeTurn(Player* currentPlayer,std::vector<Player*> vec_players, TileBag* tilebag, Board* gameboard);
void printHelp();

std::vector<Tile*> getTiles(std::vector<Tile*> vector);


int main(int argc, char**argv){
   mainMenu();


   return EXIT_SUCCESS;
}
void printHelp(){
   std::string hint_array[5] = {"\nTo place a Tile, type the command 'place(lower case)',\nfollowed by the tile you wish to place(upper case), \nthe row position(upper case) and the column number,\n example: 'place A A0'\n",
                                 "\nin the situation you cannot place a tile to form a word, simply type 'pass' to finish your turn early\n passing two times in a row will end the game however\n",
                                 "\nwhen you are finished with your turn, type the command 'place done' to finish\n",
                                 "\nif there is a tile in your hand that isn't needed, type the command 'replace', followed by the tile to be replaced(upper case)\n example: 'replace X'\n",
                                 "\ndon't type incorrectly or else the program might break\n"};
   std::string hint_continue = "yes";
   // std::cin>>hint_continue;
   while(hint_continue == "yes"){
      int randum =  (rand() % 5);
      std::cout<<hint_array[randum]<<std::endl;
      std::cout<<"would you like another random hint?\n type yes to continue\n type anything else to end: ";
      std::cin>>hint_continue;
   }
   std::cout<<std::endl;
   // ask for user input to see if they want another hint
}

// code to get randomised vector of tiles - roy
std::vector<Tile*> getTiles(std::vector<Tile*> vector){
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
                int line_size = line.size();

                char letter = line[LETTER_PLACEMENT]; 
                char value = line[VALUE_PLACEMENT];
                std::string stringValue = "";
                stringValue.push_back(value);
                if (line_size>3){
                  char value2 =line[VALUE_PLACEMENT+1];
                  stringValue.push_back(value2);
                
                }
                // need to convert value from character to string,
                // but since stoi only works with string, need to convert to string first, then to int

                int actualValue = std::stoi(stringValue);
                Tile* newTile = new Tile(letter, actualValue);
                vector.push_back(newTile);
        }
        //as program reads in the last line from file, which is empty, we need to remove it from the vector
        vector.pop_back();
        fileToRead.close();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(vector.begin(), vector.end(),std::default_random_engine(seed));
    }   
   return vector;

}
//mainMenu(): entry point of game, from which user input dictates the flow of gameplay.
void mainMenu(){
   int n = 0;
   std::string x;
   bool config_more_player = false;
   while(n == 0){
      std::cout << " ---- " << std::endl;
      std::cout << " Menu " << std::endl;
      std::cout << " ---- " << std::endl;
      std::cout << " 1. New Game " << std::endl;
      std::cout << " 2. Load Game " << std::endl;
      std::cout << " 3. Credits " << std::endl;
      std::cout << " 4. Config " << std::endl;
      std::cout << " 5. Quit " << std::endl;
      
      std::cout << std::endl;
      std::cout << ">";
      
      std::cin >> x;
      if(x == "1"){
         //New Game
         if (config_more_player == true){
            newGame_extra_player();   //to be changed to the other version
         }
         else{
            newGame();
         }
         n = 1; //only increments n if newgame or loadgame are called, thus ending the loop of mainMenu.

      }else if(x == "2"){
         //Load Game
         if (config_more_player == true){
            loadGame_extra_player();   //to be changed to the other version
         }
         else{
            loadGame();
         } //only increments n if newgame or loadgame are called, thus ending the loop of mainMenu.
         n = 1;

      }else if(x == "3"){
         // Printing Credit
               std::cout << "-----------------------" << std::endl;
               std::cout << "Name : Roy Lim" << std::endl;
               std::cout << "Student ID: s3895697" << std::endl;
               std::cout << "Email : s3895697@student.rmit.edu.au" << std::endl;
               std::cout << std::endl;
               std::cout << "Name : John Raphael Violeta" << std::endl;
               std::cout << "Student ID: s3660057" << std::endl;
               std::cout << "Email : s3660057@student.rmit.edu.au" << std::endl;
               std::cout << std::endl;
               //hes gone :(
               // std::cout << "Name : Jiou Shen Loh" << std::endl;
               // std::cout << "Student ID: s3937437" << std::endl;
               // std::cout << "Email : s3937437@student.rmit.edu.au" << std::endl;
               // std::cout << std::endl;
               std::cout << "Name : Ryan Leen" << std::endl;
               std::cout << "Student ID: s3840307" << std::endl;
               std::cout << "Email : s3840307@student.rmit.edu.au" << std::endl;
               std::cout << "-----------------------" << std::endl;
               std::cout << std::endl;
               int c = 0;
               while (c == 0){
                  std::cout << "Enter (Q) to go back to Main Menu" << std::endl;
                  std::cout << std::endl;
                  std::cout << ">";
                  n = 1;
                  char q;
                  std::cin >> q;
                  if(q == 'q'){
                    q = q - 32;
                  }
                  if( q == 'Q'){
                     n = 0;
                     c = 1;
                  }else{
                     std::cout << "Invalid Input" << std::endl;
                  }
                  std::cout << std::endl;
               }
       }
       else if(x == "4"){
         std::string player_choice = "";
         std::cout<<"do you wish to activate 3-4 player?\nyes or no(lower case): ";
         std::cin>> player_choice;
         std::cout<<std::endl;
         if (player_choice == "yes"){
            config_more_player = true;
            std::cout<<"3+ player mode has been activated"<<std::endl;
         }
         else if (player_choice == "no"){
            config_more_player = true;
            std::cout<<"3+ player mode has been disabled"<<std::endl;
         }
      }
       else if(x == "5"){
         // quit game
         std::cout << "GoodBye" << std::endl;
         n = 1; 
         exit(0);
         
      }
      
      else{
         std::cout << "Unknown Command ! " << std::endl;
      }
   }
}
//newGame(): initialises tilebag, players and board before jumping into gameplay
void newGame(){
   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   //Initialises the tilebag and randomises it.
   std::vector<Tile*> randomisedTiles;
   randomisedTiles = getTiles(randomisedTiles);
   TileBag* tilebag = new TileBag(randomisedTiles);
   
   //Initialise board 
   Board* gameboard = new Board();
   // ask num of players
    //Initialises Player 1 
   std::cout << "Enter a name for Player 1 (uppercase characters only)" << std::endl;
   std::cout << ">";
   std::string p1;
   std::cin >> p1;
   // std::cout<<"test 1"<<std::endl;
   LinkedList* p1_hand = new LinkedList();
   Player* player1 = new Player(PLAYER1_NUM,p1,STARTSCORE,p1_hand); //changed player constructor to initialise hand - ryan
   
   // std::cout<<"test 2"<<std::endl;
   player1->setHand(tilebag);
   // std::cout<<"test 3"<<std::endl;
   std::cout << std::endl;
   
   //Initialise Player 2 
   std::cout << "Enter a name for Player 2 (uppercase characters only)" << std::endl;
   std::cout << ">";
   std::string p2;
   std::cin >> p2;
   LinkedList* p2_hand = new LinkedList();
   Player* player2 = new Player(PLAYER2_NUM,p2,STARTSCORE,p2_hand); //changed player constructor to initialise hand - ryan
   player2->setHand(tilebag);
   std::cout << std::endl;
   std::cout << "Let's Play!" << std::endl;

   
   playGame(player1, player2, tilebag, gameboard, player1->getName());
}

void newGame_extra_player(){
   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   //Initialises the tilebag and randomises it.
   std::vector<Tile*> randomisedTiles;
   randomisedTiles = getTiles(randomisedTiles);
   TileBag* tilebag = new TileBag(randomisedTiles);
   
   //Initialise board 
   Board* gameboard = new Board();

   // ask num of players
   std::cout<<"enter the number of players(2-4): ";
   std::string num_of_player = "2";
   // int num_of_player = 0;
   std::cin>> num_of_player;
   std::cout<<std::endl;
   bool check_player_num = false;
   // while((num_of_player!="2")||(num_of_player!="3")||(num_of_player!="4")){
   while(check_player_num== false){
      if((num_of_player=="2")||(num_of_player=="3")||(num_of_player=="4")){
         check_player_num = true;
      }
      else{
         std::cout<<"that is not a valid option"<<std::endl;
         std::cout<<"enter the number of players(2-4): ";
         std::cin>> num_of_player;
         std::cout<<std::endl;
      }
   }
    //Initialises Player 1 
   std::cout << "Enter a name for Player 1 (uppercase characters only)" << std::endl;
   std::cout << ">";
   std::string p1;
   std::cin >> p1;
   // std::cout<<"test 1"<<std::endl;
   LinkedList* p1_hand = new LinkedList();
   Player* player1 = new Player(PLAYER1_NUM,p1,STARTSCORE,p1_hand); //changed player constructor to initialise hand - ryan
   
   // std::cout<<"test 2"<<std::endl;
   player1->setHand(tilebag);
   // std::cout<<"test 3"<<std::endl;
   std::cout << std::endl;
   
   //Initialise Player 2 
   std::cout << "Enter a name for Player 2 (uppercase characters only)" << std::endl;
   std::cout << ">";
   std::string p2;
   std::cin >> p2;
   LinkedList* p2_hand = new LinkedList();
   Player* player2 = new Player(PLAYER2_NUM,p2,STARTSCORE,p2_hand); //changed player constructor to initialise hand - ryan
   player2->setHand(tilebag);
   std::cout << std::endl;
   

   std::vector<Player*> vec_player;
   vec_player.push_back(player1);
   vec_player.push_back(player2);
   if((num_of_player == "3")||(num_of_player == "4")){
      std::cout << "Enter a name for Player 3 (uppercase characters only)" << std::endl;
      std::cout << ">";
      std::string p3;
      std::cin >> p3;
      LinkedList* p3_hand = new LinkedList();
      Player* player3 = new Player(3,p3,STARTSCORE,p3_hand); //changed player constructor to initialise hand - ryan
      player3->setHand(tilebag);
      std::cout << std::endl;
      vec_player.push_back(player3);
      if((num_of_player == "4")){
         std::cout << "Enter a name for Player 4 (uppercase characters only)" << std::endl;
         std::cout << ">";
         std::string p4;
         std::cin >> p4;
         LinkedList* p4_hand = new LinkedList();
         Player* player4 = new Player(4,p4,STARTSCORE,p4_hand); //changed player constructor to initialise hand - ryan
         player4->setHand(tilebag);
         std::cout << std::endl;
         vec_player.push_back(player4);
      }

   }
   std::cout << "Let's Play!" << std::endl;

   
   playGame(vec_player, tilebag, gameboard, player1->getName());// this will be changed to accept a vector of players
}


// if statements for checking if the first line of txt file number == something
//this will tkae alot of work
void loadGame(){
   // load the previous game(load previous player name, number, tiles in hand and so on) from a txt file.
   std::cout << std::endl;
   std::cout << "Enter load game file" << std::endl;
   std::cout << ">";
   std::string path;
   std::cin >> path;
   // user types the filename excluding the file type, and the program will look into the folder
   path = "./save_files/"+path +".save";

   //creates a vector to store all the text from the file
   std::vector<std::string> file_store;
  
   std::ifstream rfile(path);
   std::string line; 

   // if the file exists, the code will store all text into file_store, else it will print a message saying"invalid file"
   if(rfile.is_open()){
      while(!rfile.eof()){
         line = "";
         std::getline(rfile,line);
         file_store.push_back(line);
      }

      // reads in player 1's details from lines 0-2
      std::string player_1_name =file_store[LOAD_LINE_0];
      int player_1_point = std::stoi(file_store[LOAD_LINE_1]);
      //entire hand is stored in one line, meaning that it must be seperated
      std::string player_1_hand = file_store[LOAD_LINE_2];
      std::vector<std::string> word_store;
      
      //temporary token for storing the seperate words
      std::string token;
      //string stream one player 1 hand
      std::stringstream stream(player_1_hand);
      while(std::getline(stream, token, ',')){ // splits when there is a comma
         //places seperated words into the word_store vector
         word_store.push_back(token);
      }

      
      LinkedList* p1_hand  = new LinkedList();
   
      int handSize = word_store.size();
      //for loop to create tiles from word_store
      for( int i = 0; i<handSize; i++){
         int line_size = word_store[i].size();
         char letter = word_store[i][LETTER_PLACEMENT];
         
         
         char value = word_store[i][VALUE_PLACEMENT];
         std::string stringValue = "";
         stringValue.push_back(value);
         //if the value of the tile is greater than 9, extra step must be taken to read the second digit
         if (line_size>3){
            char value2 =word_store[i][SECOND_DIGIT_VALUE];
            stringValue.push_back(value2);
            
            }
         //converts the string containing the value of tile into an integer
         int actualValue = std::stoi(stringValue);
         Tile* newTile = new Tile(letter,actualValue);
         //adds to list
         p1_hand->addToList(*newTile);
         delete newTile;
      }
      //create the player class for player 1
      Player* player1 = new Player(PLAYER1_NUM, player_1_name, player_1_point,p1_hand);
      // player1->printHand();

      // player 2 
      //same steps as player 1 are taken for player 2
      std::string player_2_name =file_store[LOAD_LINE_3];
      int player_2_point = std::stoi(file_store[LOAD_LINE_4]);
      std::string player_2_hand = file_store[LOAD_LINE_5];
      std::vector<std::string> word_store2;
      std::stringstream stream2(player_2_hand);
      while(std::getline(stream2, token, ',')){
         word_store2.push_back(token);
      }
      LinkedList* p2_hand  = new LinkedList();
      int handSize2 = word_store2.size();
      for( int i = 0; i<handSize2; i++){
         int line_size = word_store2[i].size();
         char letter = word_store2[i][LETTER_PLACEMENT];
         char value = word_store2[i][VALUE_PLACEMENT];
         std::string stringValue = "";
         stringValue.push_back(value);
         if (line_size>3){
            char value2 = word_store2[i][SECOND_DIGIT_VALUE];
            stringValue.push_back(value2);
                
            }
         int actualValue = std::stoi(stringValue);
         Tile* newTile = new Tile(letter,actualValue);
         p2_hand->addToList(*newTile);
         delete newTile;
      }

      Player* player2 = new Player(PLAYER2_NUM, player_2_name, player_2_point,p2_hand);
      // tilebag load here
      //the same steps of converting string to tile from the player classes are featured here,
      //  the only difference is that tiles are being stored into a vector
      std::string bag = file_store[LOAD_LINE_7];
      std::vector<std::string> bag_store;
      std::stringstream bagstream(bag);

      while(std::getline(bagstream, token, ',')){
         bag_store.push_back(token);
      }
      int bagSize = bag_store.size();
      std::vector<Tile*> bagVec;
      for( int i = 0; i<bagSize; i++){
         int line_size = bag_store[i].size();
         char letter = bag_store[i][LETTER_PLACEMENT];
         char value = bag_store[i][VALUE_PLACEMENT];
         std::string stringValue = "";
         stringValue.push_back(value);
         if (line_size>3){
            char value2 =bag_store[i][SECOND_DIGIT_VALUE];
            stringValue.push_back(value2);
                
         }
         int actualValue = std::stoi(stringValue);
         Tile* newTile = new Tile(letter,actualValue);


         bagVec.push_back(newTile);

      }
      //creates tilebag using vector
      TileBag* newBag = new TileBag(bagVec);


      //board laod
      Board* gameBoard = new Board();
      std::string boardPlacement = file_store[LOAD_LINE_6];
      std::vector<std::string> board_store;

      std::stringstream boardstream(boardPlacement);

      //splits word apart using  boardstream
      while(std::getline(boardstream, token, ' ')){
         board_store.push_back(token);
      }

      int board_size = board_store.size();
      for(int i = 0; i<board_size; i++){
         int elementSize = board_store[i].size();
         //stores the word aquired from string steam into variable stringValueBoard
         std::string stringValueBoard = board_store[i];
         char boardletter = stringValueBoard[0]; //stores the character on the board here
         int pos  = X_POS;// positoon string steam will start from
         int end =  END_OF_WORD;// how long the string is
         if(elementSize>END_OF_WORD){
            //when element size is greater, that means it is placed on column with 2 digits meaining the string must be longer
            end =5;
         }        
         //creates new string for the column value
         std::string value_string = stringValueBoard.substr(pos,end);
         //turns new string into an integer
         int actualCol = std::stoi(value_string);
         //stores the row value
         char rowVal = board_store[i][Y_POS];

         //finally adds the tile to the board
         gameBoard->addTileToBoard(boardletter,actualCol,rowVal);
      }
      std::string currentPlayer = file_store[8];
      rfile.close();
      //starts the game with loaded in classes
   playGame(player1, player2, newBag, gameBoard,currentPlayer);

   }
   else{
      std::cout<<"invalid file name"<<std::endl;
   }

}
void loadGame_extra_player(){
   // load the previous game(load previous player name, number, tiles in hand and so on) from a txt file.
   std::cout << std::endl;
   std::cout << "Enter load game file" << std::endl;
   std::cout << ">";
   std::string path;
   std::cin >> path;
   // user types the filename excluding the file type, and the program will look into the folder
   path = "./save_file_extra/"+path +".save";

   //creates a vector to store all the text from the file
   std::vector<std::string> file_store;
  
   std::ifstream rfile(path);
   std::string line; 
   // std::cout<<"test"<<std::endl;
   // if the file exists, the code will store all text into file_store, else it will print a message saying"invalid file"
   if(rfile.is_open()){
      // int itteration = 0;
      while(!rfile.eof()){
         line = "";
         // std::cout<<itteration<<std::endl;
         std::getline(rfile,line);
         file_store.push_back(line);

      }
      // std::cout<<"test-filestrem"<<std::endl;
      int num_players = std::stoi(file_store[0]);
      // std::cout<<"num test"<<std::endl;
      std::vector<Player*> vec_players;


      
      std::string player_1_name =file_store[4];
      int player_1_point = std::stoi(file_store[5]);
      std::string player_1_hand = file_store[6];
      std::vector<std::string> word_store;

      //temporary token for storing the seperate words
      std::string token;
      //string stream one player 1 hand
      std::stringstream stream(player_1_hand);
      while(std::getline(stream, token, ',')){ // splits when there is a comma
         //places seperated words into the word_store vector
         word_store.push_back(token);
      }
     
      LinkedList* p1_hand  = new LinkedList();
      int handSize = word_store.size();
      //for loop to create tiles from word_store
      for( int i = 0; i<handSize; i++){
         int line_size = word_store[i].size();
         char letter = word_store[i][LETTER_PLACEMENT];
         char value = word_store[i][VALUE_PLACEMENT];
         std::string stringValue = "";
         stringValue.push_back(value);
         //if the value of the tile is greater than 9, extra step must be taken to read the second digit
         if (line_size>3){
            char value2 =word_store[i][SECOND_DIGIT_VALUE];
            stringValue.push_back(value2);
            
            }
         //converts the string containing the value of tile into an integer
         int actualValue = std::stoi(stringValue);
         Tile* newTile = new Tile(letter,actualValue);
         //adds to list
         p1_hand->addToList(*newTile);
         delete newTile;
      }
      

      //create the player class for player 1
      Player* player1 = new Player(PLAYER1_NUM, player_1_name, player_1_point,p1_hand);
      vec_players.push_back(player1);
      // std::cout<<"p1 success"<<std::endl;
      // player 2 
      //same steps as player 1 are taken for player 2
      std::string player_2_name =file_store[7];
      int player_2_point = std::stoi(file_store[8]);
      std::string player_2_hand = file_store[9];
      std::vector<std::string> word_store2;
      std::stringstream stream2(player_2_hand);
      while(std::getline(stream2, token, ',')){
         word_store2.push_back(token);
      }
      LinkedList* p2_hand  = new LinkedList();
      int handSize2 = word_store2.size();
      for( int i = 0; i<handSize2; i++){
         int line_size = word_store2[i].size();
         char letter = word_store2[i][LETTER_PLACEMENT];
         char value = word_store2[i][VALUE_PLACEMENT];
         std::string stringValue = "";
         stringValue.push_back(value);
         if (line_size>3){
            char value2 = word_store2[i][SECOND_DIGIT_VALUE];
            stringValue.push_back(value2);
                
            }
         int actualValue = std::stoi(stringValue);
         Tile* newTile = new Tile(letter,actualValue);
         p2_hand->addToList(*newTile);
         delete newTile;
      }

      Player* player2 = new Player(PLAYER2_NUM, player_2_name, player_2_point,p2_hand);
      vec_players.push_back(player2);
      // std::cout<<"p2 success"<<std::endl;
      
      if(num_players>=3){
         std::string player_3_name =file_store[10];
         int player_3_point = std::stoi(file_store[11]);
         std::string player_3_hand = file_store[12];
         std::vector<std::string> word_store3;
         std::stringstream stream3(player_3_hand);
         while(std::getline(stream3, token, ',')){
            word_store3.push_back(token);
         }
         LinkedList* p3_hand  = new LinkedList();
         int handSize3 = word_store3.size();
         for( int i = 0; i<handSize3; i++){
            int line_size = word_store3[i].size();
            char letter = word_store3[i][LETTER_PLACEMENT];
            char value = word_store3[i][VALUE_PLACEMENT];
            std::string stringValue = "";
            stringValue.push_back(value);
            if (line_size>3){
               char value3 = word_store3[i][SECOND_DIGIT_VALUE];
               stringValue.push_back(value3);
                  
               }
            int actualValue = std::stoi(stringValue);
            Tile* newTile = new Tile(letter,actualValue);
            p3_hand->addToList(*newTile);
            delete newTile;
         }

         Player* player3 = new Player(3, player_3_name, player_3_point,p3_hand);
         vec_players.push_back(player3);

         // std::cout<<"p3 success"<<std::endl;

         if(num_players== 4){
            std::string player_4_name =file_store[13];
            int player_4_point = std::stoi(file_store[14]);
            std::string player_4_hand = file_store[15];
            std::vector<std::string> word_store4;
            std::stringstream stream4(player_4_hand);
            while(std::getline(stream4, token, ',')){
               word_store4.push_back(token);
            }
            LinkedList* p4_hand  = new LinkedList();
            int handSize4 = word_store4.size();
            for( int i = 0; i<handSize4; i++){
               int line_size = word_store4[i].size();
               char letter = word_store4[i][LETTER_PLACEMENT];
               char value = word_store4[i][VALUE_PLACEMENT];
               std::string stringValue = "";
               stringValue.push_back(value);
               if (line_size>3){
                  char value4 = word_store4[i][SECOND_DIGIT_VALUE];
                  stringValue.push_back(value4);
                     
                  }
               int actualValue = std::stoi(stringValue);
               Tile* newTile = new Tile(letter,actualValue);
               p4_hand->addToList(*newTile);
               delete newTile;
            }

            Player* player4 = new Player(4, player_4_name, player_4_point,p4_hand);
            vec_players.push_back(player4);
            // std::cout<<"p4 success"<<std::endl;
         }

      }
      // tilebag load here
      //the same steps of converting string to tile from the player classes are featured here,
      //  the only difference is that tiles are being stored into a vector

      std::string bag = file_store[2];
      std::vector<std::string> bag_store;
      std::stringstream bagstream(bag);

      while(std::getline(bagstream, token, ',')){
         bag_store.push_back(token);
      }
      int bagSize = bag_store.size();
      std::vector<Tile*> bagVec;
      for( int i = 0; i<bagSize; i++){
         int line_size = bag_store[i].size();
         char letter = bag_store[i][LETTER_PLACEMENT];
         char value = bag_store[i][VALUE_PLACEMENT];
         std::string stringValue = "";
         stringValue.push_back(value);
         if (line_size>3){
            char value2 =bag_store[i][SECOND_DIGIT_VALUE];
            stringValue.push_back(value2);
                
         }
         int actualValue = std::stoi(stringValue);
         Tile* newTile = new Tile(letter,actualValue);


         bagVec.push_back(newTile);

      }
      //creates tilebag using vector
      TileBag* newBag = new TileBag(bagVec);
      // std::cout<<"bag success"<<std::endl;

      //board laod
      Board* gameBoard = new Board();
      std::string boardPlacement = file_store[1];
      std::vector<std::string> board_store;

      std::stringstream boardstream(boardPlacement);

      //splits word apart using  boardstream
      while(std::getline(boardstream, token, ' ')){
         board_store.push_back(token);
      }

      int board_size = board_store.size();
      for(int i = 0; i<board_size; i++){
         int elementSize = board_store[i].size();
         //stores the word aquired from string steam into variable stringValueBoard
         std::string stringValueBoard = board_store[i];
         char boardletter = stringValueBoard[0]; //stores the character on the board here
         int pos  = X_POS;// positoon string steam will start from
         int end =  END_OF_WORD;// how long the string is
         if(elementSize>END_OF_WORD){
            //when element size is greater, that means it is placed on column with 2 digits meaining the string must be longer
            end =5;
         }        
         //creates new string for the column value
         std::string value_string = stringValueBoard.substr(pos,end);
         //turns new string into an integer
         int actualCol = std::stoi(value_string);
            //stores the row value
         char rowVal = board_store[i][Y_POS];

         //finally adds the tile to the board
         gameBoard->addTileToBoard(boardletter,actualCol,rowVal);
      }
      // std::cout<<"bioard success"<<std::endl;
      std::string currentPlayer = file_store[3];
      // std::cout<<currentPlayer<<std::endl;
      rfile.close();
      //starts the game with loaded in classes
   playGame(vec_players, newBag, gameBoard,currentPlayer);

   }
   else{
      std::cout<<"invalid file name"<<std::endl;
   }

}

void saveGame(Player* player1, Player* player2, TileBag* tiles_,Board* gameBoard,std::string currentPlay, std::string fileName){
   //saves file into folder with file type being .save
   fileName = "./save_files/"+fileName+".save";
   std::ofstream saveFile(fileName);
   
   //for loop for  saving players

   //player1 save
   std::string p1name  = player1->getName();
   saveFile<<p1name; // writes player 1 nameinto file
   saveFile<<'\n';
   saveFile<<player1->getPoint();
   saveFile<<'\n';
   //creates vector of players hand
   std::vector<std::string> player1_hand_save = player1->saveHand();
   //loop through vector to save the tiles 
   int p1_hand_size = player1_hand_save.size();
   for(int i = 0; i<=p1_hand_size; i++){
      saveFile<<player1_hand_save[i];
   }
   saveFile<<'\n';
   // player 2 save
   //saves player 2's name point and hand
   saveFile<<player2->getName();
   saveFile<<'\n';
   saveFile<<player2->getPoint();
   saveFile<<'\n';
   std::vector<std::string> player2_hand_save = player2->saveHand();

   int p2_hand_size = player2_hand_save.size();
   for(int i = 0; i<=p2_hand_size; i++){
      saveFile<<player2_hand_save[i];
   }
   saveFile<<'\n';

   // board save
   //loops through the board and saves to file
   std::vector<std::string> boardSave =gameBoard->saveBoard();
   for ( auto thingy  =  boardSave.begin(); thingy != boardSave.end(); ++thingy){
      saveFile<<*thingy;
   }
   saveFile<<'\n';

   //bagsave

   std::vector<std::string> bag_save = tiles_->saveBag();
   //loops through tilebag and saves
   int tilebagSize = bag_save.size();
   for(int i = 0; i<=tilebagSize; i++){
      saveFile<<bag_save[i];
   }
   saveFile<<'\n';
   //saves the current player's name
   saveFile<<currentPlay<<'\n';
   saveFile.close();

}
void saveGame(std::vector<Player*> vec_players, TileBag* tiles_,Board* gameBoard,std::string currentPlay, std::string fileName){
   //saves file into folder with file type being .save
   fileName = "./save_file_extra/"+fileName+".save";
   std::ofstream saveFile(fileName);
   
   //for loop for  saving players
   int player_size = vec_players.size();
   saveFile<<player_size;
   saveFile<<'\n';

   // board save
   //loops through the board and saves to file
   std::vector<std::string> boardSave =gameBoard->saveBoard();
   for ( auto thingy  =  boardSave.begin(); thingy != boardSave.end(); ++thingy){
      saveFile<<*thingy;
   }
   saveFile<<'\n';

   //bagsave

   std::vector<std::string> bag_save = tiles_->saveBag();
   //loops through tilebag and saves
   int tilebagSize = bag_save.size();
   for(int i = 0; i<=tilebagSize; i++){
      saveFile<<bag_save[i];
   }
   saveFile<<'\n';
   //saves the current player's name
   saveFile<<currentPlay<<'\n';
   int vec_players_size = vec_players.size();

   for(int i = 0; i< vec_players_size; i++){
      std::string p1name  = vec_players[i]->getName();
      saveFile<<p1name; // writes player 1 nameinto file
      saveFile<<'\n';
      saveFile<<vec_players[i]->getPoint();
      saveFile<<'\n';
      //creates vector of players hand
      std::vector<std::string> player1_hand_save = vec_players[i]->saveHand();
      //loop through vector to save the tiles 
      int p1_hand_size = player1_hand_save.size();
      for(int i = 0; i<=p1_hand_size; i++){
         saveFile<<player1_hand_save[i];
      }
      saveFile<<'\n';
   }
   saveFile.close();

}

//playGame(): core gameplay is stored here
void playGame(Player* player1, Player* player2, TileBag* tilebag, Board* gameboard, std::string curentPlayer)
{
   //initilaise a vector of players
   std::vector<Player*> players = {player1, player2};
   int i = 0; //used to rotate between players
   if(curentPlayer == player2->getName()){
      i = 1;
   }
   // bool gameEnd = doesGameEnd(player1, player2, gameboard, tilebag); //called to see if game ends: UNSURE IF WORKS
   bool gameEnd = false;
   while(gameEnd == false){
      Player* currentPlayer = players[i]; //access player at ith index (first turn, i=0)
      
      takeTurn(currentPlayer,player1,player2, tilebag, gameboard); //player takes turn
      i++; //increments i
      i = i % (players.size()); //sets i to be the mod of the player vector size, hence allowing for rotation between players
      //game should end if player 1 has passed twice in a row.
      if(player1->getPass() == 2){
         gameEnd = true;
      }
      //game should end if player 2 has passed twice in a row.
      else if(player2->getPass() == 2){
         gameEnd = true;
      }
      /*
      for loop for players get pass
      */
      //game should end if tilebag is empty.
      else if(tilebag->getSize() ==0){
         gameEnd = true;
      }
   } 
   if(gameEnd == true) //if game end conditions are satisfied
   {
      std::string message = "";
      std::string saveScore = "high_score.txt";
      std::vector<std::string> highscore_vec;
      std::fstream fileEdit;
      fileEdit.open(saveScore);
      std::string line;
      if(fileEdit.is_open()){
         while(!fileEdit.eof()){
            line = "";
            std::getline(fileEdit, line);
            highscore_vec.push_back(line);
         }
         fileEdit.close();
      }

      //finds and declares the winning player if player 1 and 2 do not have the same score.
      if(player1->getPoint() != player2->getPoint())
      {  
         std::string winningPlayer = "";
         int score = 0;
         if(player1->getPoint() > player2->getPoint())
         {
            winningPlayer = player1->getName();
            score = player1->getPoint();
         }
         else if(player2->getPoint() > player1->getPoint())
         {
            winningPlayer = player2->getName();
            score = player2->getPoint();
         }
         
         int high_vec_size = highscore_vec.size();
         if (high_vec_size<2){
            //write to file here
            std::ofstream saveHigh(saveScore);
            saveHigh<<winningPlayer;
            saveHigh<<'\n';
            saveHigh<<score;
         }
         else{
            std::string high_name = highscore_vec[0];
            // std::string high_string = ;
            int highscore = std::stoi(highscore_vec[1]);
            //if check
            if (score> highscore){
               //write to file
               std::ofstream saveHigh(saveScore);
               saveHigh<<winningPlayer;
               saveHigh<<'\n';
               saveHigh<<score;
               high_name = winningPlayer;
               highscore =score;
            }
            message ="Highscore: "+std::to_string(highscore)+" by: "+high_name;
         }

      //prints out results
         std::cout << "GAME OVER!" << std::endl;
         std::cout << "Score for " << player1->getName() << ":" << player1->getPoint() << std::endl;
         std::cout << "Score for " << player2->getName() << ":" << player2->getPoint() << std::endl;
         std::cout << "The winner is: " << winningPlayer << " , with a score of " << score <<std::endl;
         
      }
      //if player1 and 2 have the same score, declare a tie
      else if(player1->getPoint() == player2->getPoint())
      {
         //print result
         std::cout << "The game was a tie. The players had a score of: " << player1->getPoint() << std::endl;
         int high_vec_size = highscore_vec.size();
         if (high_vec_size<2){
            //write to file here
            std::ofstream saveHigh(saveScore);
            saveHigh<<"it was a tie";
            saveHigh<<'\n';
            saveHigh<<player1->getPoint();
         }
         else{
            message =  + "Highscore: "+highscore_vec[1]+" by: "+highscore_vec[0];
         }
      
      }
      //save highscore here
         
      std::cout<<message<<std::endl;
      std::cout << "Goodbye!" << std::endl; 


      // exit(0);
      //delete contents of game.
      delete player1;
      delete player2;
      delete tilebag;
      delete gameboard;
   } 
}
void playGame(std::vector<Player*> vec_players, TileBag* tilebag, Board* gameboard, std::string curentPlayer)
{

   int i = 0; //used to rotate between players
   bool gameEnd = false;
   int player_size = vec_players.size();
   for(int j = 0; j < player_size; j++){
      std::string curentName = vec_players[j]->getName();
      // std::cout<<curentPlayer<<" "<<vec_players[j]->getName()<<std::endl;
      if(curentPlayer == curentName){
         i = j;
         // std::cout<<"i has changed"<<std::endl;
      }
   }
   while(gameEnd == false){
      Player* currentPlayer = vec_players[i]; //access player at ith index (first turn, i=0)
      
      takeTurn(currentPlayer,vec_players, tilebag, gameboard); //player takes turn
      
      i++; //increments i
      i = i % (player_size); //sets i to be the mod of the player vector size, hence allowing for rotation between players
      
      for(int i = 0; i< player_size; i++){
         if(vec_players[i]->getPass() == 2){
            gameEnd = true ;
         }
      }

      //game should end if tilebag is empty.
      if(tilebag->getSize() ==0){
         gameEnd = true;
      }
   } 
   if(gameEnd == true) //if game end conditions are satisfied
   {
      std::string message = "";
      std::string saveScore = "high_score.txt";
      std::vector<std::string> highscore_vec;
      std::fstream fileEdit;
      fileEdit.open(saveScore);
      std::string line;
      if(fileEdit.is_open()){
         while(!fileEdit.eof()){
            line = "";
            std::getline(fileEdit, line);
            highscore_vec.push_back(line);
         }
         fileEdit.close();
      }

      int max_score = 0;
      std::string max_player = "";
      bool tie = false;
      // array of players that tied
      std::vector<Player*> tieplayer;
      int point = 0;
      for(int i = 0; i<player_size; i++){
         point = vec_players[i]->getPoint();
         if(point == max_score){
            tie = true;
            tieplayer.push_back(vec_players[i]);//add to list
         }
         if(point>max_score){
            max_score = point;
            max_player =  vec_players[i]->getName();
            tie  = false;
            tieplayer.clear();
            //clear list
         }
      }
      //}



      //finds and declares the winning player if player 1 and 2 do not have the same score.
      if (tie == true)
      {
         // gotta change this up to to actually get the tie score
         //print result
         std::cout << "The game was a tie between players: ";// << vec_players[0]->getPoint() << std::endl;
         int tie_size = tieplayer.size();
         for (int i = 0; i<tie_size;i++){
            std::cout<<tieplayer[i]->getName()<<" ";
         }
         std::cout<<std::endl;
         int high_vec_size = highscore_vec.size();
         if (high_vec_size<2){
            //write to file here
            std::ofstream saveHigh(saveScore);
            saveHigh<<"it was a tie between: ";
            for (int i = 0; i<tie_size;i++){
            saveHigh<<tieplayer[i]->getName()<<" ";
            }
            saveHigh<<'\n';
            saveHigh<<vec_players[0]->getPoint();
         }
         else{
            std::string high_name = highscore_vec[0];
            // std::string high_string = ;
            int highscore = std::stoi(highscore_vec[1]);
            if (max_score> highscore){
               //write to file
               std::ofstream saveHigh(saveScore);
               saveHigh<<max_player;
               saveHigh<<'\n';
               saveHigh<<max_score;
               high_name = max_player;
               highscore =max_score;
            }
            message =  "Highscore: "+highscore_vec[1]+" by: "+highscore_vec[0];
            //if check
         }
         

      }
      else
      {  
         
         int high_vec_size = highscore_vec.size();
         if (high_vec_size<2){
            //write to file here
            std::ofstream saveHigh(saveScore);
            saveHigh<<max_player;
            saveHigh<<'\n';
            saveHigh<<max_score;
         }
         else{
            std::string high_name = highscore_vec[0];
            // std::string high_string = ;
            int highscore = std::stoi(highscore_vec[1]);
            //if check
            if (max_score> highscore){
               //write to file
               std::ofstream saveHigh(saveScore);
               saveHigh<<max_player;
               saveHigh<<'\n';
               saveHigh<<max_score;
               high_name = max_player;
               highscore =max_score;
            }
            message ="Highscore: "+std::to_string(highscore)+" by: "+high_name;
         }

      //prints out results
         std::cout << "GAME OVER!" << std::endl;
         for(int i = 0; i< player_size; i++){
            std::cout << "Score for " << vec_players[i]->getName() << ":" << vec_players[i]->getPoint() << std::endl;   
         }
         std::cout << "The winner is: " << max_player << " , with a score of " << max_score <<std::endl;
         
      
      //if player1 and 2 have the same score, declare a tie
      // else if(vec_players[0]->getPoint() == vec_players[1]->getPoint())
      
      
      }
      //save highscore here
         
      std::cout<<message<<std::endl;
      std::cout << "Goodbye!" << std::endl; 


      // exit(0);
      //delete contents of game.
      // delete player1;
      // delete player2;
      int player_num = vec_players.size();
      for (int i = 0; i<player_num; i++ ){
         delete vec_players[i];
      }
      delete tilebag;
      delete gameboard;
   } 
}

//takeTurn(): majority of game logic is stored here, recurs while working
void takeTurn(Player* currentPlayer,Player* p1, Player* p2, TileBag* tileBag, Board* gameboard)
{
   int bingo = 0;
   std::cout << "Turn of: " << currentPlayer->getName() << std::endl; //displays name of current player
   //uses bool, set to false initially, to recur multiple actions in a turn.
   bool finished = false;
   while(finished == false){
      //if tilebag has no tiles
      if(tileBag->getSize() ==0){
         finished = true; //end turn
      }
      else{

         //at start of turn/action, display scores and names of players
         std::cout<<"Score for "<<p1->getName()<<": "<<p1->getPoint()<<std::endl;
         std::cout<<"Score for "<<p2->getName()<<": "<<p2->getPoint()<<std::endl;
         gameboard->printBoard(); //print board
         std::cout<<std::endl;

         std::cout<<"Your hand is"<<std::endl; //print hand
         currentPlayer->printHand();
         std::cout<<"< ";
         
         //player input
         std::string playerCommand;
         //std::cout << "a" << std::endl;
         std::cin.ignore(); //used to avoid seg fault due to unallocated spaces in string ???
         std::getline(std::cin,playerCommand);

         //code deleted first character after second loop, thus we need to palce something here in the case of one character inputed
         playerCommand.insert(0,1,'_');
         std::vector<std::string> playerCommandArray;

         std::string playerInput;
         
         // std::cout<<"test store"<<std::endl;
         std::stringstream stream(playerCommand); 
         while(std::getline(stream, playerInput,' ')) //getline with delimeter set to ' '
         {
            playerCommandArray.push_back(playerInput);
            //initialised player command vector
         }
      
         //game logic
         std::string playerAction = playerCommandArray[0]; //0th element refers to player action

         //if equal to _lace or _place, 
         if((playerAction == "_lace")||(playerAction == "_place"))
         {
               
            if((playerCommandArray[1] == "Done")||(playerCommandArray[1] == "done")) //finish turn if command array equals done
            {
               //done with turn
               // std::cout<<"done test"<<std::endl;
               finished = true; //ends turn 
            }
            else
            {
               std::string playerLetter = playerCommandArray[1]; //assigns first index to player letter 
               char playerLetterChar = playerLetter[0]; //convert letter from string to char

               std::string letterPosition = playerCommandArray[2]; //assign 2nd index of playerCommandArray to letter position
               int stringlen = letterPosition.size(); //used to dictate length of str used to store position
               
               //convert letter position to row and column
               int num_to_use = 1;
               if(stringlen>2){
                  num_to_use = 2;
               }

               char letterRow = letterPosition[0]; //row converted to char
               std::string value_string = letterPosition.substr(STRING_LENGTH,num_to_use); //takes string of length num_to_use
               int letterColumn = std::stoi(value_string);         //converts the string that contains the column variable into a integer
               
               // checks to see if the player has the tile they are trying to place
               if(currentPlayer->checkForTile(playerLetterChar) == true)
               {
                  //checks if the tile was placed legally
                  if(gameboard->legalTilePlacement(letterColumn, letterRow) == true)
                  {
                     //places the tile onto the board
                     currentPlayer->placeTile(playerLetterChar, gameboard, letterColumn, letterRow);
                     bingo+=1;
                     //bingo occurs when player places 7 tiles in their turn, which adds 50 points to their total
                     if(bingo >= 7){
                        std::cout<<"BINGO!"<<std::endl;
                        currentPlayer->addPoints(50);
                        bingo = 0;
                     }
                     // player has not passed, therefore the pass count is reset to 0
                     currentPlayer->resetPass();
                     
                     if(tileBag->getSize() >= 0)
                     {
                     //if tile size is not 0, it draws a tile from the bag
                        currentPlayer->drawTile(tileBag);
                     }
                     else
                     {
                        //
                        std::cout << "There are no tiles left in the tilebag." << std::endl;
                        finished = true;
                     }
                  }
                  else
                  {
                     // invalid placement conveyed to user, and lo
                     std::cout<<"Invalid Tile Position:"<<std::endl;
                  }
               }
               else
               {

                  std::cout<<"Invalid Tile:"<<std::endl;

               }
            }
         }
         //saves the game  using users input for filename
         else if((playerAction == "_save")||((playerAction == "_ave"))){
            saveGame(p1,p2,tileBag,gameboard,currentPlayer->getName(),playerCommandArray[1]);
         }
         else if ((playerAction == "_finish")||(playerAction == "_inish")){
            finished = true;

            currentPlayer->increasePass();
            currentPlayer->increasePass();
         }
         else if((playerAction == "_help")||(playerAction == "_elp")){
            //hint function
            printHelp();
         }
         //the replace tile command for the current player
         else if((playerAction == "_eplace")||(playerAction == "_replace"))
         {
            //finds tile to replace from player command
            std::string playerTile = playerCommandArray[1];
            char playerLetterChar = playerTile[0];
            if(playerTile.length() != 1)
            {
               // throw std::runtime_error("Invalid Tile input:");
               std::cout<<"Invalid Tile input:"<<std::endl;

            }
            else
            {
               //if player has the tile specified, tile is then swaped with another tile from tilebag
               if(currentPlayer->checkForTile(playerLetterChar)==true){
                  currentPlayer->replaceTile(playerLetterChar,tileBag);
               }
               else{
                  std::cout<<"invalid input"<<std::endl;
               }
               //player pass count = 0;
               //end turn 
            }
            currentPlayer->resetPass();
         }
         //checks if the player passes
         else if((playerAction == "_ass")||(playerAction == "_pass"))
         {
            //change turn, increment pass counter
            finished = true;

            currentPlayer->increasePass();
         }
         else{
            //player has typed in an invalid input and the code loops
            std::cout<<"invalid input:"<<std::endl;
            std::cout<<std::endl;
         }
      //clears the array
      int size = playerCommandArray.size();
      for(int i =0; i<size; i++){
         playerCommandArray[i] = ' ';
      }
      }
       
   }
}
//takeTurn(): majority of game logic is stored here, recurs while working, vector of players edition
void takeTurn(Player* currentPlayer,std::vector<Player*> vec_players, TileBag* tileBag, Board* gameboard)
{
   int bingo = 0;
   std::cout << "Turn of: " << currentPlayer->getName() << std::endl; //displays name of current player
   //uses bool, set to false initially, to recur multiple actions in a turn.
   bool finished = false;
   int player_num = vec_players.size();
   while(finished == false){
      //if tilebag has no tiles
      if(tileBag->getSize() ==0){
         finished = true; //end turn
      }
      else{

         // //at start of turn/action, display scores and names of players
         // std::cout<<"Score for "<<p1->getName()<<": "<<p1->getPoint()<<std::endl;
         // std::cout<<"Score for "<<p2->getName()<<": "<<p2->getPoint()<<std::endl;
         for(int i = 0; i<player_num; i++){
            std::cout<<"Score for "<<vec_players[i]->getName()<<": "<<vec_players[i]->getPoint()<<std::endl;
         }
         gameboard->printBoard(); //print board
         std::cout<<std::endl;

         std::cout<<"Your hand is"<<std::endl; //print hand
         currentPlayer->printHand();
         std::cout<<"< ";
         
         //player input
         std::string playerCommand;
         //std::cout << "a" << std::endl;
         std::cin.ignore(); //used to avoid seg fault due to unallocated spaces in string ???
         std::getline(std::cin,playerCommand);

         //code deleted first character after second loop, thus we need to palce something here in the case of one character inputed
         playerCommand.insert(0,1,'_');
         std::vector<std::string> playerCommandArray;

         std::string playerInput;
         
         // std::cout<<"test store"<<std::endl;
         std::stringstream stream(playerCommand); 
         while(std::getline(stream, playerInput,' ')) //getline with delimeter set to ' '
         {
            playerCommandArray.push_back(playerInput);
            //initialised player command vector
         }
      
         //game logic
         std::string playerAction = playerCommandArray[0]; //0th element refers to player action

         //if equal to _lace or _place, 
         if((playerAction == "_lace")||(playerAction == "_place"))
         {
            if((playerCommandArray[1] == "Done")||(playerCommandArray[1] == "done")) //finish turn if command array equals done
            {
               //done with turn
               // std::cout<<"done test"<<std::endl;
               finished = true; //ends turn 
            }
            else
            {
               std::string playerLetter = playerCommandArray[1]; //assigns first index to player letter 
               char playerLetterChar = playerLetter[0]; //convert letter from string to char

               std::string letterPosition = playerCommandArray[2]; //assign 2nd index of playerCommandArray to letter position
               int stringlen = letterPosition.size(); //used to dictate length of str used to store position
               
               //convert letter position to row and column
               int num_to_use = 1;
               if(stringlen>2){
                  num_to_use = 2;
               }

               char letterRow = letterPosition[0]; //row converted to char
               std::string value_string = letterPosition.substr(STRING_LENGTH,num_to_use); //takes string of length num_to_use
               int letterColumn = std::stoi(value_string);         //converts the string that contains the column variable into a integer
               
               // checks to see if the player has the tile they are trying to place
               if(currentPlayer->checkForTile(playerLetterChar) == true)
               {
                  //checks if the tile was placed legally
                  if(gameboard->legalTilePlacement(letterColumn, letterRow) == true)
                  {
                     //places the tile onto the board
                     currentPlayer->placeTile(playerLetterChar, gameboard, letterColumn, letterRow);
                     bingo+=1;
                     //bingo occurs when player places 7 tiles in their turn, which adds 50 points to their total
                     if(bingo >= 7){
                        std::cout<<"BINGO!"<<std::endl;
                        currentPlayer->addPoints(50);
                        bingo = 0;
                     }
                     // player has not passed, therefore the pass count is reset to 0
                     currentPlayer->resetPass();
                     
                     if(tileBag->getSize() >= 0)
                     {
                     //if tile size is not 0, it draws a tile from the bag
                        currentPlayer->drawTile(tileBag);
                     }
                     else
                     {
                        //
                        std::cout << "There are no tiles left in the tilebag." << std::endl;
                        finished = true;
                     }
                  }
                  else
                  {
                     // invalid placement conveyed to user, and lo
                     std::cout<<"Invalid Tile Position:"<<std::endl;
                  }
               }
               else
               {

                  std::cout<<"Invalid Tile:"<<std::endl;

               }
            }
         }
         //saves the game  using users input for filename
         else if((playerAction == "_save")||((playerAction == "_ave"))){
            saveGame(vec_players,tileBag,gameboard,currentPlayer->getName(),playerCommandArray[1]);
         }
         else if((playerAction == "_help")||(playerAction == "_elp")){
            //hint function
            printHelp();
         }
         else if ((playerAction == "_finish")||(playerAction == "_inish")){
            finished = true;

            currentPlayer->increasePass();
            currentPlayer->increasePass();
         }
         //the replace tile command for the current player
         else if((playerAction == "_eplace")||(playerAction == "_replace"))
         {
            //finds tile to replace from player command
            std::string playerTile = playerCommandArray[1];
            char playerLetterChar = playerTile[0];
            if(playerTile.length() != 1)
            {
               // throw std::runtime_error("Invalid Tile input:");
               std::cout<<"Invalid Tile input:"<<std::endl;

            }
            else
            {
               //if player has the tile specified, tile is then swaped with another tile from tilebag
               if(currentPlayer->checkForTile(playerLetterChar)==true){
                  currentPlayer->replaceTile(playerLetterChar,tileBag);
               }
               else{
                  std::cout<<"invalid input"<<std::endl;
               }
               //player pass count = 0;
               //end turn 
            }
            currentPlayer->resetPass();
         }
         //checks if the player passes
         else if((playerAction == "_ass")||(playerAction == "_pass"))
         {
            //change turn, increment pass counter
            finished = true;

            currentPlayer->increasePass();
         }
         else{
            //player has typed in an invalid input and the code loops
            std::cout<<"invalid input:"<<std::endl;
            std::cout<<std::endl;
         }
      //clears the array
      int size = playerCommandArray.size();
      for(int i =0; i<size; i++){
         playerCommandArray[i] = ' ';
      }
      }
       
   }
}