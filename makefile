CC=gcc
CFLAGS=
INCLUDES=-Iinclude
OBJ=obj/grave.o obj/my_fifo.o

target:
	$(CC) $(CFLAGS) $(INCLUDES) -c include/grave.c -o obj/grave.o
	$(CC) $(CFLAGS) $(INCLUDES) -c include/my_fifo.c -o obj/my_fifo.o
	$(CC) $(CFLAGS) $(INCLUDES) src/Server.c $(OBJ) -o bin/Server
	$(CC) $(CFLAGS) $(INCLUDES) src/Client.c $(OBJ) -o bin/Client
