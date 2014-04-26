#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define MASU 3 //10以下でお願いします。

int BAN[MASU+2][MASU+2];
int endflag = 0;
int hairetsu[MASU*MASU];
int kouho[(MASU - 1) * 2];

void zyunbi(){
	int i, j;
	int x, y;
	for (i = 0; i < MASU + 2; i++){
		for (j = 0; j < MASU + 2; j++){
			BAN[i][j] = 0;
		}
	}
	srand((unsigned) time(NULL));
	i = 0;
	do{
		x = rand() % MASU + 1;
		y = rand() % MASU + 1;
		if (BAN[x][y] == 0){
			BAN[x][y] = i++;
		}
	} while (i != MASU*MASU);
}

void hyouzi(){
	int i, j,k;
	for (i = 0; i < MASU + 2; i++){
		for (j = 0; j < MASU + 2; j++){
			if (i == 0 || i == MASU + 1){
				if (i == 0){
					if (j == 0){
						printf("┏");
					}
					else if (j == MASU + 1){
						printf("━┓");
					}
					if (j < MASU - 1){
						printf("━┳");
					}
				}
				else if (i == MASU + 1){
					if (j == 0){
						printf("┗");
					}
					else if (j == MASU + 1){
						printf("━┛");
					}
					if (j < MASU - 1){
						printf("━┻");
					}
				}
			}
			else{
				if (i != 1&&j==0){
					for (k = 0; k < MASU + 2; k++){
						if (k == 0){
							printf("┣");
						}
						else if (k == MASU + 1){
							printf("━┫");
						}
						else if (k < MASU ){
							printf("━╋");
						}
					}
					printf("\n");

				}
				
				if (j == 0){
					printf("┃");
				}
				else if (j != MASU + 1){
					printf("%2d┃", BAN[i][j]);
				}
			}
		}
		printf("\n");
	}
}

int nyuuryoku(){
	int n,i,p=0;
	while (1){
		scanf_s("%d", &n);
		for (i = 0; i < MASU*MASU; i++){
			if (n == kouho[i]){
				p = n;
				break;
			}
		}
		if (p != 0){
			break;
		}
	}
	return p;
}


void hairetsusort(){
	int i, j;
	for (i = 1; i < MASU + 1; i++){
		for (j = 1; j < MASU + 1; j++){
			hairetsu[BAN[i][j]] = (i - 1)*MASU + j - 1;
		}
	}
}

void shori(){
	int i, j;
	hairetsusort();
	for (i = 0,j=0; i < MASU*MASU; i++){
		if (hairetsu[0] / MASU == hairetsu[i] / MASU || hairetsu[0] % MASU == hairetsu[i] % MASU){
			kouho[j++] = i;
		}
	}
	int number=nyuuryoku();
	i=-1;
	if (hairetsu[number] / MASU == hairetsu[0] / MASU){
		if (hairetsu[number] % MASU>hairetsu[0] % MASU){
			while (i != number){
				i=BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU + 1] = BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU + 2];
				BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU + 2] = 0;
				hairetsusort();
			}
		}
		else{
			while (i!=number){
				i = BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU + 1] = BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU ];
				BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU ] =0;
				hairetsusort();
			}
		}
	}
	else if (hairetsu[number] % MASU == hairetsu[0] % MASU){
		if (hairetsu[number] / MASU>hairetsu[0] / MASU){
			while (i != number){
				i = BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU + 1] = BAN[hairetsu[0] / MASU + 2][hairetsu[0] % MASU + 1];
				BAN[hairetsu[0] / MASU + 2][hairetsu[0] % MASU + 1] = 0;
				hairetsusort();
			}
		}
		else{
			while (i != number){
				i = BAN[hairetsu[0] / MASU + 1][hairetsu[0] % MASU + 1] = BAN[hairetsu[0] / MASU ][hairetsu[0] % MASU+1];
				BAN[hairetsu[0] / MASU ][hairetsu[0] % MASU+1] = 0;
				hairetsusort();
			}
		}
	}
}

void hantei(){
	int i, j;
	endflag = 1;
	for (i = 1; i < MASU + 1; i++){
		for (j = 1; j < MASU + 1; j++){
			if (BAN[i][j] != (i - 1)*MASU + j){
				if (BAN[i][j] != 0){
					endflag = 0;
					break;
				}
			}
		}
		if (endflag == 0){
			break;
		}
	}

}

void kekkahyouzi(){
	printf("クリアー");
}

int main(){
	zyunbi();
	do{
		hyouzi();
		shori();
		hantei();
	} while (endflag != 1);
	kekkahyouzi();
	return 0;
}