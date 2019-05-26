#include "grave.h"


bool is_free(grave_t grave){
	return (FREE_GRAVE == grave.status) ? true : false;
}

bool is_not_free(grave_t grave){
	return !is_free(grave);
}

bool in_range(uint32_t row, uint32_t col){
	return ((row < GRAVE_ROW) 
			&& (row >= 0) 
			&& (col < GRAVE_COL)
			&& (col >= 0)
			) ? true : false;
}

bool not_in_range(uint32_t row, uint32_t col){
	return !in_range(row, col);
}

void grave_to_str(grave_t g, char *s){
	(void) memset(s, ' ', strlen(s)); /* clear buffer */
	(void) sprintf(s, "%u - %u : %i : %s : %s", g.row, g.col, (int)g.status, g.date, g.person_name);
}

void str_to_grave(grave_t *g, char *s){
	(void) sscanf(s, "%u - %u : %i : %s : %s", &(g->row), &(g->col), &(g->status), g->date, g->person_name);
}

size_t print_graves(grave_t graveyard[][GRAVE_COL]){
	int	 i, j, n = 0;
	char buff[GRAVE_BUFF];

	for(i = 0; i < GRAVE_ROW; i++){
		for(j = 0; j < GRAVE_COL; j++){
			if(0 != graveyard[i][j].status){
				grave_to_str(graveyard[i][j], buff);
				(void) printf("%s\n", buff);
				(void) memset(buff, ' ', strlen(buff)); /* clear buffer */
				n++;
			}
		}
	}
	if(0 == n){
		(void) printf("No graves found..\n");
	}
	return n;
}

size_t not_free_graves(grave_t graveyard[][GRAVE_COL]){
	int	 i, j, n = 0;

	for(i = 0; i < GRAVE_ROW; i++){
		for(j = 0; j < GRAVE_COL; j++){
			if(0 != graveyard[i][j].status){
				n++;
			}
		}
	}
	return n;
}

size_t graves_to_file(grave_t graves[][GRAVE_COL]){
	int		i, j;
	int		fd = open(GRAVE_FILE, O_CREAT | O_WRONLY);
	size_t	n = 0;
	char	buff[GRAVE_BUFF] = {0};

	if(fd < 0){
		perror(GRAVE_FILE);
		return 0;
	}

	for(i = 0; i < GRAVE_ROW; i++){
		for(j = 0; j < GRAVE_COL; j++){
			if(is_not_free(graves[i][j])){
				grave_to_str(graves[i][j], buff);
				(void) write(fd, buff, GRAVE_BUFF);
				(void) memset(buff, ' ', strlen(buff)); /* clear buffer */
				n++;
			}
		}
	}

	(void) close(fd);
	return n;
}

size_t graves_from_file(grave_t graves[][GRAVE_COL]){
	grave_t g;
	int		fd = open(GRAVE_FILE, O_RDONLY);
	size_t	n = 0;
	char	buff[GRAVE_BUFF] = {0};

	if(fd < 0){
		perror(GRAVE_FILE);
		return 0;
	}

	while(read(fd, buff, GRAVE_BUFF) > 0){
		str_to_grave(&g, buff);
		if(in_range(g.row, g.col)){
			graves[g.row][g.col] = g;
			n++;
		}
	}

	(void) close(fd);
	return n;
}

void menu(){
	(void) printf("\nMenu:\n"
		"0: Exit\n"
		"1: Load graves from file\n"
		"2: Save graves to file\n"
		"3: Show grave\n"
		"4: Change grave\n"
		"5: Show all graves\n"
		"6: Save grave forever\n"
		"7: Save grave for 15 years\n"
	);
}


void clear_grave(grave_t *g){
	g->row = 0;
	g->col = 0;
	g->status = FREE_GRAVE;
	(void )memset(g->date, ' ', strlen(g->date));
	(void) memset(g->person_name, ' ', strlen(g->person_name));
}


void save_grave(grave_t *g){
	g->status = SAVED_GRAVE;
	(void) strcpy(g->date, "00-00-0000"); /* 00-00-0000 means forever */
}

void save_grave_15(grave_t *g){
	char		date[11];
	time_t		now = time(NULL) ;
	struct tm	*ts;

    ts = localtime(&now); /* today */
    ts->tm_year += 15;

    strftime(date, sizeof(date), "%02d-%02m-%04Y", ts);

	g->status = SAVED_GRAVE;
	(void) strcpy(g->date, date);
}
