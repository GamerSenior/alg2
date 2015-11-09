/*--------------------------------------------
| gcc database_linux.c -lncurses -o database |
--------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <locale.h>
#include <ncurses.h>
#include <dirent.h>

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
void gerenciar();
void pastas();

int main(){
	short c, opc, x, y;
	char buf[1000];

	char path[] = "data/";
    char pathA[] = "data/dados.bin";
    char pathH[] = "data/help.txt";

	setlocale(LC_ALL, "");
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);

	FILE *data;
	FILE *help;

    if(!mkdir(path, 0777)){
        printw("Pasta \"data\" nao encontrada.\nCriando diretório...\n");
    }

    if((data = fopen(pathA, "rb+"))==NULL){
        printw("Não foi possivel encontrar o arquivo dados.bin!\nUm novo arquivo será criado...\n");
        if((data = fopen(pathA, "wb+"))==NULL){
            printw("Não foi possivel criar o arquivo.\nO programa será finalizado em breve!\n");
            exit(1);
        }
    }
	
	do{
		erase();
		box(stdscr, '|', '-'); 
		mvprintw(1,1,"-----DATABASE EVIL CORP-----");
		mvprintw(2,1,"1. Cadastrar");
		mvprintw(3,1,"2. Gerenciar cadastros");
		mvprintw(4,1,"3. Gerenciar pastas");
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
				if((help = fopen(pathH, "r"))==NULL){
					printw("Nao foi possivel abrir o arquivo de ajuda.\nVerifique se o mesmo se encontra na pasta \"data\"");
				}
				move(0,0);
				while(fgets(buf, 1000, help))
					printw("%s", buf);

				fclose(help);
				x = 1, y = 2, opc = 0;
				refresh();
				getch();
			}

			if(c == '\n'){
				switch(opc){
					case 2:
						erase();
						cadastro(&dados);
						getch();
						opc=0;
					break;

					case 3:
						erase();
						gerenciar();
						opc=0;
					break;

					case 4:
						erase();
						pastas();
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
	fclose(data);
	return 0;
}

void pastas(){
	short c, opc, x, y, f;

	do{
		erase();
		mvprintw(0, 0,"Gerenciamento de Pastas\n1. Criar\n2. Apagar\n");
		char dirName[50] = "data/", buff[25];
		x = 0; y = 1; opc = 1;
		refresh();
		do{
			move(y, x);
			c = getch();

			if(c == 'Q' || c == 'q'){
				opc = 0;
				c = 0;
			}

			if(c == '\n'){
				switch(opc){
					case 1:
						erase();
						mvprintw(0, 0, "Nome da pasta: ");
						echo();
						getnstr(buff, 25);
						strcat(dirName, buff);
						noecho();
						if(!mkdir(dirName, 0777))
							printw("Criado diretório: %s", dirName);
						strcpy(dirName, "data/");
						opc=0;
						getch();
					break;

					case 2:
						erase();
						mvprintw(0, 0, "Nome da Pasta: ");
						echo();
						getnstr(buff, 25);
						strcat(dirName, buff);
						noecho();
						if(!rmdir(dirName))
							printw("Pasta removida com sucesso!\n");
						else
							printw("Erro ao remover a pasta. Verifique se a mesma está vazia!\n");
						strcpy(dirName, "data/");
						opc=0;
						getch();
					break;

					case 3:
					opc = 0;
					c = 0;
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
						opc=2;
						y=2;
					}
				break;

				case KEY_DOWN:
					if(opc<2){
						opc++;
						y++;
					}
					else{
						opc=1;
						y=1;
					}
			}
		}while(opc);
	}while(c);
}

void gerenciar(){
	short c, opc, x, y, f;
	char fileName[25], path[50] = "data/";
	char name[25];
	do{
		erase();
		mvprintw(0,0,"Gerenciamento de Cadastros\n1. Mover\n2. Apagar\n3. Voltar");
		x = 0; y = 1; opc = 1;
		refresh();
		do{
			move(y,x);
			c = getch();

			if(c == 'Q' || c == 'q'){
				opc=0;
				c=0;
			}
			
			if(c == '\n'){	
				switch(opc){
				 	case 1:
					 break;

					case 2:
						erase();
				 		mvprintw(0,0,"Digite o nome do cadastro que deseja deletar (case sensitive): ");
				 		echo();
				 		getnstr(fileName, 25);
				 		strcat(path, fileName);
				 		printw("Caminho: %s\n", path);
				 		noecho();
				 		f = remove(path);
				 		if(f == 0){
				 			printw("Arquivo removido com sucesso");
				 		}else{
				 			printw("Erro ao remover o arquivo ou nome incorreto. Tente novamente.");
				 		}
				 		getch();
				 		opc = 0;
				 		strcpy(path, "data/");
				 	break;

				 	case 3:
				 	opc=0;
				 	c=0;
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
						opc=3;
						y=3;
					}
				break;

				case KEY_DOWN:
					if(opc<3){
						opc++;
						y++;
					}
					else{
						opc=1;
						y=1;
					}
			}

		}while(opc);
	}while(c);

}

void cadastro(REGISTRO *dados){
	erase();
	echo();
	char path[50] = "data/";
	char ans;
	FILE *usr;
	mvprintw(0, 0, "-----REGISTRO DE DADOS-----\nNome: ");
	refresh();
    getnstr(dados->nome, sizeof(dados->nome));
    strcat(path, dados->nome);
    if((usr = fopen(path, "rb")) != NULL){
    	printw("Ja existe um cadastro com esse nome. Deseja sobreescrever? (S/N)\n");
    	do{
    		ans = toupper(getch());
    	}while(ans != 'S' && ans != 'N');
    	if(ans=='S'){
    		if((usr = fopen(path, "wb")) == NULL)
    			printw("Problema ao gerar arquivo ou privilegios insulficientes!\n");
    	}    	
    }else{
    	usr = fopen(path, "wb");
    }
    do{
	    printw("\nRG: ");
	    scanw("%ld", &dados->rg);
	    printw("CPF: ");
	    getnstr(dados->cpf, sizeof(dados->cpf));
	    printw("Altura: ");
	    scanw("%f", &dados->alt);
	    printw("Idade: ");
	    scanw("%hd", &dados->idade);

	    printw("Os dados estão corretos? (S/N)\n");
	    do{
	    	ans = toupper(getch());
	    }while(ans != 'S' && ans != 'N');
	}while(ans != 'S');
	fwrite(dados, sizeof(*dados), 1, usr);
	fclose(usr);
    noecho();
}