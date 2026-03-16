#include "team.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void printTeam(const void* data)
{
    if (data == NULL) return;
    Team* t = (Team*) data;
    printf("[Team] %s (%f)\n\n", t->name, t->points);
    SimpleNode* members = t->members.top;
    while (members != NULL)
    {
        playerScheme.print(members->value);
        printf("\n");
        members = members->next;
    }
    printf("\n=============================\n\n");
}

void initTeam(void** ptr, ...)
{
    Team* t = (Team*) calloc (1, sizeof(Team));

	va_list args;
	va_start(args, ptr);
	char* name = va_arg(args, char*);
	double points = va_arg(args, double);
	va_end(args);

	t->name = (char*) malloc(sizeof(char) * (strlen(name) + 1));
	t->points = points;

	t->members.top = NULL;
	t->members.scheme = &playerScheme;

	strcpy(t->name, name);

	*ptr = t;
}

void freeTeam(void* data)
{ 
	if (data == NULL)
    {
        printf("Cannot free null team\n");
        return;
    }

	Team* t = (Team*) data;

	free(t->name);
	deleteStack(&(t->members));
	free(data);

}

//Replaces dest with a new pointer with data copied from src (old dest must be freed by the user)
void copyTeam(void** dest, const void* src)
{
   if (src == NULL)
    {
        printf("Cannot copy null team\n");
        return;
    }

    Team* t2 = (Team*) src;
	Team* t;

	initTeam(&t, t2->name, t2->points);

	Team* t1 = (Team*) dest;
	copyStack(&t->members, &t2->members);

	*dest = t;

}

// char* toLowerCase(const char* str)
// {
// 	char* lc = (char*) calloc(strlen(str) + 1, sizeof(char));
// 	for (int i = 0; str[i]; i++)
// 		lc[i] = tolower(str[i]);

// 	return lc;
// }

/*
	> 0  -> item1 < item2
	= 0  -> item1 = item2
	< 0  -> item1 > item2
*/
int compareTeam(const void* item1, const void* item2)
{
	Team* t1 = (Team*) item1;
	Team* t2 = (Team*) item2;


	double diff = t1->points - t2->points;
	if ((diff >= 0 && diff < EPSILON) || (diff < 0 && -diff < EPSILON))
		return strcmp(t1->name, t2->name);
		
	if (diff < 0)
		return -1;

	return 1;
}

const DataScheme teamScheme = 
{
    &initTeam,
    &freeTeam,
    &copyTeam,
    &printTeam,
	&compareTeam
};

void printTeamStack(Stack* stack, FILE* f)
{
	if (stack->scheme != &teamScheme)
	{
		printf("Stack scheme does not match team scheme\n");
		return;
	}

	SimpleNode* head = stack->top;

	while (head != NULL)
	{
		fprintf(f, "%s\n", ((Team*)head->value)->name);
		head = head->next;
	}

}

void removeWorst(Stack* stack)
{
	if (stack->scheme != &teamScheme)
	{
		printf("Stack scheme does not match team scheme\n");
		return;
	}
	if (stack->top == NULL)
	{
		printf("Stack Empty\n");
		return;
	}

	float worstPoints = ((Team*)(stack->top)->value)->points;

	SimpleNode* prev = stack->top;
	int isHead = 1;

	SimpleNode* head = stack->top;
	while (head->next != NULL)
	{
		Team* t = (Team*) head->next->value;
		double diff = t->points - worstPoints; //worstPoints > points -> diff < 0
		if (diff < 0 && -diff > EPSILON) //Difference greater than 0.01
		{
			isHead = 0;
			prev = head;
			worstPoints = t->points;
		}
		head = head->next;
	}

	if (isHead)
	{
		pop(stack, NULL);
		return;
	}

	SimpleNode* n = prev->next;
	prev->next = n->next;
	teamScheme.free(n->value);
	free(n);

}