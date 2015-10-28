#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <locale.h>
#include <ncurses.h>

#define MIN 1
#define MAX 6

int main(){
	short c, opc, x, y;
	x = 0; y = 1; opc = 1;

	setlocale(LC_ALL, "");
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	printw("-----DATABASE EVIL CORP-----.\n");
	printw("1. Cadastro\n2. Whatever\n3. Whatever\n4. Whatever\n5. Whatever\n6. Whatever");
	refresh();

	do{
		move(y,x);
		c = getch();

		if(c == 'Q' || c == 'q')
			opc=0;

		if(c == KEY_F(1)){
			printw("MENU DE AJUDA");
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

	endwin();
	return 0;
}