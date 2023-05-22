#include "servidor.h"
#include "packet.h"
#include "ConexaoRawSocket.h"

int soquete_server;

void runServer()
{
    soquete_server = ConexaoRawSocket("eno1"); // Servidor
    u_packet_t* pacote_ack = createPacket(0, 0, ACK, NULL);
    int i = 1, lastSeq = 0;

    while(i)
    {
        // Receive packet
        u_packet_t* pacoteRecebido = receivePacket(soquete_server);
        if(pacoteRecebido != NULL)
        {
            printf("aqui\n");
            printPacket(pacoteRecebido);
            lastSeq = pacoteRecebido->packet.sequencia;
            free(pacoteRecebido);
            while(1)
            {
                // Send pacote_ack
                sendPacket(pacote_ack, soquete_server);
            }
        }
    }
}