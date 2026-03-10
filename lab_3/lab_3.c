#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAT_DIM 5
#define VAL_MAX 100

void f1(int *n);
void f2(int *n);
void f3(int n);
void f4(int n);
void task1(int *n);

void task1(int *n) {
    printf("Functia main\n");
    printf("Valoare initiala: %d\n", *n);
    printf("Valoare adresa initiala: %p\n", n);
    printf("\n");

    f1(n);

    printf("------------ Valoare finala n: %d ------------\n", *n);
    return;
}

void f1(int *n) {
    (*n)++;
    printf("Intrare Functia f1\n");
    printf("Valoare incrementare in f1: %d\n", *n);
    printf("Valoare adresa in f1: %p\n", n);
    printf("\n");

    f2(n);

    printf("Iesire Functia f1\n");
    printf("Valoare incrementare in f1: %d\n", *n);
    printf("Valoare adresa in f1: %p\n", n);
    printf("\n");
    return;
}

void f2(int *n) {
    (*n)++;
    printf("Intrare Functia f2\n");
    printf("Valoare incrementare in f2: %d\n", *n);
    printf("Valoare adresa in f2: %p\n", n);
    printf("\n");

    f3(*n);

    printf("Iesire Functia f2\n");
    printf("Valoare incrementare in f2: %d\n", *n);
    printf("Valoare adresa in f2: %p\n", n);
    printf("\n");
    return;
}

void f3(int n) {
    n++;
    printf("Intrare Functia f3\n");
    printf("Valoare incrementare in f3: %d\n", n);
    printf("Valoare adresa in f3: %p\n", &n);
    printf("\n");

    f4(n);

    printf("Iesire Functia f3\n");
    printf("Valoare incrementare in f3: %d\n", n);
    printf("Valoare adresa in f3: %p\n", &n);
    printf("\n");
    return;
}

void f4(int n) {
    n++;
    printf("Intrare Functia f4\n");
    printf("Valoare incrementare in f4: %d\n", n);
    printf("Valoare adresa in f4: %p\n", &n);
    printf("\n");

    return;
}

// EXERCITIU 2

void afis_matrix(int a[MAT_DIM][MAT_DIM]) {
    for(int i = 0; i < MAT_DIM; i++) {
        for(int j = 0; j < MAT_DIM; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    printf("\n");
    return;
}

void task2() {
    srand(time(NULL));
    int a[MAT_DIM][MAT_DIM];
    float medii[MAT_DIM];

    for(int i = 0; i < MAT_DIM; i++) {
        medii[i] = 0;
        for(int j = 0; j < MAT_DIM; j++) {
            a[i][j] = rand() % 10;
            medii[i] += a[i][j];
        }

        medii[i] /= MAT_DIM; 
    }

    afis_matrix(a);

    for(int i = 0; i < MAT_DIM; i++)
        printf("%.2f ", medii[i]);
    printf("\n");
    
    for(int i = 0; i < MAT_DIM; i++)
        for(int j = 0; j < MAT_DIM; j++)
            a[i][j] -= medii[i];

    for(int i = 0; i < MAT_DIM; i++) {
        medii[i] = 0;
        for(int j = 0; j < MAT_DIM; j++) {
            medii[i] += a[i][j];
        }

        medii[i] /= MAT_DIM; 
    }

    printf("\n");
    afis_matrix(a);

    for(int i = 0; i < MAT_DIM; i++)
        printf("%.2f ", medii[i]);
    printf("\n");

    return;
}

// EX3

void stergere_min(int **v, int cnt, int *adr_min) {
    int cnt_new_arr = 0;
    int *new_arr = (int*)calloc(cnt - 1, sizeof(int));
    for(int i = 0; i < cnt; i++) 
        if (&(*v)[i] != adr_min) 
            new_arr[cnt_new_arr++] = (*v)[i];

    *v = new_arr;
    *v = (int*)realloc(*v, (cnt - 1) * sizeof(int));
    free(new_arr);
    
    return;
}

int *gasire_minim(int **v, int cnt) {
    int min = __INT_MAX__;
    int *min_ptr = NULL;

    for(int i = 0; i < cnt; i++)
        if(min > (*v)[i]){
            min = (*v)[i];
            min_ptr = &((*v)[i]);
        }

    return min_ptr;
}

void task3() {
    int *v;
    v = (int*)calloc(VAL_MAX, sizeof(int));
    int cnt = 0;
    
    int x;
    printf("Introduceti elemente pana la 0 (max. 100)\n");
    scanf("%d", &x);

    while(x && cnt <= 100) {
        v[cnt++] = x;
        scanf("%d", &x);
    }

    printf("Inainte de stergere\n");
    for(int i = 0; i < cnt; i++)
        printf("%d ", v[i]);
    printf("\n");

    int *adr_min;
    adr_min = gasire_minim(&v, cnt);
    printf("Adresa elementului minim este: %p, iar val: %d\n", adr_min, *adr_min);
    stergere_min(&v, cnt, adr_min);

    for(int i = 0; i < cnt - 1; i++)
        printf("%d ", v[i]);
    return;
}

int main(void) {
    int n = 0;

    //task1(&n);

    //task2();

    task3();

    return 0;
}