#ifndef __PACKET_H__
#define __PACKET_H__

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

//funcao que cria pacote com base no seu tipo
packet_t* createPacket(unsigned char tamanho, unsigned char sequencia, unsigned char tipo, unsigned char* dados);

//funcao que envia pacote
void sendPacket(packet_t* packet, int socket);

//funcao que recebe pacote
packet_t* receivePacket(int socket);

//funcao que imprime uma mensagem dependendo do tipo da mensagem
void printTipoPacote(unsigned char tipo);

// funcao que imprime o conteudo do pacote
void printPacket(packet_t* packet);

// funcao que processa o pacote
void processPacket(packet_t* packet);

#endif