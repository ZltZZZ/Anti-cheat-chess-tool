#include "Chessboard_handler.h"
#include <string.h>

void init_attr_cont_acc(attr_container_acc* attr_cont, int count_pos) {
    malloc_attr_cont_acc(count_pos, attr_cont);
    attr_cont->count_pos = count_pos;

    for (int p = 0; p < MAX_P; p++) {
        for (int n = 0; n < MAX_N; n++) {
            for (int b = 0; b < MAX_B; b++) {
                for (int r = 0; r < MAX_R; r++) {
                    for (int q = 0; q < MAX_Q; q++) {
                        for (int c = 0; c < count_pos; c++) 
                            attr_cont->fl_cont[p][n][b][r][q][c] = POSITION_ATTR_EMPTY;
                    }
                }
            }
        }
    }
}

void init_attr_cont_count(attr_container_count* attr_cont) {
    for (int p = 0; p < MAX_P; p++) {
        for (int n = 0; n < MAX_N; n++) {
            for (int b = 0; b < MAX_B; b++) {
                for (int r = 0; r < MAX_R; r++) {
                    for (int q = 0; q < MAX_Q; q++) {
                        attr_cont->int_cont[p][n][b][r][q] = POSITION_ATTR_NO;
                    }
                }
            }
        }
    }
}

void init_attr_cont_with_other_cont_count(attr_container_count* dst, attr_container_count* src) {
    for (int p = 0; p < MAX_P; p++) {
        for (int n = 0; n < MAX_N; n++) {
            for (int b = 0; b < MAX_B; b++) {
                for (int r = 0; r < MAX_R; r++) {
                    for (int q = 0; q < MAX_Q; q++) {
                        if (src->int_cont[p][n][b][r][q] != POSITION_ATTR_NO) {
                            dst->int_cont[p][n][b][r][q] = POSITION_ATTR_YES;
                        }
                        else {
                            dst->int_cont[p][n][b][r][q] = POSITION_ATTR_NO;
                        }
                    }
                }
            }
        }
    }
}

/* Allocate memory for attr conteiner. */
void malloc_attr_cont_acc(int count_pos, attr_container_acc* attr_cont) {
    attr_cont->fl_cont = (float******)malloc(MAX_P * sizeof(float*****));
    if (attr_cont->fl_cont == NULL) {
        printf("Not enough memory\n");
        exit(-1);
    }

    for (int p = 0; p < MAX_P; p++) {
        attr_cont->fl_cont[p] = (float*****)malloc(MAX_N * sizeof(float****));
        if (attr_cont->fl_cont[p] == NULL) {
            printf("Not enough memory\n");
            exit(-1);
        }

        for (int n = 0; n < MAX_N; n++) {
            attr_cont->fl_cont[p][n] = (float****)malloc(MAX_B * sizeof(float***));
            if (attr_cont->fl_cont[p][n] == NULL) {
                printf("Not enough memory\n");
                exit(-1);
            }

            for (int b = 0; b < MAX_B; b++) {
                attr_cont->fl_cont[p][n][b] = (float***)malloc(MAX_R * sizeof(float**));
                if (attr_cont->fl_cont[p][n][b] == NULL) {
                    printf("Not enough memory\n");
                    exit(-1);
                }

                for (int r = 0; r < MAX_R; r++) {
                    attr_cont->fl_cont[p][n][b][r] = (float**)malloc(MAX_Q * sizeof(float*));
                    if (attr_cont->fl_cont[p][n][b][r] == NULL) {
                        printf("Not enough memory\n");
                        exit(-1);
                    }

                    for (int q = 0; q < MAX_Q; q++) {
                        attr_cont->fl_cont[p][n][b][r][q] = (float*)malloc(count_pos * sizeof(float));
                        if (attr_cont->fl_cont[p][n][b][r][q] == NULL) {
                            printf("Not enough memory\n");
                            exit(-1);
                        }
                    }
                }
            }
        }
    }
}

/* Free allocated attr conteiner*/
void free_attr_cont_acc(attr_container_acc* attr_cont) {
    for (int p = 0; p < MAX_P; p++) {
        for (int n = 0; n < MAX_N; n++) {
            for (int b = 0; b < MAX_B; b++) {
                for (int r = 0; r < MAX_R; r++) {
                    for (int q = 0; q < MAX_Q; q++) {
                        free(attr_cont->fl_cont[p][n][b][r][q]);
                    }

                    free(attr_cont->fl_cont[p][n][b][r]);
                }

                free(attr_cont->fl_cont[p][n][b]);
            }

            free(attr_cont->fl_cont[p][n]);
        }

        free(attr_cont->fl_cont[p]);
    }

    free(attr_cont->fl_cont);
}

void zero_attr_cont_count(attr_container_count* attr_cont_count) {
    memset(attr_cont_count->int_cont, 0, sizeof(int) * MAX_P * MAX_N * MAX_B * MAX_Q * MAX_R);
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

bool is_attr_set_in_attr_cont_count(attr_set* attr_st, attr_container_count* attr_cont) {
    if (attr_cont->int_cont[attr_st->count_P][attr_st->count_N][attr_st->count_B][attr_st->count_R][attr_st->count_Q] != POSITION_ATTR_NO) {
        return true;
    }
    else {
        return false;
    }
}

bool is_attr_set_count_pass_filter_count(attr_set* attr_st, attr_container_count* attr_cont, int max_count_of_moves) {
    if (attr_cont->int_cont[attr_st->count_P][attr_st->count_N][attr_st->count_B][attr_st->count_R][attr_st->count_Q] < max_count_of_moves) {
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