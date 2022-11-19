//#define DEBUG_CHESSBOARD_HANDLER
//#define DEBUG_ENGINE_HANDLER
//#define DEBUG_DATABASE_PARSER
#define DEBUG_DEC_MODULE
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Chessboard_handler.h"
#include "Engine_handler.h"
#include "DataBase_parser.h"
#include "DEC_module.h"

void get_input(char*, int size);

wchar_t* GetWC(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}

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

#ifdef DEBUG_DEC_MODULE
    engine engn;
    parser prsr;
    suspect_portrait player;
    suspect_portrait same_rating;
    char db_path[MAX_PATH_LENTH] = { '\0' };
    wchar_t* engn_path_w = NULL;
    char engn_path[MAX_PATH_LENTH] = { '\0' };
    char name[MAX_NAME_SIZE] = { '\0' };
    time_t time_start, time_curr;
    char command[MAX_NAME_SIZE] = { '\0' };
    int number = 0;
    int elo_min = 0, elo_max = 0,
        count_movs = 0, count_gams = 0;
    _event evnt = EVENT_BLITZ;

    printf("**********----------------------------**********\n"
        "------------Anti-Cheat-Chess-Analyzer--------------\n"
        "**********-------_P__Q__R__N__B_------********** \n");

    printf("\nEnter path to database (.pgn):\n");
    get_input(db_path, MAX_PATH_LENTH);

    printf("\nEnter name/nick-name of player (suspect):\n");
    get_input(name, MAX_NAME_SIZE);

    printf("\nEnter path to engine (.exe):\n");
    get_input(engn_path, MAX_PATH_LENTH); 
    engn_path_w = GetWC(engn_path);
    init_engine_struct(&engn, engn_path_w);

    printf("\nEngine: Enter count of CPU threads (2 or 4 or 6 or 8...). Type \"def\" to use default value(2) :\n");
    get_input(command, MAX_NAME_SIZE);
    if (strstr(command, "def") == NULL) {
        engn.cpu = atoi(command);
    }

    printf("\nEngine: Enter max count of lines to analyse (1 or 2 or 3 or 4). Type \"def\" to use default value(4) :\n");
    get_input(command, MAX_NAME_SIZE);
    if (strstr(command, "def") == NULL) {
        engn.multi_pv = atoi(command);
    }

    printf("\nEngine: Enter hash size (MB). Type \"def\" to use default value(1012) :\n");
    get_input(command, MAX_NAME_SIZE);
    if (strstr(command, "def") == NULL) {
        engn.hash = atoi(command);
    }

    printf("\nEngine: move time in sec. (how many sec engine will think for 1 move). Type \"def\" to use default value(1) :\n");
    get_input(command, MAX_NAME_SIZE);
    if (strstr(command, "def") == NULL) {
        engn.move_time = atoi(command);
    }

    printf("\nSearch (filter): type of games. Type 0 to search all Blitz games, 1 - Bullet games, 2 - Classical games, 4 - all types :\n");
    get_input(command, MAX_NAME_SIZE);
    evnt = (_event)atoi(command);

    printf("\nSearch (filter): min rating. Type -1 - all ratings :\n");
    get_input(command, MAX_NAME_SIZE);
    elo_min = atoi(command);

    printf("\nSearch (filter): max rating. Type -1 - all ratings :\n");
    get_input(command, MAX_NAME_SIZE);
    elo_max = atoi(command);

    printf("\nSearch (filter): max count of moves to analyse (when analyse all dbase) :\n");
    get_input(command, MAX_NAME_SIZE);
    count_movs = atoi(command);

    printf("\nSearch (filter): max count of games to analyse (when analyse suspect's games) (> 0) :\n");
    get_input(command, MAX_NAME_SIZE);
    count_gams = atoi(command);
    set_parser_params(&prsr, elo_min, elo_max, evnt, name, db_path, count_movs, count_gams);

    init_suspect_portrait(&player, &prsr);
    init_suspect_portrait(&same_rating, &prsr);

    time(&time_start);
    time(&time_curr);
    do_analize(&prsr, &engn, &player, &same_rating);
    time(&time_curr);
    printf("\nTotal time analysing: %f\n", difftime(time_curr, time_start));
    
#endif // DEBUG_DEC_MODULE
  
    if (engn_path_w != NULL) std::free(engn_path_w);
    return 0;
}

void CleanBuff() {
    char ch;
    ch = getchar();
    while (ch != '\n') ch = getchar();
}

void get_input(char* buff, int size) {
    scanf_s("%[^\n]s", buff, size);
    CleanBuff();
}
