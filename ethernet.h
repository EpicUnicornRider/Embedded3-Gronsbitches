#include "mbed.h"
#include <stdio.h>
#include "EthernetInterface.h"
#include "LCD_DISCO_F746NG.h"
//EthernetInterface net;
 
void internet () {
EthernetInterface net;

BSP_LCD_Clear(LCD_COLOR_BLUE);
BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
wait_us(300);
BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"Connecting to internet...", CENTER_MODE);
wait_us(1000000);
 
printf("Ethernet socket example\n");
    net.connect();
 
    // Show the network address
    SocketAddress a;
    net.get_ip_address(&a);
 
    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
 
    // Open a socket on the network interface, and create a TCP connection to mbed.org
    TCPSocket socket;
    socket.open(&net);
 
    //net.gethostbyname("ifconfig.io", &a);
    a.set_ip_address("10.130.52.204");
    a.set_port(80);
 
    socket.connect(a);
    // Send a simple http request
    char sbuffer[] = "GET /GronCan/?sw=1 / HTTP/1.1\r\n HOST: 10.130.52.60\r\n\r\n";
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
    printf("Done\n");
  
}