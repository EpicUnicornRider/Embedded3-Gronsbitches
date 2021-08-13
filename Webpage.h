#include "connection.h"


const int   OFF = 0;
const int   ON  = 1;

char* showWebPage()
{
    
    char        roomTempStr[10] = { };
    char        roomHumidStr[10] = { };
 
    //roomTemp = ds1820.read();

    sprintf(roomTempStr, "%3.1f", roomTemp);
    sprintf(roomHumidStr, "%3.0f", roomHumid);
    memset(httpBuf, 0, sizeof(httpBuf));

    /*$off*/
    strcat
    (
        httpBuf,
        "<head>"
            "<meta charset=\"utf-8\">"
            "<meta name=\"viewport\" content=\" initial-scale=1.0; maximum-scale=1.0; minimum-scale=1.0; user-scalable=0;\"/>"
            "<title>Grøns Cannabis Farm</title>"
            "<link href='http://fonts.googleapis.com/css?family=Droid+Sans&v1' rel='stylesheet' type='text/css'>"
            "<style>"
            ".switch {"
                "position: relative;"
                "display: inline-block;"
                "width: 60px;"
                "height: 34px;"
            "}"
            ".switch input {display:none;}"
            ".slider {"
                "position: absolute;"
                "cursor: pointer;"
                "top: 0;"
                "left: 0;"
                "right: 0;"
                "bottom: 0;"
                "border-radius: 34px;"
                "background-color: #ccc;"
                "-webkit-transition: .4s;"
                "transition: .4s;"
            "}"
            ".slider:before {"
                "position: absolute;"
                "content: \"\";"
                "height: 26px;"
                "width: 26px;"
                "left: 4px;"
                "bottom: 4px;"
                "border-radius: 50%;"
                "background-color: white;"
                "-webkit-transition: .4s;"
                "transition: .4s;"
            "}"
            "input:checked + .slider {"
                "background-color: #8ce196;"
            "}"
            "input:focus + .slider {"
                "box-shadow: 0 0 1px #8ce196;"
            "}"
            "input:checked + .slider:before {"
                "-webkit-transform: translateX(26px);"
                "-ms-transform: translateX(26px);"
                "transform: translateX(26px);"
            "}"
            "</style>"
        "</head>"

        "<body>"
            "<h2><a href=\".\" title=\"Click to refresh the page\">Grøns Cannabis Farm</a></h2>"
            "<pre>Temperature:\t"
    );
    strcat(httpBuf, roomTempStr);
    strcat(httpBuf, "&deg;C</pre>");

    strcat
    (
       httpBuf,
       "<pre>Humidity:\t"
    );
    strcat(httpBuf, roomHumidStr);
    strcat(httpBuf, "%</pre>");

    strcat
    (
       httpBuf,
       "<pre>Drivhus lys:\t"
    );
    if(lightbulb == ON) {
       strcat
       (
           httpBuf,
           " Tændt"
       );
    }
    else {
       strcat
       (
           httpBuf,
           " Slukket"
       );
    }
    strcat
    (
       httpBuf,
           "</pre>"
    );

    strcat
    (
       httpBuf,
       "<pre>Vindue:\t"
    );
    if(window == ON) {
       strcat
       (
           httpBuf,
           " Åbent"
       );
    }
    else {
       strcat
       (
           httpBuf,
           " Lukket"
       );
    }
    strcat
    (
       httpBuf,
           "</pre>"
    );

    strcat
    (
       httpBuf,
       "<pre>Alarm armeret:\t"
    );
    if(armed == ON) {
       strcat
       (
           httpBuf,
           "<a class=\"switch\"> "
           "<input type=\"checkbox\" checked>"
       );
    }
    else {
       strcat
       (
           httpBuf,
           "<a class=\"switch\"> "
           "<input type=\"checkbox\">"
       );
    }
    strcat
    (
       httpBuf,
           "<div class=\"slider\"></div>"
           "</pre>"
           "</a>"
    );

    strcat
    (
       httpBuf,
       "<pre>Alarm Igang:\t"
    );
    if(alarm == ON) {
       strcat
       (
           httpBuf,
           "<a class=\"switch\"> "
           "<input type=\"checkbox\" checked>"
       );
    }
    else {
       strcat
       (
           httpBuf,
           "<a class=\"switch\"> "
           "<input type=\"checkbox\">"
       );
    }
    strcat
    (
       httpBuf,
           "<div class=\"slider\"></div>"
           "</a>"
           "</pre>"
           "<hr>"
           "<pre>2021 Grøns Bitches</pre>"
       "</body>"
    );
    /*$on*/
    return httpBuf;
}