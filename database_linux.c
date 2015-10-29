#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <locale.h>
#include <ncurses.h>

#define MIN 2
#define MAX 7

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
		box(stdscr, '|', '-'); 
		mvprintw(1,1,"-----DATABASE EVIL CORP-----");
		mvprintw(2,1,"1. Cadastro");
		mvprintw(3,1,"2. Whatever");
		mvprintw(4,1,"3. Whatever");
		mvprintw(5,1,"4. Whatever");
		mvprintw(6,1,"5. Whatever");
		mvprintw(7,1,"6. Whatever");
		x = 1; y = 2; opc = 2;
		refresh();
		do{
			mvprintw(8,1,"OPC: %hd", opc);
			mvprintw(9,1,"C: %hd", c);
			move(y,x);
			c = getch();

			if(c == 'Q' || c == 'q'){
				opc=0;
				c=0;
			}

			if(c == KEY_F(2)){
				erase();
				mvprintw(0, 0, "MENU DE AJUDA");
				x = 1, y = 2, opc = 0;
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
					if(opc>MIN){
						opc--;
						y--;
					}

					else{
						opc=MAX;
						y=MAX;
					}
				break;

				case KEY_DOWN:
					if(opc<MAX){
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