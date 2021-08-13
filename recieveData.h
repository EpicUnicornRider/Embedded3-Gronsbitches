#include <cstdio>
#include <string>


std::string        sendType;
std::string        placeholder;

float              roomTemp;
float              roomHumid;
float              lightLevel;

bool               alarm        = 0;
bool               armed        = 0;
bool               lightbulb    = 0;
bool               window       = 0;

int                sound        = 0;

void getData(char* url){
  char * SepURL;
  SepURL = strtok (url," /");
  while (SepURL != NULL)
  {
    if(sendType == "TEMP"){
        roomTemp=atof(SepURL);
        printf("***************\n TEMP recieved: %.1f \n***************\n", roomTemp);
    }
    else if (sendType == "HUMID") {
        roomHumid=atof(SepURL);
        printf("***************\n HUMID recieved: %.0f \n***************\n", roomHumid);
    }
    else if(sendType == "LIGHTLVL"){
        lightLevel=atof(SepURL);
        printf("***************\n LIGHTLEVEL recieved: %.1f \n***************\n", lightLevel);
    }
    else if(sendType == "LIGHTSTATUS"){
        placeholder = SepURL;
        if(placeholder == "1"){
            lightbulb = true;
        }
        else if (placeholder == "0") {
            lightbulb = false;
        }
        printf("***************\n Lightbulb status: %i \n***************\n", lightbulb);
    }
    else if(sendType == "ALARM"){
        placeholder = SepURL;
        if(placeholder == "1"){
            alarm = true;
            printf("***************\n Alarm on \n***************\n");
        }
        else if (placeholder == "0") {
            alarm = false;
            printf("***************\n Alarm off \n***************\n");
        }
    }
    else if(sendType == "ARMED"){
        placeholder = SepURL;
        if(placeholder == "1"){
            armed = true;
            printf("***************\n Alarm is armed \n***************\n");
        }
        else if (placeholder == "0") {
            armed = false;
            printf("***************\n Alarm is disarmed \n***************\n");
        }
    }
    else if(sendType == "WINDOW"){
        placeholder = SepURL;
        if(placeholder == "1"){
            window = true;
            
        }
        else if (placeholder == "0") {
            window = false;
        }       
        printf("***************\n Window status: %i \n***************\n", window); 
        
    }
    else if(sendType == "SOUND"){
        sound=atof(SepURL);
        printf("***************\n Sound recieved: %i \n***************\n", sound);
    }

    sendType = SepURL;

    //printf ("%s\n",SepURL);
    SepURL = strtok (NULL, " /");
  }
  sendType = "BLANK";
}