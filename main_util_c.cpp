﻿//#define DEBUG_CHESSBOARD_HANDLER
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
    open_database();
#endif // DEBUG_DATABASE_PARSER


    return 0;
}