#ifndef TEAM_H
#define TEAM_H

#include "data.h"
#include "player.h"
#include "stack.h"

typedef struct
{
    char* name;
    double points;
    Stack members;
} Team;

extern const DataScheme teamScheme;

void printTeamStack(Stack* stack, FILE* f);

void removeWorst(Stack* stack);

#endif //TEAM_h