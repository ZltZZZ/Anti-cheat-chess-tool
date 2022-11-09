#define MAX_NUMBER_OF_FIGURES_OF_EACH_KIND 6
#define MAX_NUMBER_OF_FIGURES_ON_BOARD 8
#define MAX_NUMBER_OF_COLORS 2
#define MULTIPLIER_VERT_NAME_HORIZ_NUMBER 2
#define NULL_VALUE 'X'
#define MAX_MOVE_LENTH_LAN 5
#define VERT_LINE 0
#define HORIZ_NUMBER 1 

#include <iostream>

using namespace std;

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
void initialize_start_position_on_board(char (*)[MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER]);

/* Update positions of figures after each move */
void update_position_on_board(char(*)[MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER], char*);

/* Returns a figure that was written in notation (doesn't matter lower or upper case) */
enum _figure get_figure_from_char(char);

/* Shift all figures to the left after removing figure from board ("e1 XX d4 g4 XX ... XX" --> "e1 d4 g4 XX ... XX)"*/
void shift_coordinates_after_removing_figure(char*);

int main()
{
    char chessboard[MAX_NUMBER_OF_FIGURES_OF_EACH_KIND][MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER] = { NULL_VALUE };
    char move[MAX_MOVE_LENTH_LAN] = { NULL_VALUE };

    initialize_start_position_on_board(chessboard);
}

void initialize_start_position_on_board(char (*chessboard)[MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER]) {
    /*--------------------------- PAWNS ---------------------------------*/
    // White side
    chessboard[PAWN][WHITE][0] = 'a';   chessboard[PAWN][WHITE][1] = '2';
    chessboard[PAWN][WHITE][2] = 'b';   chessboard[PAWN][WHITE][3] = '2';
    chessboard[PAWN][WHITE][4] = 'c';   chessboard[PAWN][WHITE][5] = '2';
    chessboard[PAWN][WHITE][6] = 'd';   chessboard[PAWN][WHITE][7] = '2';
    chessboard[PAWN][WHITE][8] = 'e';   chessboard[PAWN][WHITE][9] = '2';
    chessboard[PAWN][WHITE][10] = 'f';   chessboard[PAWN][WHITE][11] = '2';
    chessboard[PAWN][WHITE][12] = 'g';   chessboard[PAWN][WHITE][13] = '2';
    chessboard[PAWN][WHITE][14] = 'h';   chessboard[PAWN][WHITE][15] = '2';
    // Black side
    chessboard[PAWN][BLACK][0] = 'a';   chessboard[PAWN][BLACK][1] = '7';
    chessboard[PAWN][BLACK][2] = 'b';   chessboard[PAWN][BLACK][3] = '7';
    chessboard[PAWN][BLACK][4] = 'c';   chessboard[PAWN][BLACK][5] = '7';
    chessboard[PAWN][BLACK][6] = 'd';   chessboard[PAWN][BLACK][7] = '7';
    chessboard[PAWN][BLACK][8] = 'e';   chessboard[PAWN][BLACK][9] = '7';
    chessboard[PAWN][BLACK][10] = 'f';   chessboard[PAWN][BLACK][11] = '7';
    chessboard[PAWN][BLACK][12] = 'g';   chessboard[PAWN][BLACK][13] = '7';
    chessboard[PAWN][BLACK][14] = 'h';   chessboard[PAWN][BLACK][15] = '7';
    /*--------------------------------------------------------------------*/

     /*------------------------- BISHOPS ---------------------------------*/
    // White side
    chessboard[BISHOP][WHITE][0] = 'c';   chessboard[BISHOP][WHITE][1] = '1';
    chessboard[BISHOP][WHITE][2] = 'f';   chessboard[BISHOP][WHITE][3] = '1';
    // Black side
    chessboard[BISHOP][BLACK][0] = 'c';   chessboard[BISHOP][BLACK][1] = '8';
    chessboard[BISHOP][BLACK][2] = 'f';   chessboard[BISHOP][BLACK][3] = '8';
    /*--------------------------------------------------------------------*/

     /*------------------------- KNIGHTS ---------------------------------*/
    // White side
    chessboard[KNIGHT][WHITE][0] = 'b';   chessboard[KNIGHT][WHITE][1] = '1';
    chessboard[KNIGHT][WHITE][2] = 'g';   chessboard[KNIGHT][WHITE][3] = '1';
    // Black side
    chessboard[KNIGHT][BLACK][0] = 'b';   chessboard[KNIGHT][BLACK][1] = '8';
    chessboard[KNIGHT][BLACK][2] = 'g';   chessboard[KNIGHT][BLACK][3] = '8';
    /*--------------------------------------------------------------------*/

     /*--------------------------- ROOKS ---------------------------------*/
    // White side
    chessboard[ROOK][WHITE][0] = 'a';   chessboard[ROOK][WHITE][1] = '1';
    chessboard[ROOK][WHITE][2] = 'h';   chessboard[ROOK][WHITE][3] = '1';
    // Black side
    chessboard[ROOK][BLACK][0] = 'a';   chessboard[ROOK][BLACK][1] = '8';
    chessboard[ROOK][BLACK][2] = 'h';   chessboard[ROOK][BLACK][3] = '8';
    /*--------------------------------------------------------------------*/

    /*--------------------------- QUEENS ---------------------------------*/
    // White side
    chessboard[QUEEN][WHITE][0] = 'd';   chessboard[QUEEN][WHITE][1] = '1';
    // Black side
    chessboard[QUEEN][BLACK][0] = 'd';   chessboard[QUEEN][BLACK][1] = '8';
    /*--------------------------------------------------------------------*/

    /*--------------------------- KINGS ---------------------------------*/
    // White side
    chessboard[KING][WHITE][0] = 'e';   chessboard[KING][WHITE][1] = '1';
    // Black side
    chessboard[KING][BLACK][0] = 'e';   chessboard[KING][BLACK][1] = '8';
    /*--------------------------------------------------------------------*/
}

