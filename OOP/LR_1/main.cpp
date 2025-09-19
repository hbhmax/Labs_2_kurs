#include <iostream>
#include <string>


int main(int argc, char * argv[]){

    std::string glasnye = "aeiou";

    std::string s;
    std::getline(std::cin, s);

    int flag = 0;

    for(int i = 0; i < std::size(s); i++){
        for(int j = 0; j < 5; j++){
            if(tolower(s[i]) == glasnye[j]){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            flag = 0;
            continue;
        }
        std::cout << s[i];
    }

    return 0;
}
