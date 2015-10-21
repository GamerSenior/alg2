#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <locale.h>
#ifdef _WIN32
#include <Windows.h>
#else
#error "Sistema não suportado"
#endif
#define clear system("cls");
#define MIN 1
#define MAX 6

void gotoxy(int xpos, int ypos){
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

int main(){
    short opc = 1, spc;
    char path[] = "data/";
    char pathA[] = "data/dados.bin";
    setlocale(LC_ALL, "Portuguese");
    char c=1;
    short x = 0, y = 1;

    typedef struct{
        char nome[50];
        long int rg;
        long int cpf;
        unsigned short idade;
        float alt;

    }registro;
    registro dados;

    FILE *data;

    if(!mkdir(path, "ACCESSPERMS")){
        printf("Pasta \"data\" nao encontrada.\nCriando diretório...\n");
    }

    if(!fopen(pathA, "r+")){
        printf("Não foi possivel encontrar o arquivo dados.bin!\nUm novo arquivo será criado...\n");
        if(!fopen(pathA, "w+")){
            printf("Não foi possivel criar o arquivo.\nO programa será finalizado em breve!\n");
            Sleep(2000);
            exit(1);
        }
    }

    clear
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
                clear
                printf("MENU DE AJUDA");

                c=0; opc = 1; x = 0; y = 0;
                getch();
                clear
            }
        }while(c);
    }while(c != 27);
}
