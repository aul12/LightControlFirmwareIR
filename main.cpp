#include "mbed.h"
#include "EthernetInterface.h"
#include "irCommands.h"

const int PORT = 1337;

EthernetInterface eth;          //create ethernet
UDPSocket server;               //creat server
Endpoint client;                //create endpoint

int n;                  //size of received message
char counter[1] = {0};  //sample receive/send buffer

void init_eth(void);    //initializes Ethernet
void receive(void);     //receives packets
int main(void);         //main


void receive(void)
{
    n = server.receiveFrom(client, counter, sizeof(counter));                                   //receive message from client
    if(n>0) {
        command = counter[0];
        state = 0;
    }
}

int main(void)
{
    eth.init();
    eth.connect();
    
    server.bind(PORT);
    server.set_blocking(false, 200);
    
    while (true)    //repeat forever
    {
        receive();  //wait for message
        commandTicker();
    }
}