void update_position_on_board(char (*chessboard)[MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER], char* move) {
    enum _figure figure_that_moved;
    enum _color color_of_figure_that_moved;
    int number_of_figure_that_moved;
    bool stop_flag = false,
         move_from_found = false,
         move_to_found = false;
    
    if (move[PROMOTION] != NULL_VALUE) {
        /* Promote a pawn to figure. First delete pawn, then place figure on board. */
        for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
            // Finds pawn that is promoted and remove it from board
            if (chessboard[PAWN][WHITE][number_of_figure + VERT_LINE] == move[FROM_LINE] &&
                chessboard[PAWN][WHITE][number_of_figure + HORIZ_NUMBER] == move[FROM_NUMBER]) {
                chessboard[PAWN][WHITE][number_of_figure + VERT_LINE] = NULL_VALUE;
                chessboard[PAWN][WHITE][number_of_figure + HORIZ_NUMBER] = NULL_VALUE;
                color_of_figure_that_moved = WHITE;
                shift_coordinates_after_removing_figure(chessboard[PAWN][WHITE]);
                break;
            }
            if (chessboard[PAWN][BLACK][number_of_figure + VERT_LINE] == move[FROM_LINE] &&
                chessboard[PAWN][BLACK][number_of_figure + HORIZ_NUMBER] == move[FROM_NUMBER]) {
                chessboard[PAWN][BLACK][number_of_figure + VERT_LINE] = NULL_VALUE;
                chessboard[PAWN][BLACK][number_of_figure + HORIZ_NUMBER] = NULL_VALUE;
                color_of_figure_that_moved = BLACK;
                shift_coordinates_after_removing_figure(chessboard[PAWN][BLACK]);
                break;
            }
        }

        // Finds a place in board with XX and places a figure there. 
        figure_that_moved = get_figure_from_char(move[PROMOTION]);
        for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
            if (chessboard[figure_that_moved][color_of_figure_that_moved][number_of_figure + VERT_LINE] == NULL_VALUE) {
                chessboard[figure_that_moved][color_of_figure_that_moved][number_of_figure + VERT_LINE] = move[TO_LINE];
                chessboard[figure_that_moved][color_of_figure_that_moved][number_of_figure + HORIZ_NUMBER] = move[TO_NUMBER];
                break;
            }
        }
    }
    else {
        /* Finds figure that is moving, figure that is captured or establish that nothing is captured.
       Immidietly update board, if something is captured. */
        for (int figure = PAWN; !stop_flag && figure < MAX_NUMBER_OF_FIGURES_OF_EACH_KIND; figure++) {
            for (int color = WHITE; !stop_flag && color < MAX_NUMBER_OF_COLORS; color++) {
                for (int number_of_figure = 0; !stop_flag && number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
                    if (chessboard[figure][color][number_of_figure + VERT_LINE] == NULL_VALUE) {
                        break;
                    }

                    // Update state of figure, that is captured or nothing captured.
                    if (move_to_found == false &&
                        chessboard[figure][color][number_of_figure + VERT_LINE] == move[TO_LINE] &&
                        chessboard[figure][color][number_of_figure + HORIZ_NUMBER] == move[TO_NUMBER]) {
                        chessboard[figure][color][number_of_figure + VERT_LINE] = NULL_VALUE;
                        chessboard[figure][color][number_of_figure + HORIZ_NUMBER] = NULL_VALUE;
                        shift_coordinates_after_removing_figure(chessboard[figure][color]);

                        move_to_found = true;
                        if (move_from_found) {
                            chessboard[figure_that_moved][color_of_figure_that_moved][number_of_figure_that_moved + VERT_LINE] = move[TO_LINE];
                            chessboard[figure_that_moved][color_of_figure_that_moved][number_of_figure_that_moved + HORIZ_NUMBER] = move[TO_NUMBER];
                            stop_flag = true;
                        }
                    }

                    // Update state of figure, that is moving.
                    if (move_from_found == false &&
                        chessboard[figure][color][number_of_figure + VERT_LINE] == move[FROM_LINE] &&
                        chessboard[figure][color][number_of_figure + HORIZ_NUMBER] == move[FROM_NUMBER]) {
                        figure_that_moved = (_figure)figure;
                        color_of_figure_that_moved = (_color)color;
                        number_of_figure_that_moved = number_of_figure;

                        move_from_found = true;
                        if (move_to_found) {
                            chessboard[figure][color][number_of_figure + VERT_LINE] = move[TO_LINE];
                            chessboard[figure][color][number_of_figure + HORIZ_NUMBER] = move[TO_NUMBER];
                            stop_flag = true;
                        }
                    }
                }
            }
        }

        if (move_to_found == false) {
            /* Check if it is a castling */
            if (figure_that_moved == KING &&
                move[FROM_LINE] == 'e' && move[TO_LINE] == 'g' || move[TO_LINE] == 'c') {
                // Replace rook that is castled
                if (move[TO_LINE] == 'g') { // Short castling (O-O)
                    if (color_of_figure_that_moved == WHITE) {
                        for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
                            // Replace white rook from h1 to f1
                            if (chessboard[ROOK][WHITE][number_of_figure + VERT_LINE] == 'h' &&
                                chessboard[ROOK][WHITE][number_of_figure + HORIZ_NUMBER] == '1') {
                                chessboard[ROOK][WHITE][number_of_figure + VERT_LINE] = 'f';
                                chessboard[ROOK][WHITE][number_of_figure + HORIZ_NUMBER] = '1';
                                break;
                            }
                        }
                    }
                    else {
                        for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
                            // Replace white rook from h8 to f8
                            if (chessboard[ROOK][BLACK][number_of_figure + VERT_LINE] == 'h' &&
                                chessboard[ROOK][BLACK][number_of_figure + HORIZ_NUMBER] == '8') {
                                chessboard[ROOK][BLACK][number_of_figure + VERT_LINE] = 'f';
                                chessboard[ROOK][BLACK][number_of_figure + HORIZ_NUMBER] = '8';
                                break;
                            }
                        }
                    }
                }
                else { // Long castling (O-O-O)
                    if (color_of_figure_that_moved == WHITE) {
                        for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
                            // Replace white rook from a1 to d1
                            if (chessboard[ROOK][WHITE][number_of_figure + VERT_LINE] == 'a' &&
                                chessboard[ROOK][WHITE][number_of_figure + HORIZ_NUMBER] == '1') {
                                chessboard[ROOK][WHITE][number_of_figure + VERT_LINE] = 'd';
                                chessboard[ROOK][WHITE][number_of_figure + HORIZ_NUMBER] = '1';
                                break;
                            }
                        }
                    }
                    else {
                        for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
                            // Replace white rook from a8 to d8
                            if (chessboard[ROOK][BLACK][number_of_figure + VERT_LINE] == 'a' &&
                                chessboard[ROOK][BLACK][number_of_figure + HORIZ_NUMBER] == '8') {
                                chessboard[ROOK][BLACK][number_of_figure + VERT_LINE] = 'd';
                                chessboard[ROOK][BLACK][number_of_figure + HORIZ_NUMBER] = '8';
                                break;
                            }
                        }
                    }
                }
            }

            /* Check if it is taking on the pass */
            if (figure_that_moved == PAWN && move[TO_LINE] != move[FROM_LINE]) {
                if (color_of_figure_that_moved == WHITE) {
                    for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
                        if (chessboard[PAWN][WHITE][number_of_figure + VERT_LINE] == move[TO_LINE] &&
                            chessboard[PAWN][WHITE][number_of_figure + HORIZ_NUMBER] == move[TO_NUMBER] - 1) {
                            chessboard[PAWN][WHITE][number_of_figure + VERT_LINE] = NULL_VALUE;
                            chessboard[PAWN][WHITE][number_of_figure + HORIZ_NUMBER] = NULL_VALUE;
                            shift_coordinates_after_removing_figure(chessboard[PAWN][WHITE]);
                            break;
                        }
                    }
                }
                else {
                    for (int number_of_figure = 0; number_of_figure < MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER; number_of_figure += 2) {
                        if (chessboard[PAWN][BLACK][number_of_figure + VERT_LINE] == move[TO_LINE] &&
                            chessboard[PAWN][BLACK][number_of_figure + HORIZ_NUMBER] == move[TO_NUMBER] + 1) {
                            chessboard[PAWN][BLACK][number_of_figure + VERT_LINE] = NULL_VALUE;
                            chessboard[PAWN][BLACK][number_of_figure + HORIZ_NUMBER] = NULL_VALUE;
                            shift_coordinates_after_removing_figure(chessboard[PAWN][BLACK]);
                            break;
                        }
                    }
                }
            }

            // Dont forget about figure that is moving
            chessboard[figure_that_moved][color_of_figure_that_moved][number_of_figure_that_moved + VERT_LINE] = move[TO_LINE];
            chessboard[figure_that_moved][color_of_figure_that_moved][number_of_figure_that_moved + HORIZ_NUMBER] = move[TO_NUMBER];
        }
    }
    
}

