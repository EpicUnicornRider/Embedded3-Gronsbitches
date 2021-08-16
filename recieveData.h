#include <cstdio>
#include <string>

std::string        sendType;
std::string        placeholder;

float              roomTemp;
float              roomHumid;

bool               alarmClient  = 0;
bool               alarm        = 0;
bool               armed        = 0;
bool               lightbulb    = 0;
bool               window       = 0;
bool               getSound     = 0;

int                sound;

/**
 * @brief   Get data gets and seperates the data
 *
 * @note    The data i am send gets analised and saved if it needs to
 *
 * @author  Kasper Grøn Madsen
 *
 * @date    16/08/2021
 **/

void getData(char* url){
  //char to seperate url
  char * SepURL;
  //strtok separets the url into different tokens and removes spaces and /
  SepURL = strtok (url," /");
  while (SepURL != NULL)
  {
    //check if temperature and if it is converts and saves the data as a float
    if(sendType == "TEMP"){
        roomTemp=atof(SepURL);
        printf("***************\n TEMP recieved: %.1f \n***************\n", roomTemp);
    }
    //check if humidity and if it is converts and saves the data as a float
    else if (sendType == "HUMID") {
        roomHumid=atof(SepURL);
        printf("***************\n HUMID recieved: %.0f \n***************\n", roomHumid);
    }
    //checks if light is on or off
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
    //checks if  alarm is on or off
    else if(sendType == "ALARM"){
        //Only alarmclient sends armed or alarm so we save the info that the alarmclient is connected now
        alarmClient = true;
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
    //checks if armed is on or off
    else if(sendType == "ARMED"){
        //Only alarmclient sends armed or alarm so we save the info that the alarmclient is connected now
        alarmClient = true;
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
    //checks if window is open or closed
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
    //get the request the alarmclient wants the sound
    else if(sendType == "GETSOUND"){
        getSound = true;
        printf("***************\n Get Sound Request\n***************\n"); 
        
    }
    //check if sound and if it is converts and saves the data as a int
    else if(sendType == "SOUND"){
        sound = atof(SepURL);      
        printf("***************\n Sound recieved: %i \n***************\n", sound);
    }

    //saves the current sendtype so it will be checked in the next loop
    sendType = SepURL;

    //printf ("%s\n",SepURL);
    SepURL = strtok (NULL, " /");
  }
  //resets the sendtype
  sendType = "BLANK";
}