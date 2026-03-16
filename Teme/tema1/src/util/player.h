#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stddef.h>

#include "data.h"

typedef struct Player
{
    size_t points;
    char* firstName;
    char* lastName;
} Player;

extern const DataScheme playerScheme;

#endif //PLAYER_H