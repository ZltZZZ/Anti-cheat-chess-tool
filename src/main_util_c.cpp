//#define DEBUG_CHESSBOARD_HANDLER
//#define DEBUG_ENGINE_HANDLER
//#define DEBUG_DATABASE_PARSER

#include <stdio.h>
#include "Chessboard_handler.h"
#include "Engine_handler.h"
#include "DataBase_parser.h"

int main()
{
#ifdef DEBUG_CHESSBOARD_HANDLER
    
#endif

#ifdef DEBUG_ENGINE_HANDLER
    engine test_engine;
    char buff_out[MAX_MSG_SIZE] = { '\0' };
    engine_line line[OPTION_MULTI_PV_DEF];
    time_t time_start, time_curr;

    init_engine_struct(&test_engine, L"D:\\VUZAKA\\case\\Programm\\stockfish_15_win_x64_popcnt\\stockfish_15_x64_popcnt.exe");
    if (engine_load(&test_engine) == ENGINE_LOAD_OK) {
        printf("Engine OK\n");

        engine_set_position(&test_engine, (char*)"rn1qk1nr/pp3ppp/4p3/2bpPb2/8/2P2N2/PP2BPPP/RNBQK2R b KQkq - 0 1");
        engine_send_command_start_analyze(&test_engine, 1);

        time(&time_start);
        time(&time_curr);
        engine_parse_analisys_output(&test_engine, line);
        time(&time_curr);

        for (int i = 0; i < OPTION_MULTI_PV_DEF; i++) {
            printf("line %d, move: %s\n", i, line[i].move);
        }
        printf("time: %f\n", difftime(time_curr, time_start));
    }
    else {
        printf("Engine FAIL\n");
    }

    engine_close(&test_engine);
#endif // DEBUG_ENGINE_HANDLER

#ifdef DEBUG_DATABASE_PARSER
    parser prsr;
    game gm;
    char db_path[] = "lichess_db_standard_rated_2013-05(1).pgn";
    int count_games = 0;
    char name[] = "mhs1371";

    set_parser_params(&prsr, NO_RATING, NO_RATING, EVENT_BLITZ, name, db_path);
    open_database(&prsr);

    while (get_next_game(&prsr, &gm) != DB_EOF)
    {
        /*if (gm.evnt == EVENT_BLITZ) {
            printf("Event : Blitz\n");
        }
        printf(
            "White: %s\n"
            "Black: %s\n"
            "ELO Black: %d\n"
            "Elo White: %d\n"
            "Moves: %s\n",
            gm.name_white, gm.name_black, gm.elo_black, gm.elo_white, gm.moves);
        printf("\n");*/

        count_games++;
    }

    printf("Total count of games: %d\n", count_games);

    close_database(&prsr);
#endif // DEBUG_DATABASE_PARSER


    return 0;
}
