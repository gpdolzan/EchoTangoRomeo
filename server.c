#include "ConexaoRawSocket.h"
#include "server.h"
#include "packet.h"

int soquete_server;

void runServer()
{
    soquete_server = ConexaoRawSocket("lo");
    while(1)
    {
        // Using receivePacket then print packet
        struct packet_t *pkt = NULL;
        pkt = receivePacket(soquete_server);
        if(pkt != NULL)
        {
            exit(1);
        }
    }
}