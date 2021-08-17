/**
*   @file ethernetcommunication.h
*   @brief This header file exposes fucntions.
*
*   @author Oliver P. Hartvigsen.
*   
*   @date 2021-08-17
*/

#ifndef ETHERNETCOMMUNICATION_H
#define ETHERNETCOMMUNICATION_H

#include <string>

void alarmtriggered();
void alarmstopped();
void alarmarmed();
void alarmunarmed();
std::string getsoundstatus();

#endif /*ETHERNETCOMMUNICATION_H*/