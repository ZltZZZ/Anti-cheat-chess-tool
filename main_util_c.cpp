//#define DEBUG_CHESSBOARD_HANDLER
//#define DEBUG_ENGINE_HANDLER
//#define DEBUG_DATABASE_PARSER

#include <stdio.h>
#include "Chessboard_handler.h"
#include "Engine_handler.h"
#include "DataBase_parser.h"

int main()
{
    char chessboard[MAX_NUMBER_OF_FIGURES_OF_EACH_KIND][MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER] = { NULL_VALUE };
    char move[MAX_MOVE_LENTH_LAN] = { NULL_VALUE };

#ifdef DEBUG_CHESSBOARD_HANDLER
    initialize_start_position_on_board(chessboard);
    
    move[0] = 'c';
    move[1] = '1';
    move[2] = 'e';
    move[3] = '5';
    move[4] = 'X';
    update_position_on_board(chessboard, move);

    move[0] = 'e';
    move[1] = '1';
    move[2] = 'c';
    move[3] = '1';
    move[4] = 'X';
    update_position_on_board(chessboard, move);

    /*move[0] = 'f';
    move[1] = '7';
    move[2] = 'f';
    move[3] = '6';
    move[4] = 'X';
    update_position_on_board(chessboard, move);

    move[0] = 'e';
    move[1] = '4';
    move[2] = 'e';
    move[3] = '5';
    move[4] = 'X';
    update_position_on_board(chessboard, move);

    move[0] = 'd';
    move[1] = '7';
    move[2] = 'd';
    move[3] = '5';
    move[4] = 'X';
    update_position_on_board(chessboard, move);

    move[0] = 'e';
    move[1] = '5';
    move[2] = 'd';
    move[3] = '6';
    move[4] = 'X';
    update_position_on_board(chessboard, move);*/

#endif

#ifdef DEBUG_ENGINE_HANDLER
    engine test_engine;
    char buff_out[MAX_MSG_SIZE] = { '\0' };

    init_engine_struct(&test_engine, L"D:\\VUZAKA\\case\\Programm\\stockfish_15_win_x64_popcnt\\stockfish_15_x64_popcnt.exe");
    if (engine_load(&test_engine) == ENGINE_LOAD_OK) {
        printf("Engine OK\n");

        engine_send_command(&test_engine, COMMAND_TYPE_GET_ANSW, IS_READY, buff_out);
        printf("Engine aswers: %s", buff_out);
        
    }
    else {
        printf("Engine FAIL\n");
    }

    engine_close(&test_engine);
#endif // DEBUG_ENGINE_HANDLER

#ifdef DEBUG_DATABASE_PARSER
    parser prsr;
    game gm;
    char db_path[] = "lichess_db_standard_rated_2013-05(4).pgn";
    int count_games = 0;

    set_parser_params(&prsr, NO_RATING, NO_RATING, EVENT_BLITZ, NULL, db_path);
    open_database(&prsr);

    while (get_next_game(&prsr, &gm) != DB_EOF)
    {
        if (gm.evnt == EVENT_BLITZ) {
            printf("Event : Blitz\n");
        }
        printf(
            "White: %s\n"
            "Black: %s\n"
            "ELO Black: %d\n"
            "Elo White: %d\n"
            "Moves: %s\n",
            gm.name_white, gm.name_black, gm.elo_black, gm.elo_white, gm.moves);
        printf("\n");

        count_games++;
    }

    printf("Total count of games: %d\n", count_games);

    close_database(&prsr);
#endif // DEBUG_DATABASE_PARSER


    return 0;
}
