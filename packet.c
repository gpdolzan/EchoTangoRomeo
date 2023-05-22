#include "packet.h"

u_packet_t* createPacket(unsigned int tamanho, unsigned int sequencia, unsigned int tipo, unsigned char *dados)
{
    u_packet_t* pacote = (u_packet_t*)malloc(sizeof(u_packet_t));

    // Inicializa dados como 0
    memset(pacote->packet.dados, 0, MAX_DADOS);

    pacote->packet.marcador_inicio = 0x7E;
    pacote->packet.tamanho = tamanho;
    pacote->packet.sequencia = sequencia;
    pacote->packet.tipo = tipo;

    if(dados != NULL)
    {
        memcpy(pacote->packet.dados, dados, tamanho);
    }

    // Parity to all bytes in data
    for(int i = 0; i < pacote->packet.tamanho; i++)
    {
        pacote->packet.paridade ^= pacote->packet.dados[i];
    }
    pacote->packet.paridade ^= pacote->packet.tamanho ^ pacote->packet.sequencia ^ pacote->packet.tipo;

    printf("Buffer: ");
    for(int i = 0; i < MAX_PACKET; i++)
    {
        printf("%d ", pacote->bytes[i]);
    }
    printf("\n");

    return pacote;
}

void printPacket(u_packet_t *packet)
{
    printf("Marcador de inicio: %c\n", packet->packet.marcador_inicio);
    printf("Tamanho: %d\n", packet->packet.tamanho);
    printf("Sequencia: %d\n", packet->packet.sequencia);
    printf("Tipo: %d\n", packet->packet.tipo);
    printf("Dados: %s\n", packet->packet.dados);
    printf("Paridade: %d\n", packet->packet.paridade);
}

void sendPacket(u_packet_t *packet, int socket)
{
    unsigned int packetSize = sizeof(u_packet_t);
    write(socket, &packet->packet, packetSize);
}

u_packet_t* receivePacket(int socket)
{
    // Buffer com tamanho maximo que um pacote pode ter
    unsigned char buffer[MAX_PACKET];
    unsigned char dados[MAX_DADOS + 1];
    int paridade = 0;
    
    // Aloca pacote
    u_packet_t* packet = (u_packet_t*) malloc(sizeof(u_packet_t));

    // Usando ConexaoRawSocket, recebe pacote
    read(socket, buffer, MAX_PACKET);

    printf("Buffer: ");
    for(int i = 0; i < MAX_PACKET; i++)
    {
        printf("%d ", packet->bytes[i]);
    }
    printf("\n");

    // Verifica marcador de inicio para validar pacote
    if(buffer[0] == 0x7E)
    {
        packet->packet.marcador_inicio = buffer[0];

        packet->packet.tamanho = buffer[1];
        packet->packet.sequencia = buffer[2];
        packet->packet.tipo = buffer[3];

        // Copia dados do buffer para o pacote usando memcpy
        memcpy(packet->packet.dados, buffer + 4, 63);
        memcpy(dados, buffer + 4, 63);
        dados[64] = '\0';
        
        printf("%s\n", packet->packet.dados);
        printf("%s\n", dados);

        // Pega paridade do pacote
        packet->packet.paridade = buffer[67];

        // Calcula paridade
        // Parity to all bytes in data
        for(int i = 0; i < packet->packet.tamanho; i++)
        {
            paridade ^= packet->packet.dados[i];
        }
        paridade ^= packet->packet.tamanho ^ packet->packet.sequencia ^ packet->packet.tipo;

        if(packet->packet.paridade == paridade)
        {
            return packet;
        }
        else
        {
            // Erro de paridade, manda erro e espera resposta TO DO
            return NULL;
        }
    }
    return NULL;
}