#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
	int bomb;
	int open;
	int parent;

}Celula;
int l, c, tam = 10;

Celula table[10][10];


void startTable(){
	for(l = 0; l < tam; l++){
		for(c = 0; c < tam; c++){
			table[l][c].bomb = 0;
			table[l][c].open = 0;
			table[l][c].parent = 0;
		}
	}
}

void sortBomb(int n){
	int i;
	srand(time(NULL));
	for(i = 0; i < n; i++){
		l = rand() % n ;
		c = rand() % n;
		if(table[l][c].bomb == 0) 
			table[l][c].bomb = 1;
		else
			i--;
	}
}

int validateCoordinate(int l, int c){
	if(l >= 0 && l < tam && c >= 0 && c < tam)
		return 1;
	else
		return 0;
}

int countParentBomb(int l ,int c){
	int qtd = 0;

	if(validateCoordinate(l - 1, c) && table[l - 1][c].bomb)
		qtd++;
	if(validateCoordinate(l + 1, c) && table[l + 1][c].bomb)
		qtd++;
	if(validateCoordinate(l, c + 1) && table[l][c + 1].bomb)
		qtd++;
	if(validateCoordinate(l, c - 1) && table[l][c - 1].bomb)
		qtd++;
	if(validateCoordinate(l -  1, c + 1) && table[l - 1][c + 1].bomb)
		qtd++;
	if(validateCoordinate(l + 1, c + 1) && table[l + 1][c + 1].bomb)
		qtd++;
	if(validateCoordinate(l - 1, c - 1) && table[l - 1][c - 1].bomb)
		qtd++;
	if(validateCoordinate(l  + 1, c - 1) && table[l + 1][c - 1].bomb)
		qtd++;
	return qtd;
}

void coutBomb(){

	for(l = 0; l < tam; l++){
		for(c = 0; c < tam; c++)
			table[l][c].parent = countParentBomb(l, c);
	}
}

void printTable(){
	printf("\n\n\t");
	for(l = 0; l < tam; l++)
		if(l == 0)
			printf("     %d", l);
		else
			printf("     %d", l); 
	for(l = 0; l < tam; l++){
			printf("\n\t  -------------------------------------------------------------\n");
			
		
		printf(" \t%d |", l);
		for(c = 0; c < tam; c++){
			if(table[l][c].open){
				if(table[l][c].bomb)
					printf("  *  ");
				else
					printf("  %d  ", table[l][c].parent);
			}else
				printf("     ");
			printf("|");
		}
			if(l == 9)
				printf("\n\t  -------------------------------------------------------------\n");
	}
}
void openCell(int row, int colum){
	if(validateCoordinate(row,colum) == 1 && table[row][colum].open == 0){
		table[row][colum].open = 1;
		if(table[row][colum].parent == 0){
			openCell(row - 1, colum);
			openCell(row + 1, colum);
			openCell(row, colum + 1);
			openCell(row, colum - 1);
		}
	}
}

int victory(){
	int qtd = 0;
	for(l = 0; l < tam; l++){
		for(c = 0; c < tam; c++){
			if(table[l][c].open == 0 && table[l][c].bomb == 0)
				qtd++;
		}	
	}
	return qtd;
}

void play(){
	int row = 0, colum = 0;
	do{
		do{
			printf("Digite a linha e coluna desejada: ");
			scanf("%d%d", &row,&colum);	
			if(validateCoordinate(row,colum) == 0 || table[row][colum].open == 1)
				printf("Por favor digite uma coordenada valida.\n");
			
			
				
			
		}while(validateCoordinate(row,colum) == 0 || table[row][colum].open == 1);
	
		
		
		
		openCell(row,colum);
		system("cls"); 
		printTable();
	}while(victory() != 0 && table[row][colum].bomb == 0);
	
	if(table[row][colum].bomb == 1)
		printf("\n\tVoce perdeu\n");
	else
		printf("\n\tParabéns voce ganhou\n");

}


int main(){
	int option;
	
	do{
		startTable();
		sortBomb(5);
		coutBomb();
		printTable();
		play();
	
		printf("Digite 1 para jogar novamente.\n");
		scanf("%d", &option);
	}while(option == 1);

	
	
	return 0;
}







