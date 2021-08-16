#include "mbed.h"
#include "EthernetInterface.h"
#include "LCD_DISCO_F746NG.h"
#include "ntp-client/NTPClient.h"
#include <string>
#include <cstring>
#include "light.h"
#include "sound.h"

EthernetInterface net;
SocketAddress a;
TCPSocket socket;
char timenow[50];
char unit_adr[50];

Thread Thread4;
 
void internet () {
    

BSP_LCD_Clear(LCD_COLOR_BLUE);
BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
wait_us(300);
BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"Connecting to internet...", CENTER_MODE);
wait_us(1000000);
 
printf("Connecting to Ethernet...\n");
    net.connect();
 
    // Show the network address
    net.get_ip_address(&a);

    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

    sprintf(unit_adr, "IP Address: %s", a.get_ip_address());
    BSP_LCD_DisplayStringAt(0, LINE(2), (uint8_t *)unit_adr, CENTER_MODE);

    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    // Open a socket on the network interface, and create a TCP connection to mbed.org
    socket.open(&net);
 
    a.set_ip_address("10.130.52.204");
    a.set_port(80);
 
    socket.connect(a);
    // Send a simple http request
    char sbuffer[] = "GET /GronCan/ / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n";
    int scount = socket.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);
 
    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    int rcount = socket.recv(rbuffer, sizeof rbuffer);
    printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
 
    // Close the socket to return its memory and bring down the network interface
    socket.close();
 
    // Bring down the ethernet interface
    net.disconnect();
    printf("Disconnected\n");

  
}

void SensorsInfo()
{
    while(true) {

    bool lightstat;
    net.connect();
     
    // Open a socket on the network interface, and create a TCP connection to mbed.org
    socket.open(&net);
 
    a.set_ip_address("10.130.52.204");
    a.set_port(80);

    // Check if the light value is under a certain value (light/dark)
    if(g < 0.3){
        lightstat = 1;
    }
    else{
        lightstat = 0;
    }
 
    socket.connect(a);
    // Send a simple http request and send light and sound data
    char sbuffer[] = "GET /GronCan/ / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n";
    sprintf(sbuffer, "GET /GronCan/ /LIGHTSTATUS/ %i /SOUND/ %i / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n", lightstat, loudestsound);
    int scount = socket.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);

    loudestsound = 0;
    
    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    int rcount = socket.recv(rbuffer, sizeof rbuffer);
    printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
 
    // Close the socket to return its memory and bring down the network interface
    socket.close();
 
    // Bring down the ethernet interface
    net.disconnect();
    printf("Disconnected\n");
    wait_us(10000000);
    }
}

void Time_thread()
{
    NTPClient ntp(&net);
    time_t timestamp = ntp.get_timestamp();

    timestamp += 2 * 60 * 60;
    set_time(timestamp);

    while(1){
        timestamp = time(NULL);
        string str = ctime(&timestamp);
        printf("%s\n", str.substr(11,8).c_str());
        sprintf(timenow, "Time: %s", str.substr(11,8).c_str()); // Saving a substring to "timenow" containing only the part with the time in the string
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)timenow, CENTER_MODE); //Display current time reading on LCD display
        wait_us(500000);
    }
}