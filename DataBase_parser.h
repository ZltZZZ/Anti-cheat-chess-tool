#pragma once

/* That is parser. It gets information from PGN base.*/

#define MAX_NAME_SIZE 61
#define MAX_PATH_LENTH 256

#include <iostream> 
#include <fstream> 
#include <string>
#include <time.h>

/* Event. It is blitz, classic, bullet and other. */
typedef enum _eevent {
	BLITZ,
	BULLET,
	CLASSIC
} _event;

/* Contains information about parametrs of searching (filter of games)
   and database file stream. */
typedef struct _parser {
	struct _params {
		int elo_min;                // Elo rating left range
		int elo_max;				// Elo rating right range
		_event evnt;				// Type of game. Blitz, classic and other
		char name[MAX_NAME_SIZE];	// Name of player, or empty string if not a player
	}params;

	struct _db {
		char path_to_db[MAX_PATH_LENTH];
		std::ifstream pgn_db;
		std::string buff;
	}db;
} parser;

/* Contains information about curr game that is analizing*/
typedef struct _game {
	int avrg_elo;
	_event evnt;
	char name_white[MAX_NAME_SIZE];
	char name_black[MAX_NAME_SIZE];
	std::string moves;
} game;

/* Set paramets that will filter games. */
void set_search_params(parser*, 
					   int min_elo, 
	                   int max_elo, 
	                   _event evnt, 
	                   char* name,
	                   char* path_to_db);

/* Returns _game structure about next game in database. */
void get_next_game(parser*, game*);

/* Returns TRUE if end of database is reached, owerwise FALSE. */
bool is_end_of_db(parser*);

/* Opens file stream. */
void open_database(parser*);

/* Closes file stream. */
void close_database(parser*);
