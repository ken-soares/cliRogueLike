/*** includes ***/
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>


typedef struct Player{
	int xPosition;
	int yPosition;
	int health;
}Player;

/*** prototypes ***/
int screenSetup();
int mapSetup();
int handleInput(int ch, Player *player);
int playerMove(int y, int x, Player *player);
int checkPosition(int newY, int newX, Player *player);

Player *playerSetup();

int main(int argc, char **argv){

	Player *player;
	int ch;

	screenSetup();
	mapSetup();
	player = playerSetup();

	while((ch = getch()) != 'q'){
		handleInput(ch, player);
	}

	endwin();

	return 0;
}

int screenSetup(){

	initscr();
	noecho();
	refresh();
	return 0;
}

int mapSetup(){

	mvprintw(13,13,"--------");
	mvprintw(14,13,"|......|");
	mvprintw(15,13,"|......|");
	mvprintw(16,13,"|......|");
	mvprintw(17,13,"|......|");
	mvprintw(18,13,"--------");

	mvprintw(1,40,"------------");
	mvprintw(2,40,"|..........|");
	mvprintw(3,40,"|..........|");
	mvprintw(4,40,"............");
	mvprintw(5,40,"|..........|");
	mvprintw(6,40,"------------");

	mvprintw(12,40,"--------");
	mvprintw(13,40,"|......|");
	mvprintw(14,40,"|......|");
	mvprintw(15,40,"|......|");
	mvprintw(16,40,"|......|");
	mvprintw(17,40,"|......|");
	mvprintw(18,40,"--------");

	return 0;
}

Player *playerSetup(){
	Player *newPlayer;

	newPlayer = malloc(sizeof(Player));
	newPlayer->xPosition = 14;
	newPlayer->yPosition = 14;
	newPlayer->health = 20;

	playerMove(newPlayer->yPosition,newPlayer->xPosition, newPlayer);

	return newPlayer;
}

int handleInput(int ch, Player *player){

	int newY;
	int newX;

	ch = tolower(ch); // make input case insensitive

	switch(ch){
		case 'w':
			newY = player->yPosition - 1;
			newX = player->xPosition;
			break;
		case 'a':
			newY = player->yPosition;
			newX = player->xPosition - 1;
			break;
		case 's':
			newY = player->yPosition + 1;
			newX = player->xPosition;
			break;
		case 'd':
			newY = player->yPosition;
			newX = player->xPosition + 1;
			break;

		default:
			break;
	}

	checkPosition(newY,newX,player);

	return 0;
}

int checkPosition(int newY, int newX, Player *player){

	int space;

	/* check what is at new position */
	switch(mvinch(newY,newX)){
		case '.':
			playerMove(newY,newX,player);
			break;

		default:
			move(player->yPosition, player->xPosition);
			break;
	}

	return 0;
}

int playerMove(int y, int x, Player *player){
	mvprintw(player->yPosition,player->xPosition, ".");

	player->xPosition = x;
	player->yPosition = y;

	mvprintw(player->yPosition,player->xPosition, "@");
	move(player->yPosition,player->xPosition);

	return 0;
}
