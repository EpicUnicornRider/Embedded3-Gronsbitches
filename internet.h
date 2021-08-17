/**
*   @file internet.h
*   @brief This file exposes the internet function.
*
*   @author Oliver P. Hartvigsen.
*   
*   @date 2021-08-17
*/

#ifndef INTERNET_H
#define INTERNET_H

#include <string>

std::string internet(char ip[], int port, std::string txtsend);

void closeconnection();

#endif /*INTERNET_H*/