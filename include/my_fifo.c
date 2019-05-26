#include "my_fifo.h"

void read_option(char* opt){
    int fd = open(FIFO_PATH, O_RDONLY);
    (void) read(fd, opt, 1); 
    (void) close(fd);
}

void write_option(char opt){
    int fd = open(FIFO_PATH, O_WRONLY);
    (void) write(fd, &opt, 1); 
    (void) close(fd);
}

void read_str(char* str){
    int fd = open(FIFO_PATH, O_RDONLY);
    (void) read(fd, str, FIFO_BUFF); 
    (void) close(fd);
}

void write_str(char* str){
    int fd = open(FIFO_PATH, O_WRONLY);
    (void) write(fd, str, FIFO_BUFF); 
    (void) close(fd);
}

void setup_server(){
    char a;
	(void) mkfifo(FIFO_PATH, FIFO_MODE); 
    read_option(&a);
    write_option(a);
    (void) printf("> Received from Client: %i\n", a); 
}

void setup_client(){
    char a, b;
	(void) mkfifo(FIFO_PATH, FIFO_MODE); 
    a = rand() % 100;
    write_option(a);
	(void) printf("> Send to Server: %i\n", a);
    read_option(&b);
    if(a != b) {
        printf("> Connection failed..\n\n");
        exit(1);
    } else {
        printf("> Connected..\n");
    }
}
