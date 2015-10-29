#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <locale.h>
#include <ncurses.h>

#define MIN 1
#define MAX 6

//STRUCT PARA ARMEZAR DADOS PARA CADASTRO
typedef struct{
    char nome[50];
    long int rg;
    char cpf[11];
    unsigned short idade;
    float alt;
}REGISTRO;

REGISTRO dados;

//Inicialização da função cadastro
void cadastro(REGISTRO *dados);

int main(){
	short c, opc, x, y;

	char path[] = "data/";
    char pathA[] = "data/dados.bin";

	setlocale(LC_ALL, "");
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);

	FILE *data;

    if(!mkdir(path, 0777)){
        printf("Pasta \"data\" nao encontrada.\nCriando diretório...\n");
    }

    if((data = fopen(pathA, "r+"))==NULL){
        printf("Não foi possivel encontrar o arquivo dados.bin!\nUm novo arquivo será criado...\n");
        if((data = fopen(pathA, "w+"))==NULL){
            printf("Não foi possivel criar o arquivo.\nO programa será finalizado em breve!\n");
            exit(1);
        }
    }
	
	do{
		erase();
		mvprintw(0,0,"-----DATABASE EVIL CORP-----\n");
		printw("1. Cadastro\n2. Whatever\n3. Whatever\n4. Whatever\n5. Whatever\n6. Whatever\n");
		x = 0; y = 1; opc = 1;
		refresh();
		do{
			mvprintw(7,0,"OPC: %hd", opc);
			mvprintw(8,0,"C: %hd", c);
			move(y,x);
			c = getch();

			if(c == 'Q' || c == 'q'){
				opc=0;
				c=0;
			}

			if(c == KEY_F(2)){
				erase();
				mvprintw(0, 0, "MENU DE AJUDA");
				x = 0, y = 1, opc = 0;
				refresh();
				getch();
			}

			if(c == '\n'){
				switch(opc){
					case 1:
						erase();
						cadastro(&dados);
						getch();
						opc=0;
					break;

					case 2:
						erase();
						printw("TESTE");
						getch();
						opc=0;
					break;

					default:
						erase();
						mvprintw(0,0, "Opcao invalida ou ainda em construcao.");
						getch();
						opc=0;
					break;
				}
			}

			switch(c){
				case KEY_UP:
					if(opc>1){
						opc--;
						y--;
					}

					else{
						opc=MAX;
						y=MAX;
					}
				break;

				case KEY_DOWN:
					if(opc<6){
						opc++;
						y++;
					}
					else{
						opc=MIN;
						y=MIN;
					}
			}

		}while(opc);
	}while(c);

	endwin();
	return 0;
}

void cadastro(REGISTRO *dados){
	erase();
	mvprintw(0, 0, "-----REGISTRO DE DADOS-----\nNome: ");
	refresh();
    fgets(dados->nome, sizeof(dados->nome), stdin);
    printw("RG: ");
    scanf("%ld", &dados->rg);
    fflush(stdin);
    printw("CPF: ");
    fgets(dados->cpf, sizeof(dados->cpf), stdin);
    printw("Altura: ");
    scanf("%f", &dados->alt);
    printw("Idade: ");
    scanf("%hd", &dados->idade);
}