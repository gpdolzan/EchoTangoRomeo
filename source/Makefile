CFLAGS = -Wextra -g

objs = main.o ConexaoRawSocket.o packet.o

# regra default (primeira regra)
all: main

# regras de ligacao
main: $(objs)

# regras de compilação
main.o: main.c
ConexaoRawSocket.o: ConexaoRawSocket.c ConexaoRawSocket.h
packet.o: packet.c packet.h
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f main

run: main
	./main