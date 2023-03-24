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

#define POSITION_ATTR_YES -1
#define POSITION_ATTR_NO  0
#define POSITION_ATTR_EMPTY -2

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
typedef struct _attr_container_acc {
    float****** fl_cont;  // Used for displaying accuracies in float
    int count_pos;        // Size of massive
} attr_container_acc;

typedef struct _attr_container_count {
    int int_cont[MAX_P][MAX_N][MAX_B][MAX_R][MAX_Q];   // Used for summing accurasies in int
} attr_container_count;

/* Allocate memory for attr conteiner. */
void malloc_attr_cont_acc(int count_pos, attr_container_acc* attr_cont);

/* Free allocated attr conteiner*/
void free_attr_cont_acc(attr_container_acc* attr_cont);

/* Set all fields in attr_cont_acc with 0. */
void init_attr_cont_acc(attr_container_acc*, int count_pos);

/* Set all fields in attr_cont_acc with POSITION_ATT_NO. */
void init_attr_cont_count(attr_container_count* attr_cont);

/* Run through scr container and if in field no POSITION_ATT_NO, then in dst field places POSITION_ATTR_YES. */
void init_attr_cont_with_other_cont_count(attr_container_count* dst, attr_container_count* src);

/* Set all field in attr_cont as 0. */
void zero_attr_cont_count(attr_container_count*);

/* Parse FEN string and gest set of attributes of this position. */
void get_attr_set(const char* fen_string, attr_set*);

/* Compare two attr_set. Returns 0 if equal, overwise != 0 */
int compare_attr_sets(attr_set* set_1, attr_set* set_2);

/* Copy contains from set_src to set_dst. */
void copy_attr_set(attr_set* set_dst, attr_set* set_src);

/* Returns TRUE, if attr_set is in attr_cont. Overwise returns FALSE. */
bool is_attr_set_in_attr_cont_count(attr_set*, attr_container_count*);

/* Returns TRUE is count of attr_set in attr_cont less or equal, than max_count_of_moves. Overwise FALSE.*/
bool is_attr_set_count_pass_filter_count(attr_set*, attr_container_count*, int max_count_of_moves);

/* Make move on board. */
void make_move(thc::ChessRules*, char* move);

/* Sets start position on board. */
void set_start_position_on_board(thc::ChessRules*);