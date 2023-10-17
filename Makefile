CC=cc
RPC_SYSTEM=rpc.o

.PHONY: all format

all: server client

server: server.c $(RPC_SYSTEM)
	$(CC) -o $@ $^

client: client.c $(RPC_SYSTEM)
	$(CC) -o $@ $^

$(RPC_SYSTEM): rpc.c rpc.h
	$(CC) -Wall -c -o $@ $<

format:
	clang-format -style=file -i *.c *.h

clean:
	rm -f server client $(RPC_SYSTEM)
