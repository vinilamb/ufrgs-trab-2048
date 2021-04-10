#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define DIMENSAO 4

void rand_num(int mat[][DIMENSAO]);
void imprimir_matriz(int mat[][DIMENSAO]);
void mov_baixo(int mat[][DIMENSAO]);
void mov_cima(int mat[][DIMENSAO]);
void mov_esq(int mat[][DIMENSAO]);
void mov_dir(int mat[][DIMENSAO]);
int validar_movimento(int mat[][DIMENSAO]);
void unir_baixo(int mat[][DIMENSAO]);
void unir_cima(int mat[][DIMENSAO]);
void unir_esq(int mat[][DIMENSAO]);
void unir_dir(int mat[][DIMENSAO]);

typedef int Tabuleiro[DIMENSAO][DIMENSAO];

int main(void){
	// _setcursortype(_NOCURSOR);
	int mat[DIMENSAO][DIMENSAO] = {0, 0, 0,  0,
								   0, 0,  0,  0,
								   0, 0,  0,  0,
								   0, 0, 0,  0};	

	rand_num(mat);
	rand_num(mat);
	imprimir_matriz(mat);
	
	do{
		if((GetKeyState(VK_UP) & 0x80) && validar_movimento(mat)){
			mov_cima(mat);
			unir_cima(mat);
			mov_cima(mat);
			Sleep(100);
		}
		else if((GetKeyState(VK_DOWN) & 0x80) && validar_movimento(mat)){
			mov_baixo(mat);
			unir_baixo(mat);
			mov_baixo(mat);
			Sleep(100);
		}
		else if((GetKeyState(VK_RIGHT) & 0x80) && validar_movimento(mat)){
			mov_dir(mat);
			unir_dir(mat);
			mov_dir(mat);
			Sleep(100);
		}
		else if((GetKeyState(VK_LEFT) & 0x80) && validar_movimento(mat)){
			mov_esq(mat);
			unir_esq(mat);
			mov_esq(mat);
			Sleep(100);
		}
		if(validar_movimento){
			rand_num(mat);
			imprimir_matriz(mat);
		}
		
	}while(!(GetKeyState(VK_ESCAPE) & 0x80));
	return 0;
}


void imprimir_matriz(int mat[][DIMENSAO]){
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			printf("%5d", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	return;
}

void mov_baixo(int mat[][DIMENSAO]){
	int troca;
	do{
		troca =0;
		for(int i = 0; i < DIMENSAO; i++){
			for(int j = 0; j < DIMENSAO; j++){
				if((mat[DIMENSAO - i][j] == 0) && (i != 0) &&  (mat[DIMENSAO - i - 1][j] != 0)){
					int aux = mat[DIMENSAO - i][j];
					mat[DIMENSAO - i][j] = mat[DIMENSAO - i -1][j];
					mat[DIMENSAO - i - 1][j] = aux;
					troca = 1;
				}
			}
		}	
	}while(troca == 1);
	return;
}


void mov_cima(int mat[][DIMENSAO]){
	int troca;
	do{
		troca =0;
		for(int i = 0; i < DIMENSAO; i++){
			for(int j = 0; j < DIMENSAO; j++){
				if((mat[i][j] == 0)&& (i != DIMENSAO - 1) && (mat[i + 1][j] != 0)){
					int aux = mat[i][j];
					mat[i][j] = mat[i + 1][j];
					mat[i + 1][j] = aux;
					troca = 1;
				}
			}
		}	
	}while(troca == 1);
	return;
}	
	
void mov_dir(int mat[][DIMENSAO]){  //Creio que dê pra simplificar isso com transposição de matrizes
	int troca;
	do{
		troca =0;
		for(int i = 0; i < DIMENSAO; i++){
			for(int j = 0; j < DIMENSAO; j++){
				if((mat[i][DIMENSAO - j] == 0) && ((j != 0) && mat[i][DIMENSAO- j - 1] != 0)){
					int aux = mat[i][DIMENSAO - j];
					mat[i][DIMENSAO - j] = mat[i][DIMENSAO - j - 1];
					mat[i][DIMENSAO - j - 1] = aux;
					troca = 1;
				}
			}
		}	
	}while(troca == 1);
	return;
}

void mov_esq(int mat[][DIMENSAO]){  //Creio que dê pra simplificar isso com transposição de matrizes
	int troca;
	do{
		troca =0;
		for(int i = 0; i < DIMENSAO; i++){
			for(int j = 0; j < DIMENSAO; j++){
				if((mat[i][j] == 0) && ((j != DIMENSAO - 1) && mat[i][j + 1] != 0)){
					int aux = mat[i][j];
					mat[i][j] = mat[i][j + 1];
					mat[i][j + 1] = aux;
					troca = 1;
				}
			}
		}	
	}while(troca == 1);
	return;
}

int validar_movimento(int mat[][DIMENSAO]){
	int copia[DIMENSAO][DIMENSAO];
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			copia[i][j] = mat[i][j];
		}
	}
	if(GetKeyState(VK_UP) & 0x80){
		mov_cima(copia);
	}	
	else if(GetKeyState(VK_DOWN) & 0x80){
		mov_baixo(copia);
	}
	else if(GetKeyState(VK_RIGHT) & 0x80){
		mov_dir(copia);
	}
	else if(GetKeyState(VK_LEFT) & 0x80){
		mov_esq(copia);
	}
	
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			if(copia[i][j] != mat[i][j] || (copia[i][j] == copia[i+1][j] && i != (DIMENSAO - 1) && copia[i][j] != 0)|| (copia[i][j] == copia[i][j+1] && j != (DIMENSAO - 1) && copia[i][j] != 0))
				return 1;
		}
	}
	return 0;	
}


void unir_baixo(int mat[][DIMENSAO]){
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			if(mat[DIMENSAO-i -1][j] == mat[DIMENSAO - i - 2][j] && i != (DIMENSAO - 1)){
				mat[DIMENSAO - i - 1][j] *= 2;
				mat[DIMENSAO - i - 2][j] = 0;
			}
		}
	}
	return;
}

void unir_cima(int mat[][DIMENSAO]){
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			if(mat[i][j] == mat[i + 1][j] && i != (DIMENSAO - 1)){
				mat[i][j] *= 2;
				mat[i +1][j] = 0;
			}
		}
	}
	return;
}

void unir_esq(int mat[][DIMENSAO]){
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			if(mat[i][j] == mat[i][j + 1] && i != (DIMENSAO - 1)){
				mat[i][j] *= 2;
				mat[i][j + 1] = 0;
			}
		}
	}
	return;
}

void unir_dir(int mat[][DIMENSAO]){
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			if(mat[i][DIMENSAO - 1 - j] == mat[i][DIMENSAO - 2 - j] && j != DIMENSAO - 1){
				mat[i][DIMENSAO - 1 - j] *= 2;
				mat[i][DIMENSAO - 2 - j] = 0;
			}
		}
	}
	return;
}



void rand_num(int mat[][DIMENSAO]){
	int cont=0;
	int numero = rand() % 10;
	int lugar = rand() % 16;
	if(numero == 9)
		numero = 4;
	else
		numero = 2;
	
	do{
	
		if(mat[lugar / DIMENSAO][lugar % DIMENSAO] == 0){
			mat[lugar / DIMENSAO][lugar % DIMENSAO] = numero;
			cont++;
		}
		lugar = rand() % 16;
	}while(cont == 0);
}