#include <stdio.h>

int main(){
	int n, fat=1;

	printf("\nDigite um numero inteiro para calcular seu fatorial:\n");
	scanf("%d", &n);

	int i;
	for (i=n; i>1; i--){
		fat = fat*i;	
	}

	printf("\nFatorial de %d eh: %d\n", n, fat);

	return 0;
}
