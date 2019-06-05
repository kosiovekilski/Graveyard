#ifndef GRAVE_H
#define GRAVE_H

#include <stdio.h>		/* sprintf, sscanf*/
#include <string.h>		/* memset, size_t */
#include <fcntl.h>      /* open, O_RDONLY, O_WRONLY */
#include <unistd.h>		/* close, write, read */
#include <stdint.h>		/* uint32_t */
#include <stdbool.h>	/* bool */
#include <time.h>		/* time, localtime, strftime */

#define GRAVE_COL	5
#define GRAVE_ROW	10
#define GRAVE_FILE	"../data/graves.bin" /* file location */
#define GRAVE_BUFF	50 /* grave buffer size */


typedef enum grave_status_t {
	FREE_GRAVE,
	SAVED_GRAVE,
	USED_GRAVE
} grave_status_t;

typedef struct {
	uint32_t		row;
	uint32_t		col;
	grave_status_t	status;
	char			date[11]; /* "DD-MM-YYYY" */
	char			person_name[20];
} grave_t;


bool is_free(grave_t);

bool is_not_free(grave_t);

bool in_range(uint32_t, uint32_t);

bool not_in_range(uint32_t, uint32_t);

void grave_to_str(grave_t g, char *s);

void str_to_grave(grave_t *g, char *s);

size_t print_graves(grave_t graves[][GRAVE_COL]);

size_t not_free_graves(grave_t graves[][GRAVE_COL]);

size_t graves_to_file(grave_t graves[][GRAVE_COL]);

size_t graves_from_file(grave_t graves[][GRAVE_COL]);

void menu();

void clear_grave(grave_t *g);

void save_grave(grave_t *g);

void save_grave_15(grave_t *g);

void special_dates(grave_t g);

#endif
