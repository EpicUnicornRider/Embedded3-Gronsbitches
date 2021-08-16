#include "Webpage.h"

/**
 * @brief   Client connection
 *
 * @note    Everything that needs to happen when the client connects
 *          return a confirmation.
 *          return data.
 *           unautorized access
 *
 * @author  Kasper Grøn Madsen
 *
 * @date    16/08/2021
 **/

void clientCon(){
    
        client = server.accept();
        if (client) {
        
            client->getpeername(&addr);
            printf("Connection succeeded!\n\rIP: %s\n\r", addr.get_ip_address());
            client->recv(httpBuf, 1500);
            //listening for http GET request
            if (strncmp(httpBuf, "GET", 3) != 0) {
                strcpy(httpHeader, "HTTP/1.0 200 OK top");
                strcpy(httpBuf, "<h1>200 OK</h1>");
                sendHTTP(client, httpHeader, httpBuf);
            }
            else if ((strncmp(httpBuf, "GET", 3) == 0) && (strncmp(httpBuf + 3, " / ", 3) == 0)) {
                strcpy(httpHeader, "HTTP/1.0 200 OK buttom");
                strcpy(httpBuf, "<p>Usage: http://host_or_ip/password</p>\r\n");
                sendHTTP(client, httpHeader, httpBuf);
            }
            else {
                int cmd = analyseURL(httpBuf);
                switch (cmd) {
                    //return sound to
                    case -4:
                        sprintf(httpHeader, "HTTP/1.0 200 OK /SOUND/ %i", sound);
                        sendHTTP(client, httpHeader, httpBuf);
                        sound = false;
                        break;
                    case -3:
                        //default
                        strcpy(httpHeader, "HTTP/1.0 200 OK");
                        sendHTTP(client, httpHeader, showWebPage());
                        break;

                    case -2:
                        // redirect to the right base url
                        strcpy(httpHeader, "HTTP/1.0 301 Moved Permanently\r\nLocation: ");
                        sendHTTP(client, httpHeader, movedPermanently(1));
                        break;

                    case -1:
                    //unautorized access
                        strcpy(httpHeader, "HTTP/1.0 401 Unauthorized");
                        strcpy(httpBuf, "<h1>401 Unauthorized</h1>");
                        sendHTTP(client, httpHeader, httpBuf);
                        break;
                }
            }
            getSound = false;
            alarmClient = false;
            client->close();
        }   
}




