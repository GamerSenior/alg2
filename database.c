#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <locale.h>

//SE FOR EXECUTADO EM WINDOWS
#ifdef _WIN32
#include <Windows.h>
void gotoxy(int xpos, int ypos){
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}
#define limpa system("cls");

//SE FOR EXECUTADO EM LINUX
#elif __linux__
#include <ncurses.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>
#include <fcnt1.h>
void gotoxy(int xpos, int ypos){
    move(xpos, ypos);
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
#define limpa system("clear");
#else
#error "Sistema n�o suportado"
#endif
#define MIN 1
#define MAX 6

typedef struct{
    char nome[50];
    long int rg;
    char cpf[11];
    unsigned short idade;
    float alt;
}REGISTRO;

REGISTRO dados;

void cadastro(REGISTRO *);

int main(){
    short opc = 1, spc;
    char path[] = "data/";
    char pathA[] = "data/dados.bin";
    setlocale(LC_ALL, "Portuguese");
    char c=1;
    short x = 0, y = 1;

    FILE *data;

    if(!mkdir(path, "ACCESSPERMS")){
        printf("Pasta \"data\" nao encontrada.\nCriando diret�rio...\n");
    }

    if(!fopen(pathA, "r+")){
        printf("N�o foi possivel encontrar o arquivo dados.bin!\nUm novo arquivo ser� criado...\n");
        if(!fopen(pathA, "w+")){
            printf("N�o foi possivel criar o arquivo.\nO programa ser� finalizado em breve!\n");
            exit(1);
        }
    }

    limpa
    do{
        x = 0; y = 1; c = 1;
        printf("-----DATABASE EVIL CORP-----\n");
        printf("1. Cadastro\n2. Whatever\n3. Whatever\n4. Whatever\n5. Whatever\n0. Sair");

        //Verifica se a tecla pressionada
        do{
            gotoxy(x, y);
            if(kbhit()){
                spc = 0;
                c = getch();
                //Se for tecla especial, altera valor de spc para 1
                if(c<=0){
                    spc = 1;
                    c = getch();
                }
                //Seta pra baixo aumenta o Y
                if(c == 80 && spc == 1){
                    if(opc < MAX){
                        opc++;
                        y++;
                    }else{
                        opc = MIN;
                        y = MIN;
                    }
                }
                //Seta pra cima diminui o Y
                if(c == 72 && spc == 1){
                    if(opc>1){
                        opc--;
                        y--;
                    }else{
                        opc = MAX;
                        y = MAX;
                    }
                }
            }
            //Menu de Ajuda
            if(c == 59 && spc == 1){
                limpa
                printf("MENU DE AJUDA");

                c=0; opc = 1; x = 0; y = 0;
                getch();
                limpa
            }

            if(c == 13){
                switch(opc){
                case 1:
                    cadastro(&dados);
                    puts(dados.nome);
                    printf("%ld\n", dados.rg);
                    puts(dados.cpf);
                    fwrite(&dados, sizeof(dados), 1, data);
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 6:
                    exit(1);
                    break;
                }
            }

        }while(c);
    }while(c != 27);
}

cadastro(REGISTRO *dados){
    limpa
    printf("-----REGISTRO DE DADOS-----\nNome: ");
    fgets(dados->nome, sizeof(dados->nome), stdin);
    printf("RG: ");
    scanf("%ld", &dados->rg);
    fflush(stdin);
    printf("CPF: ");
    fgets(dados->cpf, sizeof(dados->cpf), stdin);
    printf("Altura: ");
    scanf("%f", &dados->alt);
    printf("Idade: ");
    scanf("%hd", &dados->idade);
}
