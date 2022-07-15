/** @file song_analyzer.c
 *  @brief A small program to analyze songs data.
 *  @author Mike Z.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Juan G.
 *  @author STUDENT_NAME
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "473875632_emalloc_7_4061257891092015.h"
#include "ics.h"
#include "473875632_list_22_2063433319193623.c"

void convert();
node_t *read_file(const char *, node_t *, const int, const int);
void date_print(node_t *);
void summary_print(node_t *, void *);
void free_list_memory(node_t *);

#define MAX_LINE_LEN 80

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->word);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of words: %d\n", len);

    apply(l, print_node, "%s\n");
}

/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
	int from_y = 0, from_m = 0, from_d = 0;
    int to_y = 0, to_m = 0, to_d = 0;
    char *filename = NULL;
    int cmd_start, cmd_end;
    node_t *head = NULL;

    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], "--start=", 7) == 0) {
            sscanf(argv[i], "--start=%d/%d/%d", &from_y, &from_m, &from_d);
        } else if (strncmp(argv[i], "--end=", 5) == 0) {
            sscanf(argv[i], "--end=%d/%d/%d", &to_y, &to_m, &to_d);
        } else if (strncmp(argv[i], "--file=", 7) == 0) {
            filename = argv[i]+7;
        }
    }

    if (from_y == 0 || to_y == 0 || filename == NULL) {
        fprintf(stderr,
            "usage: %s --start= --end= --file=icsfile\n",
            argv[0]);
        exit(1);
    }

	convert(from_y, from_m, from_d, to_y, to_m, to_d, &cmd_start, &cmd_end);
	head = read_file(filename, head, cmd_start, cmd_end);
	date_print(head);
	apply(head, summary_print, NULL);
	free_list_memory(head);
	
    exit(0);
}

/*
Usage:  when given a date-time, we add the number of days 
	    so that we get the correct dates
	    i.e. given for before is:
	    
		20190520T111500
		
		assuming that the value for after is the default 100,
		the date stored in after will become:
		
		20190828T111500
		
		this date is 100 days after the starting date
	
From: timeplay.c from our first assignment
*/
void dt_increment(char *after, const char *before, int const num_days)
{
	struct tm temp_time;
	time_t    full_time;
	
	memset(&temp_time, 0, sizeof(struct tm));
    sscanf(before, "%4d%2d%2d", &temp_time.tm_year, &temp_time.tm_mon, &temp_time.tm_mday);
    temp_time.tm_year -= 1900;
    temp_time.tm_mon -= 1;
    temp_time.tm_mday += num_days;

    full_time = mktime(&temp_time);
    after[0] = '\0';
    strftime(after, 9, "%Y%m%d", localtime(&full_time));
    strncpy(after + 8, before + 8, 7);
    after[15] = '\0';	
}

void dt_format(char *formatted_time, const char *dt_time, const int len)
{
    struct tm temp_time;
    time_t    full_time;

    memset(&temp_time, 0, sizeof(struct tm));
    sscanf(dt_time, "%4d%2d%2d", &temp_time.tm_year, &temp_time.tm_mon, &temp_time.tm_mday);
    temp_time.tm_year -= 1900;
    temp_time.tm_mon -= 1;
    full_time = mktime(&temp_time);
    strftime(formatted_time, len, "%B %d, %Y (%a)",
    localtime(&full_time));
}




void song_print(node_t* n){

	char* time = NULL;
	time = (char *)emalloc(sizeof(char) * 25);
		dt_format(time, n->val->dtstart, 25);
		printf("%s\n", time);
		for(int i = 0; i < strlen(time); i++){
		
			printf("-%s", (i==strlen(time)-1) ? "\n":"");
		
		}
		free(time);
}


void summary_print(node_t *n, void *arg){

	int starting_string;
	int ending_string;
	
	// this gets our hours from the date-time
	sscanf(n->val->dtstart + 9, "%4d", &starting_time);
	sscanf(n->val->dtend   + 9, "%4d", &ending_time);
	
	time_print(starting_time);
	printf(" to ");
	time_print(ending_time);
	printf(": %s {{%s}}\n", n->val->summary, n->val->location);
	
	//for when there is a non null node, where current and next dont share equal starting dates
	if (n->next != NULL && strncmp(n->val->dtstart, n->next->val->dtstart, 8) != 0){
		printf("\n");
		date_print(n->next);
	}
}

/*
Usage: by initilizing what is contained in the event_t structure from the ics.h file
	   we can make an event

input: event_t event: this is the event we want to make
	   
	   pointers to the contents of our event i.e., char *dtstart
*/
void make_event(event_t *event, char *dtstart, char *dtend, char *summary, char *location, char *rrule){
	
	strncpy(event->dtstart, dtstart, strlen(dtstart));
    strncpy(event->dtend, dtend, strlen(dtend));
    strncpy(event->summary, summary, strlen(summary));
    strncpy(event->location, location, strlen(location));
    strncpy(event->rrule, rrule, strlen(rrule));

}

