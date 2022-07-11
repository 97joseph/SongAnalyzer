#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Struct to hold the data of the song (linked list)
//  Just Song for shorter reference 
typedef struct Song {  
    char *dataString;// Stores all details of the song
    char *title;
    char *artist;
    char *album;
    int year;
    char *genre;
    int minutes;
    int seconds;
    struct Song *next; // address of next element
}Song;

//Function of type of 'Song' to add a song to database
void Add() {
    //Input song's details for storing in a file
    char title[21];
    char performer[21];
    char album[21];
    int year;
    char genre[21];
    int minutes;
    int seconds;    
    FILE * fpointer = fopen("songs-database.txt", "a");
    printf("Enter Title: ");
    scanf("%s", title);
    printf("Enter Performer: ");
    scanf("%s", performer);
    printf("Enter Album: ");
    scanf("%s", album);
    printf("Enter Year: ");
    scanf("%d", &year);
    printf("Enter Genre: ");
    scanf("%s", genre);
    printf("Enter Duration in minutes and seconds:\n");
    printf("Minutes: ");
    scanf("%d", &minutes);
    printf("Seconds: ");
    scanf("%d", &seconds);

    //Printing received details of the song in a databese in readable format
    fprintf(fpointer, "Title: %s Performer: %s Album: %s Year: %d Genre: %s Length: %d:%d\n", title, performer, album, year, genre, minutes, seconds);
    printf("\n===================SAVED!====================\n");
    fclose(fpointer); 
    
}

// Get all songs from database in linked list 
Song *Read(void) {
    FILE * fpointer = fopen("songs-database.txt", "r"); //Open file in read mode
    
    Song *lis = NULL;   //For creating a linked list
    char line[180];

    //Read line by line and store it in a linked list until the EOF is reached
    while (fgets(line, sizeof(line), fpointer)) {
        char title[21];
        char artist[21];
        char album[21];
        int year;
        char genre[21];
        int minutes;
        int seconds;

        Song *u;
        u = malloc(sizeof(Song));
        
        //Point details of a song in linked list
        u->dataString = strdup(line);
        //sscanf for scanning only the song's details
        sscanf(line, "%*s %s %*s %s %*s %s %*s %d %*s %s %*s %d:%d", title, artist, album, &year, genre, &minutes, &seconds);
        u->title = strdup(title);
        u->artist = strdup(artist);
        u->album = strdup(album);
        u->year = year;
        u->genre = strdup(genre);
        u->minutes = minutes;
        u->seconds = seconds;

        u->next = lis;
        lis = u;
    }

    fclose(fpointer);
    return lis;
 
 }

//Function to display all the songs of selected artist
void artist() {
    Song *head;
    head = Read();
    char artist[21];

    printf("\nType without spaces! \n ==ForExampleThis==\n\n");
    printf("Enter performer: ");
    scanf("%s", artist);

    //Going through the entire linked list
    while (head != NULL) {

        // If selected artist in database, then print the title of his song
        if (strcmp(head->artist, artist) == 0) {
            printf("> %s\n", head->title);
        }
        head = head->next;
    }
    printf("\n==============================================\n\n");
}

//Function to display all the songs' title's released in the same year
void year() {
    Song *head;
    head = Read();
    int year;

    printf("Enter year: ");
    scanf("%d", &year);

    //Going through the entire linked list
    while (head != NULL) {

        // If selected year in database, then print the title of song
        if (head->year == year) {
            printf("\n> %s", head->title);
        } 
        head = head->next;
    }
    printf("\n==============================\n\n");
}

//Function to display title, artist, album and the year of release of all songs of the same genre
void genre() {
    Song *head;
    head = Read();
    char genre[21];

    printf("\nType without spaces! \n ==ForExampleThis==\n\n");
    printf("Enter genre: ");
    scanf("%s", genre);

    //Going through the entire linked list
    while (head != NULL) {

        // If selected genre in database, then print the title, artist, album and year of the song
        if (strcmp(head->genre, genre) == 0) {
            printf("\n> Title: %s Artist: %s Album: %s Year: %d", head->title, head->artist, head->album, head->year);
        }
        head = head->next;
    }
    printf("\n==============================\n\n");
}

//Function to display all DETAILS of the songs in the same album
void album() {
    Song *head;
    head = Read();
    char album[21];
    char artist[21];

    printf("\nType without spaces! \n ==ForExampleThis==\n\n");
    printf("Enter album: ");
    scanf("\n%s", album);
    printf("Enter Performer: ");
    scanf("\n%s", artist);

    //Going through the entire linked list
    while (head != NULL) {

        // If selected album in database, then print all details of the song
        if (strcmp(head->album, album) == 0 && strcmp(head->artist, artist) == 0) {
            printf("> %s\n", head->dataString);
        }
        head = head->next;
    }
    printf("==============================\n\n");
}


int main() {

        // Main menu simple interface
        printf("\n\n=============SONG STORING SYSTEM==============\n\n");
        printf("1. Add a song to database\n");
        printf("2. Display all songs of one specific artist\n");
        printf("3. Display all songs released in specific year\n");
        printf("4. Display all songs of the same genre\n");
        printf("5. Display details of all songs in an album\n");
        printf("\n==============================================\n\n");

        int choise;
        printf("Enter your choise: ");

        //Get input in range 1-5 that will call appropriate function
        scanf("%d", &choise);
            switch (choise) {
            case 1:
                Add();
                break;
            case 2:
                artist();
                break;
            case 3:
                year();
                break;
            case 4:
                genre();
                break;
            case 5:
                album();
                break;
            };
}

