#include "../include/removeVowels.h"
#include <string>

std::string removeVowels(std::string str){

    std::string glasnye = "aeiou";
    std::string final = "";

    int flag = 0;

    for(int i = 0; i < std::size(str); i++){
        for(int j = 0; j < 5; j++){
            if(tolower(str[i]) == glasnye[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            flag = 0;
            continue;
        }
        final += str[i];
    }
    return final;
}