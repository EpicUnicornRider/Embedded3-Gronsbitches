#ifndef ETHERNETCOMMUNICATION_H
#define ETHERNETCOMMUNICATION_H

#include <string>

void alarmtriggered();
void alarmstopped();
void alarmarmed();
void alarmunarmed();
std::string getsoundstatus();

#endif /*ETHERNETCOMMUNICATION_H*/