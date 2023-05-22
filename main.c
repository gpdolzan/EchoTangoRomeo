#include "trfiles.h"
#include "client.h"
#include "servidor.h"

int main(int argc, char const *argv[])
{
    if(argc == 1)
    {
        printf("Por favor, inicie o client ou server!\n");
        printf("\tPara iniciar o client, rode 'sudo ./main client'\n");
        printf("\tPara iniciar o server, rode 'sudo ./main server'\n");
    }
    else if (argc > 1)
    {
        if(strcmp(argv[1], "client") == 0)
        {
            printf("Cliente iniciando\n");
            runClient();
        }
        else if(strcmp(argv[1], "server") == 0)
        {
            printf("Servidor iniciando\n");
            runServer();
        }
        else
            printf("Argumento invalido\n");
    }
    return 0;
}