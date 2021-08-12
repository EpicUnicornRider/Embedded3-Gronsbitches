#include <cstdio>
#include <ostream>
#include <iostream>
#include <string>


std::string        sendType;
std::string        placeholder;

float              roomTemp;
float              roomHumid;

bool               alarm;
bool               armed;
bool               lightbulb;
bool               window;

void getData(char* url){
  char * pch;
  char * compare_c = "0";
  printf ("%s", url);
  pch = strtok (url," /");
  while (pch != NULL)
  {
    if(sendType == "TEMP"){
        roomTemp=atof(pch);
        printf("**********\n TEMP recieved: %.1f \n************\n", roomTemp);
    }
    else if (sendType == "HUMID") {
        roomHumid=atof(pch);
        printf("**********\n HUMID recieved: %.1f \n************\n", roomHumid);
    }
    else if(sendType == "LIGHTLVL"){
        
    }
    else if(sendType == "LIGHTSTATUS"){
        placeholder = pch;
        if(placeholder == "true"){
            lightbulb = true;
        }
        else if (placeholder == "false") {
            lightbulb = false;
        }
        
    }
    else if(sendType == "ALARM"){
        placeholder = pch;
        if(placeholder == "true"){
            alarm = true;
            printf("Alarm on\n");
        }
        else if (placeholder == "false") {
            alarm = false;
            printf("Alarm off\n");
        }
    }
    else if(sendType == "ARMED"){
        placeholder = pch;
        if(placeholder == "true"){
            armed = true;
        }
        else if (placeholder == "false") {
            armed = false;
        }
    }
    else if(sendType == "WINDOW"){
        placeholder = pch;
        if(placeholder == "true"){
            window = true;
        }
        else if (placeholder == "false") {
            window = false;
        }        
    }

    sendType = pch;

    printf ("%s\n",pch);
    pch = strtok (NULL, " /");
  }
  sendType = "BLANK";
}