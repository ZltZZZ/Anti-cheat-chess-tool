#define MAX_P 9   /* Max count of figures on board + extra empty stot for empty attr. */
#define MAX_N 7
#define MAX_B 7
#define MAX_R 7
#define MAX_Q 7
#define EMPTY_P 9
#define EMPTY_N 7
#define EMPTY_B 7
#define EMPTY_R 7
#define EMPTY_Q 7


#define POSITION_ATTR_YES -15
#define POSITION_ATTR_NO  -16

#include "lib/thc.h"

enum _figure {
    PAWN = 0,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING
};

enum _color {
    WHITE = 0,
    BLACK
};

enum _move_components {
    FROM_LINE = 0,
    FROM_NUMBER,
    TO_LINE,
    TO_NUMBER,
    PROMOTION
};

enum _promotion_components {
    PROMOTION_BISHOP = 'b',
    PROMOTION_KNIGHT = 'n',
    PROMOTION_ROOK = 'r',
    PROMOTION_QUEEN = 'q'
};

/* Set of attributes for position. */
typedef struct _attr_set {
    int count_P;
    int count_B;
    int count_N;
    int count_R;
    int count_Q;
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

/* Set all field in attr_cont as 0. */
void zero_attr_cont(attr_container*);

/* Parse FEN string and gest set of attributes of this position. */
void get_attr_set(const char* fen_string, attr_set*);

/* Compare two attr_set. Returns 0 if equal, overwise != 0 */
int compare_attr_sets(attr_set* set_1, attr_set* set_2);

/* Copy contains from set_src to set_dst. */
void copy_attr_set(attr_set* set_dst, attr_set* set_src);

/* Make move on board. */
void make_move(thc::ChessRules*, char* move);

/* Sets start position on board. */
void set_start_position_on_board(thc::ChessRules*);