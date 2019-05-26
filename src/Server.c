#include <stdio.h>      /* printf */
#include <stdlib.h>     /* EXIT_SUCCESS */

#include "grave.h"      /* grave_t */
#include "my_fifo.h"    /* */


int main(){
    char    i, j;
    char    opt = 1;
    char    buff[GRAVE_BUFF];
	grave_t	graves[GRAVE_ROW][GRAVE_COL] = {{{0}}};
    grave_t g;

    (void) printf("Server:\n");

    setup_server();
    
    while(1){
        read_option(&opt);
        
        switch(opt){
            case 0:
                (void) printf("Client exiting ...\n");
                exit(0);
		        break;

            case 1:
                opt = graves_from_file(graves);
                (void) printf("> %i graves from file\n", opt);
                write_option(opt);
                break;

            case 2:
                opt = graves_to_file(graves);
                (void) printf("> %i graves to file\n", opt);
                write_option(opt);
                break;

            case 3:
                read_option(&i);
                read_option(&j);
                if(in_range(i, j))
                    grave_to_str(graves[i][j], buff);
                else
                    (void) strcpy(buff, "Not in range.");
                write_str(buff);
		break;
                
            case 4:
                // change grave
                read_option(&i);
                read_option(&j);

                opt = in_range(i, j);
                write_option(opt);

                if(false == opt) {
                    (void) printf("> Grave not in range\n");
                } else {
                    read_str(buff);
                    str_to_grave(&g, buff);
                    graves[g.row][g.col] = g;
                    write_option(opt);
                }
                
                break;

            case 5:
                opt = not_free_graves(graves);
                write_option(opt);
                (void) printf("> Sending %i graves to Client...", opt);
                for(i = 0; i < GRAVE_ROW; i++){
                    for(j = 0; j < GRAVE_COL; j++){
                        if(is_not_free(graves[i][j])){
                            opt--;
                            grave_to_str(graves[i][j], buff);
                            //(void) printf("%s\n", buff);
                            sleep(1);
                            write_str(buff);
                        }
                        if(0 == opt) {
                            (void) printf("Done\n");
                            i = GRAVE_ROW;
                            j = GRAVE_COL;
                        }
                    }
                }
                read_option(&opt);
                if(0 == opt)
                    (void) printf("> Client received all graves\n");
                    opt = 5;
                break;

            case 6:
                read_str(buff);
                str_to_grave(&g, buff);
                opt = in_range(g.row, g.col);
                if(true == opt){
                    save_grave(&g);
                    graves[g.row][g.col] = g;
                }
                write_option(opt);
                break;

            case 7:
                read_str(buff);
                str_to_grave(&g, buff);
                opt = in_range(g.row, g.col);
                if(true == opt){
                    save_grave_15(&g);
                    graves[g.row][g.col] = g;
                }
                write_option(opt);
                break;

            default:
                /*(void) printf("> undefined option\n");*/
		break;
        }

    }
    
    return EXIT_SUCCESS;
}
