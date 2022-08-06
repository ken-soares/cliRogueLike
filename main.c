/*** includes ***/
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>


typedef struct Position{
	int x;
	int y;
}Position;

typedef struct Room{
	Position position;
	int height;
	int width;
	/* Monster **monsters; */
	/* Item **items; */
}Room;

typedef struct Player{
	Position position;
	int health;
}Player;

/*** prototypes ***/
int screenSetup();
Room **mapSetup();
int drawRoom(Room *room);
Room *createRoom(int x, int y, int width, int height);
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

Room **mapSetup(){


	Room **rooms;
	rooms = malloc(sizeof(Room) * 6);

	/* mvprintw(13,13,"--------"); */
	/* mvprintw(14,13,"|......|"); */
	/* mvprintw(15,13,"|......|"); */
	/* mvprintw(16,13,"|......|"); */
	/* mvprintw(17,13,"|......|"); */
	/* mvprintw(18,13,"--------"); */

	rooms[0] = createRoom(13, 13, 6, 8);
	drawRoom(rooms[0]);

	/* mvprintw(1,40,"------------"); */
	/* mvprintw(2,40,"|..........|"); */
	/* mvprintw(3,40,"|..........|"); */
	/* mvprintw(4,40,"............"); */
	/* mvprintw(5,40,"|..........|"); */
	/* mvprintw(6,40,"------------"); */

	rooms[1] = createRoom(40, 2, 6, 8);
	drawRoom(rooms[1]);

	/* mvprintw(12,40,"--------"); */
	/* mvprintw(13,40,"|......|"); */
	/* mvprintw(14,40,"|......|"); */
	/* mvprintw(15,40,"|......|"); */
	/* mvprintw(16,40,"|......|"); */
	/* mvprintw(17,40,"|......|"); */
	/* mvprintw(18,40,"--------"); */

	rooms[2] = createRoom(40, 12, 6, 12);
	drawRoom(rooms[2]);

	return rooms;
}

int drawRoom(Room *room){

	int x;
	int y;

	/* draw top and bottom */

	for(x = room->position.x; x < room->position.x+room->width; x++){

		//top
		mvprintw(room->position.y,x,"-");
		//bottom
		mvprintw(room->position.y + room->height - 1,x,"-");
	}

	/* draw floors and walls */

	for(y = room->position.y+1; y < room->position.y+room->height - 1; y++){

		//draw walls
		mvprintw(y,room->position.x,"|");
		mvprintw(y,room->position.x+room->width - 1,"|");

		for(x = room->position.x+1; x<room->position.x+room->width - 1; x++){
			mvprintw(y,x,".");
		}
	}

	return 0;
}

Room *createRoom(int x, int y, int height, int width){
	Room *newRoom;
	newRoom = malloc(sizeof(Room));
	newRoom->position.x = x;
	newRoom->position.y = y;
	newRoom->width = width;
	newRoom->height = height;

	return newRoom;
}

Player *playerSetup(){
	Player *newPlayer;

	newPlayer = malloc(sizeof(Player));
	newPlayer->position.x = 14;
	newPlayer->position.y = 14;
	newPlayer->health = 20;

	playerMove(newPlayer->position.y,newPlayer->position.x, newPlayer);

	return newPlayer;
}

int handleInput(int ch, Player *player){

	int newY;
	int newX;

	ch = tolower(ch); // make input case insensitive

	switch(ch){
		case 'w':
			newY = player->position.y - 1;
			newX = player->position.x;
			break;
		case 'a':
			newY = player->position.y;
			newX = player->position.x - 1;
			break;
		case 's':
			newY = player->position.y + 1;
			newX = player->position.x;
			break;
		case 'd':
			newY = player->position.y;
			newX = player->position.x + 1;
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
			move(player->position.y, player->position.x);
			break;
	}

	return 0;
}

int playerMove(int y, int x, Player *player){
	mvprintw(player->position.y,player->position.x, ".");

	player->position.x = x;
	player->position.y = y;

	mvprintw(player->position.y,player->position.x, "@");
	move(player->position.y,player->position.x);

	return 0;
}
