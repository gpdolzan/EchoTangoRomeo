#include "packet.h"
#include "fileManager.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

packet_t* createPacket(unsigned char tamanho, unsigned char sequencia, unsigned char tipo, unsigned char* dados)
{
    packet_t* packet = (packet_t*) malloc(sizeof(packet_t));
    packet->marcador_inicio = 0x7E;
    packet->tamanho = tamanho;
    packet->sequencia = sequencia;
    packet->tipo = tipo;

    // Coloca todos os valores de dados dentro do pacote como sendo 1 usando memset
    memset(packet->dados, 65, MAX_DADOS);

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
    unsigned char dados[MAX_DADOS + 1];
    int paridade = 0;
    
    // Aloca pacote
    packet_t* packet = (packet_t*) malloc(sizeof(packet_t));

    // Usando ConexaoRawSocket, recebe pacote
    read(socket, buffer, MAX_PACKET);

    // Verifica marcador de inicio para validar pacote
    if(buffer[0] == 0x7E)
    {
        packet->marcador_inicio = buffer[0];

        packet->tamanho = buffer[1];
        packet->sequencia = buffer[2];
        packet->tipo = buffer[3];

        // Copia dados do buffer para o pacote usando memcpy
        memcpy(packet->dados, buffer + 4, 63);
        memcpy(dados, buffer + 4, 63);
        dados[64] = '\0';
        
        printf("%s\n", packet->dados);
        printf("%s\n", dados);

        // Pega paridade do pacote
        packet->paridade = buffer[67];

        // Calcula paridade
        paridade = packet->tamanho ^ packet->sequencia ^ packet->tipo;

        if(packet->paridade == paridade)
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

/*void printTipoPacote(unsigned char tipo)
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
}*/

void printPacket(packet_t* packet)
{
    printf("Marcador de inicio: %d\n", packet->marcador_inicio);
    printf("Tamanho do pacote: %d\n", packet->tamanho);
    printf("Sequencia do pacote: %d\n", packet->sequencia);
    printf("Tipo do pacote: %d\n", packet->tipo);
    //printTipoPacote(packet->tipo);
    printf("Paridade do pacote: %d\n", (int)packet->paridade);
    printf("Dados do pacote: %s\n", packet->dados);
}

void processPacket(packet_t* packet)
{
    if(packet->tipo == BACKUP_ARQ)
    {
        // Recebeu nome do arquivo nos dados, usar isso para criar arquivo
        FILE* file = createFile(packet->dados);


    }
}