#include "packet.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

packet_t* createPacket(unsigned char tamanho, unsigned char sequencia, unsigned char tipo, unsigned char* dados)
{
    packet_t* packet = (packet_t*) malloc(sizeof(packet_t));
    packet->tamanho = tamanho;
    packet->sequencia = sequencia;
    packet->tipo = tipo;
    
    // aloca dados com base no tamanho
    packet->dados = (unsigned char*) malloc(tamanho);

    // Paridade eh um xor de tamanho sequencia e tipo
    packet->paridade = tamanho ^ sequencia ^ tipo;

    return packet;
}

void sendPacket(packet_t* packet, int socket)
{
    unsigned int packetSize = sizeof(packet_t) + packet->tamanho;

    // Usando ConexaoRawSocket, envia pacote
    write(socket, packet, packetSize);
}

packet_t* receivePacket(int socket)
{
    // Buffer com tamanho maximo que um pacote pode ter
    unsigned char buffer[MAX_PACKET];
    unsigned char* dados;
    int lastCount = 0;
    
    // Aloca pacote
    packet_t* packet = (packet_t*) malloc(sizeof(packet_t));

    // Usando ConexaoRawSocket, recebe pacote
    read(socket, buffer, MAX_PACKET);

    // Verifica marcador de inicio para validar pacote
    if(buffer[0] == 0x7E)
    {
        packet->marcador_inicio = buffer[0];
        printf("Recebi um pacote, verificando seu conteudo\n");

        packet->tamanho = buffer[1];
        printf("Tamanho do pacote: %d\n", packet->tamanho);
        packet->sequencia = buffer[2];
        printf("Sequencia do pacote: %d\n", packet->sequencia);
        packet->tipo = buffer[3];
        printTipoPacote(packet->tipo);

        // Usando tamanho, use um for para ler somente o tamanho de dados
        dados = (unsigned char*) malloc(packet->tamanho);
        for(int i = 4; i < packet->tamanho + 4; i++)
        {
            dados[i - 4] = buffer[i];
            lastCount = i;
        }
        packet->dados = dados;
        printf("Dados do pacote: %s\n", packet->dados);
        lastCount++;

        // Pega paridade do pacote
        packet->paridade = buffer[lastCount];
        printf("Paridade do pacote: %d\n", (int)packet->paridade);
        
        return packet;
    }
    return NULL;
}

void printTipoPacote(unsigned char tipo)
{
    // Switch contendo todos os tipos dentro de Packet.h e um printf que imprime o tipo do pacote
    switch (tipo)
    {
        case 0x00:
            printf("Tipo do pacote: BACKUP_ARQ\n");
            break;
        case 0x01:
            printf("Tipo do pacote: BACKUP_ARQS\n");
            break;
        case 0x02:
            printf("Tipo do pacote: RECUPERA_ARQ\n");
            break;
        case 0x03:
            printf("Tipo do pacote: RECUPERA_ARQS\n");
            break;
        case 0x04:
            printf("Tipo do pacote: DEF_DIR_SERVER\n");
            break;
        case 0x05:
            printf("Tipo do pacote: VERIFICA_BKUP\n");
            break;
        case 0x06:
            printf("Tipo do pacote: ARQ_NAME_REC\n");
            break;
        case 0x07:
            printf("Tipo do pacote: MD5_ARQ\n");
            break;
        case 0x08:
            printf("Tipo do pacote: DADOS_ARQ\n");
            break;
        case 0x09:
            printf("Tipo do pacote: FIM_ARQ\n");
            break;
        case 0x0A:
            printf("Tipo do pacote: FIM_ARQS\n");
            break;
        case 0x0B:
            printf("Tipo do pacote: NULL\n");
            break;
        case 0x0C:
            printf("Tipo do pacote: ERROR\n");
            break;
        case 0x0D:
            printf("Tipo do pacote: OK\n");
            break;
        case 0x0E:
            printf("Tipo do pacote: ACK\n");
            break;
        case 0x0F:
            printf("Tipo do pacote: NACK\n");
            break;
        default:
            printf("Tipo do pacote: INVALIDO\n");
            break;
    }
}