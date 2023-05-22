#include "client.h"
#include "packet.h"
#include "ConexaoRawSocket.h"

int soquete;

void runClient()
{
    int soquete = ConexaoRawSocket("enp5s0");
    //printf("Cliente conectado ao soquete\n");
    //soquete = ConexaoRawSocket("lo");
    char command;

    while(1)
    {
        system("clear");
        printf("Tecle 1 se quiser realizar o backup de um arquivo\n");
        printf("Tecle 2 se quiser realizar o backup de um grupo de arquivos\n");
        printf("Tecle 3 se quiser recuperar um arquivo\n");
        printf("Tecle 4 se quiser recuperar um grupo de arquivos\n");
        printf("Tecle 5 se quiser definir o diretorio do servidor\n");
        printf("Tecle 6 se quiser definir o diretorio do cliente\n");
        printf("Tecle 7 se verificar o backup usando MD5 hash\n");
        printf("Tecle 8 se quiser sair\n\n");
        printf("Digite a opcao desejada: ");
        command = getchar();
        
        switch(command)
        {
            case '1':
                menuBackupSingleFile();
                break;
            case '2':
                printf("Realizar backup de um grupo de arquivos\n");
                break;
            case '3':
                printf("Recuperar um arquivo\n");
                break;
            case '4':
                printf("Recuperar um grupo de arquivos\n");
                break;
            case '5':
                printf("Definir diretorio do servidor\n");
                break;
            case '6':
                printf("Definir diretorio do cliente\n");
                break;
            case '7':
                printf("Verificar backup usando MD5 hash\n");
                break;
            case '8':
                exit(1);
                break;
            default:
                printf("Comando invalido\n");
                break;
        }
    }
}

void menuBackupSingleFile()
{
    char command;
    char fileName[64];
    int loop = 1;

    memset(fileName, '\0', 64);

    while(loop)
    {
        system("clear");
        printf("Voce deve escolher o arquivo que voce quer realizar um backup\n");
        printf("Tecle 1 para para digitar nome do arquivo\n");
        printf("Tecle 2 para mudar diretorio corrente\n");
        printf("Tecle 3 para mudar para diretorio pai\n");
        printf("Tecle 4 se quiser voltar ao menu principal\n\n");
        // listar arquivos
        printf("Lista de arquivos do diretorio: %s\n", getcwd(NULL, 0));
        system("ls -p | grep -v /");
        // listar dirs
        printf("\nLista de outros diretorios: %s\n", getcwd(NULL, 0));
        system("ls -d */");
        printf("\nDigite a opcao desejada: ");
        command = getchar();

        switch(command)
        {
            case '1':
                printf("Digite o nome do arquivo: ");
                scanf("%63s", fileName);
                // Check if file exists
                if(access(fileName, F_OK) == -1)
                {
                    printf("Arquivo nao existe\n");
                    break;
                }
                else
                {
                    backupSingleFile(fileName);
                    loop = 0;
                }
                break;
            case '2':
                char path[64];
                printf("Digite o caminho do diretorio: ");
                scanf("%63s", path);
                changeDirectory(path);
                break;
            case '3':
                changeDirectory("..");
                break;
            case '4':
                return;
                break;
            default:
                printf("Comando invalido\n");
                break;
        }
    }
}

void backupSingleFile(char* fileName)
{
    int i = 1;
    u_packet_t* pacote = createPacket(strlen(fileName), 0, BACKUP_ARQ, fileName);
    printPacket(pacote);

    while(i)
    {
        // Send packet
        sendPacket(pacote, soquete);
        printf("Pacote enviado, esperando resposta!\n");
        // Receive packet
        u_packet_t* pacoteRecebido = receivePacket(soquete);
        if(pacoteRecebido != NULL)
        {
            printf("aqui\n");
            printPacket(pacoteRecebido);
            scanf("%d", &i);
        }
    }
}

void changeDirectory(char* path)
{
    // Verify if can change
    if(chdir(path) == -1)
    {
        printf("Error changing directory\n");
    }
    else
    {
        printf("Directory changed to %s\n", path);
    }
}

uint8_t* calculateMD5(char* data, int type)
{
    uint8_t* md5 = (uint8_t*) malloc(sizeof(uint8_t) * 16);
    // Set to 0
    memset(md5, 0, 16);
    FILE* file;
    // If is a file, calculate md5 of file using md5File
    if(type == MD5_FILE)
    {
        // use fopen on data
        file = fopen(data, "r");
        if(file == NULL)
        {
            printf("Error opening file\n");
            return NULL;
        }
        md5File(file, md5);
        fclose(file);
        return md5;
    }
    else
    {
        // If is a string, calculate md5 of string using md5String
        md5String(data, md5);
        return md5;
    }
    return NULL;
}

void freeMD5(uint8_t* md5)
{
    // Free memory of md5 hash
    free(md5);
}

void printMD5(uint8_t* md5)
{
    // Print md5 hash
    for(int i = 0; i < 16; i++)
    {
        printf("%02x", md5[i]);
    }
    printf("\n");
}