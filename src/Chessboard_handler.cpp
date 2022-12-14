#include "Chessboard_handler.h"
#include <string.h>

void init_attr_cont(attr_container* attr_cont) {
    for (int p = 0; p < MAX_P; p++) {
        for (int n = 0; n < MAX_N; n++) {
            for (int b = 0; b < MAX_B; b++) {
                for (int r = 0; r < MAX_R; r++) {
                    for (int q = 0; q < MAX_Q; q++) {
                        attr_cont->cont.int_cont[p][n][b][r][q] = POSITION_ATTR_NO;
                    }
                }
            }
        }
    }
}

void init_attr_cont_with_other_cont(attr_container* dst, attr_container* src) {
    for (int p = 0; p < MAX_P; p++) {
        for (int n = 0; n < MAX_N; n++) {
            for (int b = 0; b < MAX_B; b++) {
                for (int r = 0; r < MAX_R; r++) {
                    for (int q = 0; q < MAX_Q; q++) {
                        if (src->cont.int_cont[p][n][b][r][q] != POSITION_ATTR_NO) {
                            dst->cont.int_cont[p][n][b][r][q] = POSITION_ATTR_YES;
                        }
                        else {
                            dst->cont.int_cont[p][n][b][r][q] = POSITION_ATTR_NO;;
                        }
                    }
                }
            }
        }
    }
}

void zero_attr_cont(attr_container* attr_cont) {
    memset(attr_cont->cont.int_cont, 0, sizeof(int) * MAX_P * MAX_N * MAX_B * MAX_Q * MAX_R);
}

void get_attr_set(const char* fen_string, attr_set* attr_st) {
    int len = strlen(fen_string);

    memset(attr_st, 0, sizeof(attr_set));
    for (int i = 0; i < len; i++) {
        if (fen_string[i] == ' ') break;

        // Parse string of kind: "x/x/x/x/x/x/x/x", where 'x' is set of figures and(or) numbers. Example: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR".
        if (fen_string[i] == 'p' || fen_string[i] == 'P') {
            attr_st->count_P++;
        }
        else if (fen_string[i] == 'n' || fen_string[i] == 'N') {
            attr_st->count_N++;
        }
        else if (fen_string[i] == 'b' || fen_string[i] == 'B') {
            attr_st->count_B++;
        }
        else if (fen_string[i] == 'r' || fen_string[i] == 'R') {
            attr_st->count_R++;
        }
        else if (fen_string[i] == 'q' || fen_string[i] == 'Q') {
            attr_st->count_Q++;
        }
    }
}

int compare_attr_sets(attr_set* set_1, attr_set* set_2) {
    return memcmp(set_1, set_2, sizeof(attr_set));
}

void copy_attr_set(attr_set* set_dst, attr_set* set_src) {
    memcpy(set_dst, set_src, sizeof(attr_set));
}

bool is_attr_set_in_attr_cont(attr_set* attr_st, attr_container* attr_cont) {
    if (attr_cont->cont.int_cont[attr_st->count_P][attr_st->count_N][attr_st->count_B][attr_st->count_R][attr_st->count_Q] != POSITION_ATTR_NO) {
        return true;
    }
    else {
        return false;
    }
}

bool is_attr_set_count_pass_filter(attr_set* attr_st, attr_container* attr_cont, int max_count_of_moves) {
    if (attr_cont->cont.int_cont[attr_st->count_P][attr_st->count_N][attr_st->count_B][attr_st->count_R][attr_st->count_Q] < max_count_of_moves) {
        return true;
    }
    else {
        return false;
    }
}

void make_move(thc::ChessRules* cr, char* move) {
    thc::Move mv;
    mv.NaturalIn(cr, move);

    cr->PlayMove(mv);
}

void set_start_position_on_board(thc::ChessRules* cr) {
    cr->Init();
}
