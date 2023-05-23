#include "packet.h"

unsigned char calcParity(struct packet_t *packet)
{
    unsigned char paridade = 0;
    unsigned char *ptr = (unsigned char *)packet;
    for(int i = 0; i < packet->tamanho; i++)
    {
        paridade ^= *ptr;
        ptr++;
    }
    return paridade;
}

void initPacket(struct packet_t *packet, unsigned int tipo, unsigned int sequencia, unsigned char *dados, unsigned int tamanho)
{
    // Inicializa dados como 0
    memset(packet->dados, 0, MAX_DADOS);

    packet->marcador_inicio = 0x7E;
    packet->tamanho = tamanho;
    packet->sequencia = sequencia;
    packet->tipo = tipo;
    memcpy(packet->dados, dados, tamanho);
    packet->paridade = calcParity(packet);
}

void printPacket(struct packet_t *packet)
{
    printf("Marcador de inicio: %c\n", packet->marcador_inicio);
    printf("Tamanho: %d\n", packet->tamanho);
    printf("Sequencia: %d\n", packet->sequencia);
    printf("Tipo: %d\n", packet->tipo);
    printf("Dados: %s\n", packet->dados);
    printf("Paridade: %d\n", packet->paridade);
}

void sendPacket(int socket, struct packet_t *packet)
{
    int bytesSent = 0;
    // Send packet to socket
    bytesSent = write(socket, packet, MAX_PACKET);
    // Verify if all bytes were sent
    if(bytesSent != MAX_PACKET)
    {
        printf("Error sending packet\n");
    }
}

struct packet_t *receivePacket(int socket)
{
    // Allocate pointer based on max value of packet_t
    unsigned char *ptr = (unsigned char *)malloc(MAX_PACKET);

    int bytesRead = 0;
    struct packet_t *packet;
    // Receive packet from socket
    bytesRead = read(socket, ptr, MAX_PACKET);
    // Verify if all bytes were received
    if(bytesRead != MAX_PACKET)
    {
        printf("Error receiving packet\n");
    }
    // Check if packet is valid
    if(ptr[0] == '~')
    {
        // Allocate packet
        packet = (struct packet_t *)malloc(sizeof(struct packet_t));
        // Memcopy ptr to packet
        memcpy(packet, ptr, MAX_PACKET);

        if(calcParity(packet) != packet->paridade)
        {
            printf("Parity error\n");
        }
        else
        {
            printPacket(packet);
            exit(1);
        }
    }
    return NULL;
}