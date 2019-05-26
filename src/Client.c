#include <stdio.h>      /* printf, scanf */
#include <stdlib.h>     /* EXIT_SUCCESS */

#include "grave.h"      /* grave_t */
#include "my_fifo.h"	/* */


void scan_int(const char *, int*);

void scan_str(const char *, char*);


int main(){
	int		fd;
	char	opt;
	char	buff[GRAVE_BUFF];
	grave_t g;

	(void) printf("Client:\n");

	setup_client();

	while(1){
		menu();
		scan_int("> option: ", &opt);

		write_option(opt);

		switch(opt){
			case 0:
				(void) printf("Goodbye ... \n");
				exit(0);
				break;

			case 1:
				read_option(&opt);
                (void) printf("> %i graves from file\n", opt);
				break;

			case 2:
				read_option(&opt);
                (void) printf("> %i graves to file\n", opt);
				break;

			case 3:
				scan_int("row: ", &opt);
				write_option(opt);

				scan_int("col: ", &opt);
				write_option(opt);

				read_str(buff);
				(void) printf("%s\n", buff);
				break;

			case 4:
				scan_int("row: ", &g.row);
				write_option(g.row);

				scan_int("col: ", &g.col);
				write_option(g.col);

				read_option(&opt);
				if(false == opt) {
					clear_grave(&g);
					(void) printf("> Grave not in range\n");
				} else {
					scan_int("status: ", &g.status);
					scan_str("date: ", g.date);
					scan_str("name: ", g.person_name);

					grave_to_str(g, buff);
					write_str(buff);
					read_option(&opt);
					if(true == opt)
						(void) printf("> Grave saved\n");
				}
				break;

			case 5:
				read_option(&opt);
				(void) printf("> printing %i graves\n", opt);
				while(0 != (opt--)){
					read_str(buff);
					(void) printf("%s\n", buff);
					clear_grave(&g);
				}
				write_option(opt);
				break;

			case 6:
				scan_int("row: ", &g.row);
				scan_int("col: ", &g.col);
				scan_str("name: ", g.person_name);
				grave_to_str(g, buff);
				write_str(buff);
				read_option(&opt);
				if(true == opt)
					(void) printf("> Grave saved forever\n");
				else
					(void) printf("> Not in range\n");
				
				break;

			case 7:
				scan_int("row: ", &g.row);
				scan_int("col: ", &g.col);
				scan_str("name: ", g.person_name);
				grave_to_str(g, buff);
				write_str(buff);
				read_option(&opt);
				if(true == opt)
					(void) printf("> Grave saved for 15 years\n");
				else
					(void) printf("> Not in range\n");
				
				break;

			default:
				(void) printf("> Client choose not available option\n");
		}
	}

	return EXIT_SUCCESS;
}


void scan_int(const char *str, int *arg){
	(void) printf("%s", str);
	fflush(stdin);
	(void) scanf("%d", arg);
	fflush(stdin);
}

void scan_str(const char *str, char *arg){
	(void) printf("%s", str);
	fflush(stdin);
	(void) scanf("%s", arg);
	fflush(stdin);
}#include <stdio.h>      /* printf, scanf */
#include <stdlib.h>     /* EXIT_SUCCESS */

#include "grave.h"      /* grave_t */
#include "my_fifo.h"	/* */


void scan_int(const char *, int*);

void scan_str(const char *, char*);


int main(){
	int		fd;
	char	opt;
	char	buff[GRAVE_BUFF];
	grave_t g;

	(void) printf("Client:\n");

	setup_client();

	while(1){
		menu();
		scan_int("> option: ", &opt);

		write_option(opt);

		switch(opt){
			case 0:
				(void) printf("Goodbye ... \n");
				exit(0);
				break;

			case 1:
				read_option(&opt);
                (void) printf("> %i graves from file\n", opt);
				break;

			case 2:
				read_option(&opt);
                (void) printf("> %i graves to file\n", opt);
				break;

			case 3:
				scan_int("row: ", &opt);
				write_option(opt);

				scan_int("col: ", &opt);
				write_option(opt);

				read_str(buff);
				(void) printf("%s", buff);

			case 4:
				scan_int("row: ", &opt);
				g.row = opt;
				write_option(opt);

				scan_int("col: ", &opt);
				g.col = opt;
				write_option(opt);

				read_option(&opt);
				if(false == opt) {
					clear_grave(&g);
					(void) printf("> Grave not in range\n");
				} else {
					scan_int("status: ", &g.status);
					scan_str("date: ", g.date);
					scan_str("name: ", g.person_name);

					grave_to_str(g, buff);
					write_str(buff);
					read_option(opt);
					if(true == opt)
						(void) printf("> Grave saved\n");
				}
				break;

			case 5:
				read_option(&opt);
				while(0 != (opt--)){
					read_str(buff);
					(void) printf("%s\n", buff);
					clear_grave(&g);
				}
				write_option(opt);
				break;

			case 6:
				scan_int("row: ", &g.row);
				scan_int("col: ", &g.col);
				scan_str("name: ", g.person_name);
				grave_to_str(g, buff);
				write_option(buff);
				read_option(&opt);
				if(true == opt)
					(void) printf("> Grave saved forever\n");
				else
					(void) printf("> Not in range\n");
				
				break;

			case 7:
				scan_int("row: ", &g.row);
				scan_int("col: ", &g.col);
				scan_str("name: ", g.person_name);
				grave_to_str(g, buff);
				write_option(buff);
				read_option(&opt);
				if(true == opt)
					(void) printf("> Grave saved for 15 years\n");
				else
					(void) printf("> Not in range\n");
				
				break;

			default:
				(void) printf("> Client choose not available option\n");
		}
	}

	return EXIT_SUCCESS;
}


void scan_int(const char *str, int *arg){
	(void) printf("> Enter %s: ", str);
	(void) scanf(" %d", arg);
}

void scan_str(const char *str, char *arg){
	(void) printf("> Enter %s: ", str);
	(void) scanf(" %s", arg);
}
