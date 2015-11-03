#include <stdio.h>
#include <string.h>

void encrypt(char plaintext[255]);

int main(){
	int pos, i=0, key, r;
	char text_buff[255];
	char *pathH = "/data/help.txt";
	char *pathE = "/data/help_e.txt";
	FILE *help;


	if((help = fopen(pathH, "r"))==NULL)
		printf("Erro na leitura do arquivo help.txt");


	printf("Cipher BCC\nAviso: Arquivo help.txt deve conter apenas 255 caracteres por linha.\n");
	encrypt(text_buff);

	fclose(help);
}

void encrypt (char plaintext[255]){
	char buffer[255], ciphertext[255];
	char key[255] = "abracadabra";
	short i, j, dtln, kln;
	dtln = strlen(plaintext);
	kln  = strlen(key);

	strcpy(buffer, key);

	do{
		if(strlen(plaintext)>strlen(key)){
			strcat(buffer, key);
		}

		if(plaintext[i]==32)
			i++;

		for(i=0; i<dtln; i++){
			if(plaintext[i]==32){
				chipertext[i] = '';
				i++;
			}else 
			if(plaintext[i]<=90 && plaintext[i]>=60){
				
			}		
		}

	}while(fgets(text_buff, sizeof(text_buff), help));
}