CFLAGS = -Wextra -g 

objs = main.o trfiles.o client.o server.o md5.o ConexaoRawSocket.o packet.o

# regra default (primeira regra)
all: main

# regras de ligacao
main: $(objs)

# regras de compilação
main.o: main.c
client.o: client.c client.h
trfiles.o: trfiles.c trfiles.h
md5.o: md5.c md5.h
packet.o: packet.c packet.h
server.o: server.c server.h
ConexaoRawSocket.o: ConexaoRawSocket.c ConexaoRawSocket.h
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f main

run: main
	./main