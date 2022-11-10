#define MAX_NUMBER_OF_FIGURES_OF_EACH_KIND 6
#define MAX_NUMBER_OF_FIGURES_ON_BOARD 8
#define MAX_NUMBER_OF_COLORS 2
#define MULTIPLIER_VERT_NAME_HORIZ_NUMBER 2
#define NULL_VALUE 'X'
#define MAX_MOVE_LENTH_LAN 5
#define VERT_LINE 0
#define HORIZ_NUMBER 1 

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

/* Places figures on start positions */
void initialize_start_position_on_board(char(*chessboard_ptr)[MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER]);

/* Update positions of figures after each move */
void update_position_on_board(char(*chessboard_ptr)[MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER], char* move_ptr);

/* Returns a figure that was written in notation (doesn't matter lower or upper case) */
enum _figure get_figure_from_char(char char_in_notation);