enum _figure get_figure_from_char(char c) {
    if (c == 'q' || c == 'Q') {
        return QUEEN;
    }
    if (c == 'k' || c == 'K') {
        return KING;
    }
    if (c == 'r' || c == 'R') {
        return ROOK;
    }
    if (c == 'b' || c == 'B') {
        return BISHOP;
    }

        return KNIGHT;
}

void shift_coordinates_after_removing_figure(char* string_with_coors) {
    for (int i = 0; i < MAX_NUMBER_OF_FIGURES_OF_EACH_KIND * MULTIPLIER_VERT_NAME_HORIZ_NUMBER - 2; i++) {
        if (string_with_coors[i] == NULL_VALUE) {
            for (; i < MAX_NUMBER_OF_FIGURES_OF_EACH_KIND * MULTIPLIER_VERT_NAME_HORIZ_NUMBER - 2 && string_with_coors[i] != NULL_VALUE; i += 2) {
                string_with_coors[i] = string_with_coors[i + 2];
                string_with_coors[i + 1] = string_with_coors[i + 3];

                if (string_with_coors[i] == NULL_VALUE) {
                    break;
                }
            }

            string_with_coors[i] = NULL_VALUE;
            string_with_coors[i + 1] = NULL_VALUE;

            break;
        }
    }
}