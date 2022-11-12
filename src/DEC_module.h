#pragma once

#define MAX_P 9   /* Max count of figures on board + extra empty stot for statistics*/
#define MAX_N 7
#define MAX_B 7
#define MAX_R 7
#define MAX_Q 7

#include "DataBase_parser.h"
#include "Engine_handler.h"
#include "Chessboard_handler.h"

/* This is a module that unite all handlers in one synchronized working machine
   called "DEC" - Database-Engine-Chessboard module. */

/* That is a struct that contains information about accuracy of suspected person,
   and other following information about range of research. */
typedef struct _suspect_portrait {
	parser prsr;

    /* Avarage accuracy for all possible sets of attributes. */
	float attr_acc[MAX_P][MAX_N][MAX_B][MAX_R][MAX_Q];

	/* The number of attribute sets encountered (used to calculate the average accuracy after analysis). */
	float attr_acc[MAX_P][MAX_N][MAX_B][MAX_R][MAX_Q];
} suspect_portrait;

