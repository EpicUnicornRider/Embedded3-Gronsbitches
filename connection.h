#include "EthernetInterface.h"
#include "TCPSocket.h"
#include "mbed.h"
#include <string>
#include "screen.h"
#include <stdio.h>

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

/**
 * @brief   Analyses the received URL
 * @note    The string passed to this function will look like this:
 *          GET /password HTTP/1.....
 *          GET /password/ HTTP/1.....
 *          GET /password/?sw=1 HTTP/1.....
 *          GET /password/?sw=0 HTTP/1.....
 * @param   url URL string
 * @retval -1 invalid password
 *         -2 no command given but password valid
 *         -3 just refresh page
 *          0 switch off
 *          1 switch on
 */
SocketAddress   addr;
void ipAdress(){
    net->get_ip_address(&addr);
    printf("IP address: %s\n", addr.get_ip_address() ? addr.get_ip_address() : "None");
    net->get_netmask(&addr);
    printf("Netmask: %s\n", addr.get_ip_address() ? addr.get_ip_address() : "None");
    net->get_gateway(&addr);
    printf("Gateway: %s\n", addr.get_ip_address() ? addr.get_ip_address() : "None");
}
    

int8_t analyseURL(char* url)
{
    
    printf("%s\n", url);

    if (strlen(url) < (5 + strlen(PASSWORD) + 1))
        return(-1);

    //if (url.substr(5, PASSWORD.size()) != PASSWORD)
    if (strncmp(url + 5, PASSWORD, strlen(PASSWORD)) != 0)
        return(-1);

    uint8_t pos = 5 + strlen(PASSWORD);

    //if (url.substr(pos, 1) != "/")

    if (*(url + pos) != '/')
        return(-1);

    //if (url.substr(pos++, 1) == " ")
    if (*(url + pos++) == ' ')
        return(-2);



    //string  cmd(url.substr(pos, 5));
    *(url + pos + 5) = '\0';    // terminate the cmd string
    char*   cmd = ((url + pos));
    if (strcmp(cmd, "?sw=0") == 0)
        return(0);
    if (strcmp(cmd, "?sw=1") == 0)
        return(1);
    if (strcmp(cmd, "?sw=2") == 0)
        return (2);
    return(-3);
}

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
    memmove(httpBuf + strlen(header), httpBuf, strlen(content));    // make room for the header
    strcpy(httpBuf, header);                                        // copy the header on front of the content
    httpBuf[strlen(header)] = c;
    client->send((uint8_t*)httpBuf, strlen(httpBuf));
}

void serverCon(){
    /* Open the server on ethernet stack */
    server.open(net);

    /* Bind the HTTP port (TCP 80) to the server */
    server.bind(PORT);

    /* Listen for clients */
    server.listen();
    
}

void start(EthernetInterface*  net){
    
    // Show the network address
    ipAdress();

    serverCon();
    
    printf("\r\n Starting \r\n");

    startup();
    
    printf("=========================================\r\n");
    printf("Ready to serve clients.\r\n");
    net->get_ip_address(&addr);
    printf("Usage: Type http:\/\/%s\/%s\/  into your web browser and hit ENTER\r\n", addr.get_ip_address(), PASSWORD);
    
    Dannebrog();
    
}

