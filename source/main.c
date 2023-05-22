#include <stdio.h>
#include <unistd.h>
#include "ConexaoRawSocket.h"
#include "packet.h"

int main(int argc, char const *argv[])
{
    // ConexaoRawSocket("eno1"); // Servidor
    //int socket = ConexaoRawSocket("enp5s0"); // Cliente
    int socket = ConexaoRawSocket("eth0"); // Cliente
    //int socket = ConexaoRawSocket("lo");

    int i = 1;

    // Cria pacote usando Packet.h
    // Cliente
    packet_t* packet = createPacket(10, 1, BACKUP_ARQ, "arq.texto");
    // Servidor
    packet_t* receiverPacket;

    // Send buffer to socket
    while (1)
    {
        // Cliente
        while(i)
        {
            sendPacket(packet, socket);
            scanf("%d", &i);
        }
        // Servidor
        receiverPacket = receivePacket(socket);
        if(receiverPacket != NULL)
        {
            sleep(5);
        }
    }
    return 0;
}