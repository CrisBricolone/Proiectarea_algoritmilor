#include <stdlib.h>
#include <stdio.h>

int function(int x, int *cnt){
	x=x-2;
	(*cnt)++;

	if(x)
		x = function(x, cnt);
		
	return x;
}

int main(){
	int a=30, i=0;
	
	a=function(a, &i);
	printf("%d", i);
	
	return 0;	
}

