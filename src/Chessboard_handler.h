#pragma once

#define MAX_P 18  /* Max count of figures on board + extra empty stot for empty attr. */
#define MAX_N 7
#define MAX_B 7
#define MAX_R 7
#define MAX_Q 7
#define EMPTY_P 17
#define EMPTY_N 6
#define EMPTY_B 6
#define EMPTY_R 6
#define EMPTY_Q 6

#define POSITION_ATTR_YES -15
#define POSITION_ATTR_NO  -16

#define WHITE_SIDE 1
#define BLACK_SIDE 0

#include "../../Anti-cheat-chess-tool/lib/thc.h"

/* Set of attributes for position. */
typedef struct _attr_set {
    int count_P;            // Count of Pawns on board.
    int count_B;            // Count of Bishops on board.
    int count_N;            // Count of Knights on board
    int count_R;            // Count of Rooks on board.
    int count_Q;            // Count of Queens on board.
} attr_set;

/* Contains all possible combinations of attributes of position. Used to assign some number to a specific set of attributes. */
typedef struct _attr_container {
    // You can use int or float container as you want
    union _cont
    {
        float fl_cont[MAX_P][MAX_N][MAX_B][MAX_R][MAX_Q];  // Used for displaying accyracies in float
        int int_cont[MAX_P][MAX_N][MAX_B][MAX_R][MAX_Q];   // Used for summing accyrasies int int
    } cont;
} attr_container;

/* Set all fields in attr_cont as POSITION_ATTR_NO. */
void init_attr_cont(attr_container*);

/* Run through scr container and if in field no POSITION_ATT_NO, then in dst field places POSITION_ATTR_YES. */
void init_attr_cont_with_other_cont(attr_container* dst, attr_container* src);

/* Set all field in attr_cont as 0. */
void zero_attr_cont(attr_container*);

/* Parse FEN string and gest set of attributes of this position. */
void get_attr_set(const char* fen_string, attr_set*);

/* Compare two attr_set. Returns 0 if equal, overwise != 0 */
int compare_attr_sets(attr_set* set_1, attr_set* set_2);

/* Copy contains from set_src to set_dst. */
void copy_attr_set(attr_set* set_dst, attr_set* set_src);

/* Returns TRUE, if attr_set is in attr_cont. Overwise returns FALSE. */
bool is_attr_set_in_attr_cont(attr_set*, attr_container*);

/* Returns TRUE is count of attr_set in attr_cont less or equal, than max_count_of_moves. Overwise FALSE.*/
bool is_attr_set_count_pass_filter(attr_set*, attr_container*, int max_count_of_moves);

/* Make move on board. */
void make_move(thc::ChessRules*, char* move);

/* Sets start position on board. */
void set_start_position_on_board(thc::ChessRules*);