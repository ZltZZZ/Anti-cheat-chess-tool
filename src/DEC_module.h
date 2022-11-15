#pragma once

#define MOVE_TIME_DEFUALT 1

#include "DataBase_parser.h"
#include "Engine_handler.h"
#include "Chessboard_handler.h"

/* ------------This is a module that unite all handlers in one synchronized working machine----------------------
   -----------------------called "DEC" - Database-Engine-Chessboard module.-------------------------------------- */

/* That is a struct that contains information about accuracy of suspected person,
   and other following information about range of research. */
typedef struct _suspect_portrait {
	parser prsr;

    /* Sum of accuracies for all possible sets of attribute (used to calculate the average accuracy after analysis)  */
	attr_container attr_acc;

	/* The count of attributes of each kind (used to calculate the average accuracy after analysis). */
	attr_container attr_count;
} suspect_portrait;

/* Return accuracy of move. THIS IS A MAIN ALGORINM OF ANALIZING. */
int analize_move(engine*, thc::ChessRules*, char* mv_next, std::string* fen_string);

/* Analize a game of a player, named NAME. */
void analize_game_player(game*, engine*, suspect_portrait*, char* name);

/* Get a move string from notation. Returns NULL, if this is was last move in notation. */
char* get_next_move_from_notation(char* notation, char* move_buff);

/* Ananlizes all games of choosed player. */
void do_analize_glob_player(parser*, engine*, suspect_portrait*);

/* Ananlizes all games that without name filter (analyze ONLY positions, that player played. */
void do_analize_glob_no_name(parser*, engine*, suspect_portrait*);

/* Ananlizes all games that without name filter (with full analize of game). */
void do_analize_glob(parser*, engine*, suspect_portrait*);

/* Main function, that calls from entry point. */
void do_analize(parser*, engine*, suspect_portrait*);

/* Compare next move of ENGINE with next move of Player. Returns a number, that correspondes to number of line. */
int get_accuracy_of_move(thc::Move*, engine_line*, int count_of_lines);

/* Fill accuracy of move in all sets of attr of suspect.*/
void fill_acc_in_attr_containers(attr_set* attr_st, suspect_portrait*, int accuracy);

