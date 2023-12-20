#include <curses.h>
#include <stdlib.h>
#include <unistd.h>


//the snake is made out of snake bits.
typedef struct snakeBit {
	int posX;
	int posY;
	struct snakeBit* nextBit;
}snakeBit;

//used for actual movement, all other bits move accordingly to the head;
snakeBit* snakeHead;
//used for cleanup later;
snakeBit* snakeButt;

void updateSnakePos(int xInc, int yInc);
void addSnakeBit();

void main() {
	WINDOW* win = initscr();
	keypad(win, true);
	nodelay(win, true);
	snakeHead = (snakeBit*) malloc(sizeof(snakeBit));
	snakeHead->posX = 0;
	snakeHead->posY = 0;
	snakeHead->nextBit = NULL;
	snakeButt = NULL;
	int foodX = rand() % 20;
	int foodY = rand()% 20;
	int dirX = 1;
	int dirY = 0;
	while(1){
		int pressed = wgetch(win);
		switch(pressed){
			case KEY_LEFT:
				dirX = -1;
				dirY = 0;
				break;
			case KEY_RIGHT:
				dirX = 1;
				dirY = 0;
				break;
			case KEY_DOWN:
				dirX = 0;
				dirY = 1;
				break;
			case KEY_UP:
				dirX = 0;
				dirY = -1;
				break;
		}
		erase();
		updateSnakePos(dirX, dirY);
		mvaddstr(foodY, foodX, "&");
		if (foodX == snakeHead->posX  &&  foodY == snakeHead->posY){
			addSnakeBit();
			foodX = rand() % 20;
			foodY = rand() % 20;
		}
		usleep(100000);
	}
	endwin();
}

void updateSnakePos(int xInc, int yInc){
	if(snakeButt != NULL){
		snakeBit* aux = snakeButt;
		while(aux->nextBit != NULL){
			aux->posX = aux->nextBit->posX;
			aux->posY = aux->nextBit->posY;
			mvaddstr(aux->posY, aux->posX, "x");
			aux = aux->nextBit;
		}
	}
	snakeHead->posX += xInc;
	snakeHead->posY += yInc;
	mvaddstr(snakeHead->posY, snakeHead->posX, "*");
}

void addSnakeBit(){
	//if the snake is 1 snakeBit long (head only) the new snake bit
	//is the first butt, otherwise update snakeButt;
	if (snakeButt == NULL){
		snakeButt = (snakeBit*) malloc(sizeof(snakeBit));
		snakeButt->posX = snakeHead->posX;
		snakeButt->posY = snakeHead->posY;
		snakeButt->nextBit = snakeHead;
	}else{
		snakeBit* newSnakeBit = (snakeBit*) malloc(sizeof(snakeBit));
		newSnakeBit->posX = snakeButt->posX;
		newSnakeBit->posY = snakeButt->posY;
		newSnakeBit->nextBit = snakeButt;
		snakeButt = newSnakeBit;
	}
}
