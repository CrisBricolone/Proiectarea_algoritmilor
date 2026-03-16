#include "player.h"

#include <string.h>
#include <stdlib.h>

void printPlayer(const void* data)
{
    if (data == NULL) return;
    Player* p = (Player*) data;
    printf("PLAYER{%s %s, %ld}\n", p->firstName, p->lastName, p->points);
}

void initPlayer(void** ptr, ...)
{
    Player* p = (Player*) calloc(1, sizeof(Player));
    
    va_list args;
    va_start(args, ptr);
    char* firstName = va_arg(args, char*);
    char* lastName = va_arg(args, char*);
    size_t points = va_arg(args, size_t);
    va_end(args);

    p->firstName = (char*) malloc(sizeof(char) * (strlen(firstName) + 1));
    p->lastName = (char*) malloc(sizeof(char) * (strlen(lastName) + 1));
    p->points = points;

    strcpy(p->firstName, firstName);
    strcpy(p->lastName, lastName);


    *ptr = p;

}

void freePlayer(void* data)
{
    if (data == NULL)
    {
        printf("Cannot free null player\n");
        return;
    }
    Player* p = (Player*) data;

    free(p->firstName);
    free(p->lastName);

    free(data);

}

//Replaces dest with a new pointer with data copied from src (old dest must be freed by the user)
void copyPlayer(void** dest, const void* src)
{
    if (src == NULL)
    {
        printf("Cannot copy null player\n");
        return;
    }

    Player* p2 = (Player*) src;
    Player* p;
    initPlayer(&p, p2->firstName, p2->lastName, p2->points);
    *dest = p;
}

//Not needed, not comparing players here
int comparePlayer(const void* item1, const void* item2)
{
    return 0;
}

const DataScheme playerScheme = 
{
    &initPlayer,
    &freePlayer,
    &copyPlayer,
    &printPlayer,
    &comparePlayer
};