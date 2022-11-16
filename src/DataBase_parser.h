#pragma once

/* That is parser. It gets information from PGN base.*/

#define MAX_NAME_SIZE 61
#define MAX_PATH_LENTH 256
#define MAX_BUFF_SIZE 3072
#define NO_RATING -1
#define DB_SUCCESS 1
#define DB_EOF 0

#include <iostream> 
#include <fstream> 
#include <string>
#include <time.h>

/* Event. It is blitz, classic, bullet and other. */
typedef enum _eevent {
	EVENT_BLITZ,
	EVENT_BULLET,
	EVENT_CLASSIC,
	EVENT_UNDEFINED
} _event;

typedef enum _tag{
	TAG_EVENT,
	TAG_WHITE,
	TAG_BLACK,
	TAG_WHITE_ELO,
	TAG_BLACK_ELO,
	TAG_UNDEFINED
} tag;

/* Contains information about parametrs of searching (filter of games)
   and database file stream. */
typedef struct _parser {
	struct _filter {
		int elo_min;                // Elo rating left range. Set NO_RATING if no filter for ratings.
		int elo_max;				// Elo rating right range. Set NO_RATING if no filter for ratings.
		_event evnt;				// Type of a game. Blitz, classic and other. Set UNDEFINED_EVENT if no filter for event.
		char name[MAX_NAME_SIZE];	// Name of a player, or empty string if not a player. Now, it is an obligatory argument, but later it can be set as an empty string
		int max_count_of_sets;      // After analysing player, analyse attr_sets that was in player analisys, NO MORE than max_count_of_sets. 
		int max_count_of_games;     // Analyse no more than max_count_of_games
	}fiter;

	struct _db {
		char path_to_db[MAX_PATH_LENTH];
		FILE* pgn_db;
		char buff[MAX_BUFF_SIZE];
	}db;
} parser;

/* Contains information about curr game that is analizing*/
typedef struct _game {
	int elo_black;
	int elo_white;
	_event evnt;
	char name_white[MAX_NAME_SIZE];
	char name_black[MAX_NAME_SIZE];
	char moves[MAX_BUFF_SIZE];
} game;

/* Set paramets that will filter games. */
void set_parser_params(parser*, 
					   int min_elo,         
	                   int max_elo, 
	                   _event evnt, 
	                   char* name,
	                   char* path_to_db,
	                   int max_count_of_sets,
                       int max_count_of_games);

/* Null all fields in structure _game. */
void game_clear(game*);

/* Returns _game structure about next game in database. */
int get_next_game(parser*, game*);

/* Opens file stream. */
void open_database(parser*);

/* Closes file stream. */
void close_database(parser*);

/* Gets name of tag. It can be Event, Result, Black_elo and others */
tag get_tag_name(char* buff);

/* Gets value of tag. It can be number or string (name). Returns pointer to first letter of value ("). */
char* get_tag_value(char* buff);

/* Fill information about tag in _game structure. */
void fill_tag_in_game(game*, tag, char* value_ptr);

/* Compairs filter params of parser with game params and returns FALSE if not equal, overwise TRUE. */
bool check_filter(parser*, game*);

/* Parse a string of moves. Delete all comments, odd numbers, dots and other useless stuff. White correct moves in _game structure*/
void move_parser(game*, char* buff);
