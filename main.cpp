#include "Client.h"
#include <cstdlib>

using namespace std;

int main(void)
{
    //Start the lcd function so things will be shown on the LCD screen
    LCDStart();
    //ethLed.start(eth_led);
    //net = NetworkInterface::get_default_instance();
    net = new EthernetInterface();

    //static IP
    net->set_network(IP, NETMASK, GATEWAY);  // use static IP address, netmask, gateway

    if (!net) {
        printf("Error! No network inteface found.\n");
        return 0;
    }

    nsapi_size_or_error_t   r = net->connect();
    if (r != NSAPI_ERROR_OK) {
        printf("Error! net->connect() returned: %d\n", r);
        return r;
    }

    //startup function
    start(net);

    while (true) {
        
        //clientconnection
        clientCon();    

    }
}
