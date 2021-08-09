#include "Webpage.h"

DigitalOut          output(LED1);

void clientCon(){
    //listening for http GET request
        client = server.accept();
        if (client) {
            client->getpeername(&addr);
            printf("Connection succeeded!\n\rIP: %s\n\r", addr.get_ip_address());
            printf("Output: %s\n\r", output);
            client->recv(httpBuf, 1500);
            if (strncmp(httpBuf, "GET", 3) != 0) {
                strcpy(httpHeader, "HTTP/1.0 200 OK top");
                strcpy(httpBuf, "<h1>200 OK</h1>");
                sendHTTP(client, httpHeader, httpBuf);
            }
            else
            if ((strncmp(httpBuf, "GET", 3) == 0) && (strncmp(httpBuf + 3, " / ", 3 == 0))) {
                strcpy(httpHeader, "HTTP/1.0 200 OK buttom");
                strcpy(httpBuf, "<p>Usage: http://host_or_ip/password</p>\r\n");
                sendHTTP(client, httpHeader, httpBuf);
            }
            else {
                int cmd = analyseURL(httpBuf);
                switch (cmd) {
                    case -3:
                        // update webpage
                        strcpy(httpHeader, "HTTP/1.0 200 OK -3");
                        sendHTTP(client, httpHeader, showWebPage(output));
                        break;

                    case -2:
                        // redirect to the right base url
                        strcpy(httpHeader, "HTTP/1.0 301 Moved Permanently\r\nLocation: ");
                        sendHTTP(client, httpHeader, movedPermanently(1));
                        break;

                    case -1:
                        strcpy(httpHeader, "HTTP/1.0 401 Unauthorized");
                        strcpy(httpBuf, "<h1>401 Unauthorized</h1>");
                        sendHTTP(client, httpHeader, httpBuf);
                        break;

                    case 0:
                        output = OFF;   // output off
                        strcpy(httpHeader, "HTTP/1.0 200 OK 0");
                        sendHTTP(client, httpHeader, showWebPage(output));
                        break;

                    case 1:
                        output = ON;    // output on
                        strcpy(httpHeader, "HTTP/1.0 200 OK 1");
                        sendHTTP(client, httpHeader, showWebPage(output));
                        break;
                }
            }
            client->close();
        }   
}




