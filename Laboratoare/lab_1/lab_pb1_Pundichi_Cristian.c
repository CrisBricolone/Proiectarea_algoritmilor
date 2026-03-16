#include <stdlib.h>
#include <stdio.h>
#define SIZE_TABLA 8
#define NR_INPUTS 32
#define WHITE 'w'
#define BLACK 'b'
#define KING 'k'
#define QUEEN 'q'
#define ROOK 'r'
#define BISHOP 'b'
#define KNIGHT 'n'

int t_sah[SIZE_TABLA][SIZE_TABLA];

//plaseaza piesele pe tabla de sah
void plasare_piese(const char input_s[], const char color) {
    int index, pawn_pos;
    
    //realizeaza simetria necesara in functie de culoare
    if(color == WHITE) {
        index = 0;
        pawn_pos= 1;
    }
    else {
        index = 7;
        pawn_pos = 6;
    }

    //plaseaza piesele in functie de tipul lor
    if (input_s[0] == KING)
        t_sah[index][4] = 1;
    else if (input_s[0] == QUEEN)
        t_sah[index][3] = 1;
    else if (input_s[0] == ROOK)
        if (t_sah[index][0] == 0)
            t_sah[index][0] = 1;
        else t_sah[index][7] = 1;
    else if (input_s[0] == KNIGHT)
        if (t_sah[index][1] == 0)
            t_sah[index][1] = 1;
        else t_sah[index][6] = 1;
    else if (input_s[0] == BISHOP)
        if (t_sah[index][2] == 0)
                t_sah[index][2] = 1;
        else t_sah[index][5] = 1;
    else 
        {
            //plaseaza pionii in functie de culoara lor
            int cnt = 0;
            while (t_sah[pawn_pos][cnt] != 0)
                cnt++;
            t_sah[pawn_pos][cnt] = 1;
        }
    
    return;
}

int main(){
    char input_s[3];
	
    //initializeaza tabla de sah cu valori de 0
    for (int i = 0; i < SIZE_TABLA; i++)
        for (int j = 0; j < SIZE_TABLA; j++)
            t_sah[i][j] = 0;
	
    for (int i = 0; i < NR_INPUTS; i++)
    {
        scanf("%s", input_s);

        //verifica ce fel de culoare are piesa respectiva
        switch(input_s[1]) {
            case WHITE:
                plasare_piese(input_s, WHITE);
                break;
            case BLACK:
                plasare_piese(input_s, BLACK);
                break;
            default:
                //valideaza daca piesa respectiva are o culoarea valida
                printf("Not a valid format. Write a valid string!\n");
                i--;
                break;
        }
    }

    //afiseaza piesele de sah plasate pe tabla de sah
    for (int i = SIZE_TABLA - 1; i >= 0; i--)
    {
        for (int j = 0; j < SIZE_TABLA; j++)
            printf("%d", t_sah[i][j]);
        printf("\n");
    }

    return 0;	
}

