#pragma once

#include "DataBase_parser.h"
#include "Engine_handler.h"
#include "Chessboard_handler.h"

/* This is a module that unite all handlers in one synchronized working machine
   called "DEC" - Database-Engine-Chessboard module. */

/* That is a struct that contains information about accuracy of suspected person,
   and other following information about range of research. */
typedef struct _suspect_portrait {
	parser prsr;

    /* Sum of accuracies for all possible sets of attribute (used to calculate the average accuracy after analysis)  */
	attr_container attr_acc;

	/* The count of attributes of each kind (used to calculate the average accuracy after analysis). */
	attr_container attr_count;
} suspect_portrait;

/* Insert iformation about move in attr_acc and attr_count of suspect. THIS IS A MAIN ALGORINM OF ANALIZING. */
void analize_move(engine*, char* move, suspect_portrait*, thc::ChessRules*);

void do_analize_glob();

