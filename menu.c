#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define COORDX_MENU 13
#define COORDY_MENU 13

void iniciar_menu(void);
char ler_opcao(void);


int main(void){
	// _setcursortype(_NOC);
	char c1 = getch();
	iniciar_menu();
	char c = ler_opcao();
	clrscr();
	return 0;

}

void iniciar_menu(void){
	clrscr();
	printf("  \t\t      ___   ___  _  _   ___ \n"
          "   \t\t     |__ \\ / _ \\| || | / _ \\\n"
          "   \t\t        ) | | | | || || (_) |\n"
          "   \t\t       / /| | | |__   _> _ < \n"
          "   \t\t      / /_| |_| |  | || (_) |\n"
          "   \t\t     |____|\\___/   |_| \\___/ \n"
		  "\n\n\n\n\n"
		  "DIGITE SUA OPCAO: \n"
		  "1- NOVO JOGO\n"
		  "2- CARREGAR JOGO\n"
		  "3- SAIR\n");
	
		  gotoxy(COORDX_MENU, COORDY_MENU);
	return;
}

char ler_opcao(void){
	char opc;
	int opc_valida;
	do{
		opc = getch();
		opc_valida = (opc == '1') + (opc == '2') + (opc == '3');
	}while(!opc_valida);
	
	return opc;
}