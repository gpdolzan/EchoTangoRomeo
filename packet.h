#ifndef __PACKET_H__
#define __PACKET_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/* Definicao dos possiveis tipos */
#define BACKUP_ARQ     0000
#define BACKUP_ARQS    0001
#define RECUPERA_ARQ   0010
#define RECUPERA_ARQS  0011
#define DEF_DIR_SERVER 0100
#define VERIFICA_BKUP  0101
#define ARQ_NAME_REC   0110
#define MD5_ARQ        0111
#define DADOS_ARQ      1000
#define FIM_ARQ        1001
#define FIM_ARQS       1010
// 1011 NADA
#define ERROR          1100
#define OK             1101
#define ACK            1110
#define NACK           1111

/* Definicoes sobre pacote */
#define MAX_PACKET 68
#define MAX_DADOS 63

typedef struct packet_t
{
    unsigned char marcador_inicio;
    unsigned char tamanho : 6;
    unsigned char sequencia : 6;
    unsigned char tipo : 4;
    unsigned char dados[63];
    unsigned char paridade;
}packet_t;

// Union [68 bytes ambos]
typedef union u_packet_t
{
    packet_t packet;
    unsigned char bytes[MAX_PACKET];
}u_packet_t;

// Function that creates a u_packet_t
u_packet_t* createPacket(unsigned int tamanho, unsigned int sequencia, unsigned int tipo, unsigned char *dados);

// Function that prints a packet
void printPacket(u_packet_t *packet);

// Function that sends packet
void sendPacket(u_packet_t *packet, int socket);

// Function that receives packet
u_packet_t* receivePacket(int socket);

#endif