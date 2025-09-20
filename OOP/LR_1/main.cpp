#include <iostream>
#include <string>
#include "include/removeVowels.h"

int main()
{
  std::string str;

  std::cin >> str;

  std::cout << "result: " << removeVowels(str) << std::endl;

  return 0;
}