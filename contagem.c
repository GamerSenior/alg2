/* GIOVANI GARCIA ABEL
   RA: 151022755      */

#include <stdlib.h>
#include <stdio.h>
#define MAX 50

void getVet(int n, int vet[]){
	int i;

	for(i = 0; i < n; i++){
		printf("[%d] ", n);
		scanf("%d", vet[n]);
	}
}

void mostrarVet(int n, int vet[]){
	int i;

	for(i = 0; i < n; i++){
		printf("[%d] %d\n", i, vet[i]);
	}
}

void ordena(int n, int vet[]){
	int count[MAX], i, j, x;

	for(i = 0; i < n; i++){
		x = 0;
		for(j = 1; j < n; j++){
			if(vet[i]>vet[j])
				x++;
		}
		printf("%d %d\n", x, vet[i]); //DEBUG

        count[x] = vet[i];
	}

	mostrarVet(n, count);
}

int main(){
	int vet[MAX], n;

	printf("Numero de elementos no vetor: ");
	do{
		scanf("%d", &n);
	}while(n>50);
	getVet(n, vet);
    system("cls");
    //ordena(n, vet);
    mostrarVet(n, vet);
}
