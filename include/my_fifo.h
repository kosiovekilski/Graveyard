#ifndef MY_FIFO_H
#define MY_FIFO_H

#include <stdio.h>      /* printf */
#include <fcntl.h>      /* open, O_RDONLY, O_WRONLY */
#include <stdlib.h>     /* rand */
#include <unistd.h>     /* close, write, read */
#include <sys/stat.h>   /* mkfifo */
#include <sys/types.h>  /* third open arg (not used) */

#define FIFO_PATH	"/tmp/fifo_grave"
#define FIFO_MODE	0666 /* rw- rw- rw-  user/group/other*/
#define FIFO_BUFF	50


void read_option(char* opt);

void write_option(char opt);

void read_str(char* str);

void write_str(char* str);

void setup_server();

void setup_client();


#endif
