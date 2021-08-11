#include <ostream>
#include <regex>
#include <stdio.h>
#include <iostream>

std::cmatch match;
char test[] = "dfhdfg \\Karsten\\ dsada";
char test2[100];

void getData(char URL){
    std::regex reg("/[\\](.*)[\\]/g");
    if (regex_search(test, match, reg)){
        std::cout << match[0] << std::endl;
    }
}