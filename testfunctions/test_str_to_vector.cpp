#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

int main(void)
{
   std::string playerCommand;
   std::cout << "a" << std::endl;
   // std::cin >> playerCommand;
   std::getline(std::cin,playerCommand);
   //std::cout<<playerCommand<<std::endl;
   std::vector<std::string> playerCommandArray;

   std::string playerInput;
   std::stringstream stream(playerCommand);
   while(std::getline(stream, playerInput,' '))
   {
      playerCommandArray.push_back(playerInput);
   }

   int y =playerCommandArray.size();
   std::cout << y << std::endl;

   for(int i = 0; i < y ; i++)
   {
      std::cout << playerCommandArray[i] << std::endl;
   }
}