/*
Usage: this can be used to get rid of the newline char (\n)
	   and replace it with '\0'

Input: char*  l: 		address of first characters position
	   size_t length:   size (in bytes) of the memory block
					    pointed to by l
		FILE  *infile:     stream which l is read from
*/
void delete_line(char* l, size_t length, FILE *infile){
	
	getline(&l, &length, infile);
	//if the end of our line is (length - 1 since it start counting position with 0) is '\n' replace with '\0'
	if(l[strlen(l) - 1] == '\n'){
		l[strlen(l) - 1] = '\0';
	}
}

void *determine_event(const int command_start, const int command_end, char *dtstart, char *dtend, char *summary, char *location, char *rrule, node_t *head){

	event_t *current_event = NULL;
	node_t  *current_node  = NULL;
	if((atoi(dtstart) >= command_start) && (atoi(dtstart) <= command_end)){
		
		current_event = (event_t *)emalloc(sizeof(event_t));
		make_event(current_event, dtstart, dtend, summary, location, rrule);
		current_node = new_node(current_event);
		head = sorted_insert(head, current_node);
	}
	return head;
}

/*
Usage:  opens and reads the file line by line, storing the contents of the icsfile
	    in a linkedlist. also check for repeating events (and how many reps)

Inputs: const char *filename:     file to read
		const char *head:		  head of our list
		const int command_start:  start date from cmdl
		const int command_end:    end date from cmdl

Return: head of linked list after our insertion 
*/
node_t *read_file(const char *filename, node_t *head, const int command_start, const int command_end){

	char *end, *start;
	char *summary;
	char *location;
	char *rrule;
	// address of first character
	char *l = NULL;
	//size of memory block
	size_t length = 0;
	//dates after incrementation
	char *after = (char *)emalloc(sizeof(char) * 16);

	FILE* infile = fopen(filename, "r");
	if(infile == NULL){
		exit(1);
	}
	while(getline(&l, &length, infile) >= 0){
	
		if (strncmp(l, "BEGIN:VEVENT", 12) == 0) {
			// find and store the start and end info
			while (strncmp(l, "DTSTART:", 8) != 0) { 
                delete_line(l, length, infile); 
            }
			start = strdup(l + 8);
			while(strncmp(l, "DTEND:", 6) != 0){
				delete_line(l, length, infile);
			}
			end = strdup(l + 6);
			delete_line(l, length, infile);
			
			// this is for our repeating events
			if(strncmp(l, "RRULE:FREQ=WEEKLY;UNTIL", 23) == 0){
				l[39] = '\0';
				rrule = strdup(l + 24);
				delete_line(l, length, infile);
			} else if(strncmp(l, "RRULE:", 6) == 0){
				l[47] = '\0';
				rrule = strdup(l + 32);
				delete_line(l, length, infile);
			} else {
				rrule = strdup("");
			}
			
			// find and store location and summary info
			while(strncmp(l, "LOCATION:", 9) != 0){
				delete_line(l, length, infile);
			}
			location = strdup(l + 9);
			
			while(strncmp(l, "SUMMARY:", 8) != 0){
				delete_line(l, length, infile);
			}
			summary = strdup(l + 8);
			head = determine_event(command_start, command_end, start, end, summary, location, rrule, head);
			int x = 0;
			while(strcmp(start, rrule) <= 0 || (strcmp(rrule, "") != 0 && x == 0)){
				if (x > 0){
					head = determine_event(command_start, command_end, start, end, summary, location, rrule, head);
				}
				dt_increment(after, start, 7);
				strncpy(start, after, strlen(after));
				x++;
			}
			free(start), free(end), free(summary), free(location), free(rrule);
			
		}
	}
	free(l);
	fclose(infile);
	free(after);
	return head;
}

/*
you give this a start and and end from cmdl, and it converts the date into a
start date int and an end date int to rep the ate info from ics files.
i.e from_y = 2021, from_m = 11, and from_d = 17:

2021*10000 + 11*100 + 17 = 20211114

which would be november 17th 2021

*/
void convert(int from_y, int from_m, int from_d, int to_y, int to_m, int to_d, int *start, int *end){
    
	*start = from_y * 10000 + from_m * 100 + from_d;
    *end = to_y * 10000 + to_m * 100 + to_d;

}


void free_list_memory(node_t *head){

	if(head->next){
		free_list_memory(head->next);
	}
	free(head->val);
	free(head);
}


