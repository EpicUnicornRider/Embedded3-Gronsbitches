#include "EthernetInterface.h"
#include "TCPSocket.h"
#include "mbed.h"
#include <string>
#include "screen.h"
#include <stdio.h>
#include "recieveData.h"

#define IP      "10.130.52.204"
#define GATEWAY "10.130.52.1"
#define NETMASK "255.255.254.0"

#define PORT    80
/* */
EthernetInterface*  net;
TCPSocket           server;
TCPSocket*          client;
const char          PASSWORD[] = "GronCan";
char                httpBuf[1500];
char                httpHeader[256];

char                newTemp[100];

SocketAddress   addr;
void ipAdress(){
    net->get_ip_address(&addr);
    printf("IP address: %s\n", addr.get_ip_address() ? addr.get_ip_address() : "None");
    net->get_netmask(&addr);
    printf("Netmask: %s\n", addr.get_ip_address() ? addr.get_ip_address() : "None");
    net->get_gateway(&addr);
    printf("Gateway: %s\n", addr.get_ip_address() ? addr.get_ip_address() : "None");
}

/**
 * @brief   Analyses the received URL
 * @retval -1 invalid password
 *         -2 no command given but password valid
 *         -3 just refresh page
 */

int8_t analyseURL(char* url)
{
    //return -1 if not long enough for password
    if (strlen(url) < (5 + strlen(PASSWORD) + 1))
        return(-1);

    //return -1 if not password
    if (strncmp(url + 5, PASSWORD, strlen(PASSWORD)) != 0)
        return(-1);

    //return -1 if not long enough for password
    uint8_t pos = 5 + strlen(PASSWORD);

    //return -1 if password not followed by a /
    if (*(url + pos) != '/')
        return(-1);

    //return -2 if its moved
    if (*(url + pos++) == ' ')
        return(-2);

    //run getData function
    getData(url);

    //if sound is requested and its the alarmclient that wants it return -4
    if(getSound == true && alarmClient == true){
        return (-4);
    }

    //if nothing else return -3
    return(-3);
}

/**
 * @brief   If the page that has been looked for isnt found it will send them somewhere else
 *
 * @author  Kasper Grøn Madsen
 *
 * @date    16/08/2021
 **/

char* movedPermanently(uint8_t flag)
{
    memset(httpBuf, 0, sizeof(httpBuf));
    if (flag == 1) {
        strcpy(httpBuf, "/");
        strcat(httpBuf, PASSWORD);
        strcat(httpBuf, "/");
    }

    strcat(httpBuf, "<h1>301 Moved Permanently</h1>\r\n");
    return(httpBuf);
}


/**
 * @brief   Send http back to client
 *
 * @author  Kasper Grøn Madsen
 *
 * @date    16/08/2021
 **/

void sendHTTP(TCPSocket* client, char* header, char* content)
{
    char    content_length[10] = { };
    sprintf(content_length, "%u\r\n", strlen(content));
    strcat(header, "\r\nContent-Type: text/html\r\n");
    strcat(header, "Content-Length: ");
    strcat(header, content_length);
    strcat(header, "Pragma: no-cache\r\n");
    strcat(header, "Connection: About to close\r\n\r\n");

    char    c = content[0];
    //memmove(httpBuf + strlen(header), httpBuf, strlen(content));    // make room for the header
    strcpy(httpBuf, header);                                        // copy the header on front of the content
    httpBuf[strlen(header)] = c;
    client->send((uint8_t*)httpBuf, strlen(httpBuf));
}

/**
 * @brief   overall server connection setup
 *
 * @author  Kasper Grøn Madsen
 *
 * @date    16/08/2021
 **/

void serverCon(){
    /* Open the server on ethernet stack */
    server.open(net);

    /* Bind the HTTP port (TCP 80) to the server */
    server.bind(PORT);

    /* Listen for clients */
    server.listen();
    
}

/**
 * @brief   Startup
 *
 * @note    nearly everything that needs to run at the start of the program
 * @author  Kasper Grøn Madsen
 *
 * @date    16/08/2021
 **/


void start(EthernetInterface*  net){
    
    // Show the network address
    ipAdress();

    serverCon();
    
    printf("\r\n Starting \r\n");

    //Startup on lcd
    startup();
    
    printf("=========================================\r\n");
    printf("Ready to serve clients.\r\n");
    net->get_ip_address(&addr);
    printf("Usage: Type http://%s/%s/  into your web browser and hit ENTER\r\n", addr.get_ip_address(), PASSWORD);
    
    //dannebrog når programmet kører
    Dannebrog();
    
}

