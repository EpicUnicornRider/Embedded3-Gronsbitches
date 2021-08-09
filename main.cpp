#include "Client.h"

using namespace std;

int main(void)
{
    
    //ethLed.start(eth_led);
    //net = NetworkInterface::get_default_instance();
    net = new EthernetInterface();

    net->set_network(IP, NETMASK, GATEWAY);  // use static IP address, netmask, gateway
    if (!net) {
        printf("Error! No network inteface found.\n");
        return 0;
    }

    //net->set_network (IP, NETMASK, GATEWAY);  // include this for using static IP address
    nsapi_size_or_error_t   r = net->connect();
    if (r != NSAPI_ERROR_OK) {
        printf("Error! net->connect() returned: %d\n", r);
        return r;
    }

    start(net);
    
    while (true) {
        clientCon();    

    }
}
