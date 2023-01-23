#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Chessboard_handler.h"
#include "UCI_API.h"
#include "DataBase_parser.h"
#include "DEC_module.h"

void get_input(char*, int size);

void get_config(FILE* config,
    std::string* path_db,
    std::string* name,
    _event* type_games,
    int* minR,
    int* maxR,
    int* count_pos,
    int* count_games,
    std::wstring* path_engn,
    int* threads,
    int* multipv,
    int* hash,
    int* movetime);

wchar_t* GetWC(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}

int main()
{
    UCI_Engine engn;
    parser prsr;
    suspect_portrait player;
    suspect_portrait same_rating;
    FILE* config = NULL;
    std::string path_db;
    std::wstring path_engn;
    std::string name;
    int threads;
    int multipv;
    int hash;
    int movetime;
    time_t time_start, time_curr;
    char db_path[MAX_PATH_LENTH] = { '\0' };
    int elo_min = 0, elo_max = 0,
        count_pos = 0, count_games = 0;
    _event evnt = EVENT_BLITZ;

    /* Get options from config. */
    printf("Enter path to Config.txt file: ");
    scanf_s("%s", db_path, MAX_PATH_LENTH);
    fopen_s(&config, db_path, "r");
    if (config == NULL) {
        printf("Can't open file %s\n", db_path);
        exit(-1);
    }

    get_config(config,
        &path_db,
        &name,
        &evnt,
        &elo_min,
        &elo_max,
        &count_pos,
        &count_games,
        &path_engn,
        &threads,
        &multipv,
        &hash,
        &movetime
    );

    /* Set engine params. */
    engn.path_to_engine = path_engn;
    engn.set_options(threads, multipv, hash, movetime);

    /* Set parser params. */
    set_parser_params(&prsr, elo_min, elo_max, evnt, (char*)name.c_str(), (char*)path_db.c_str(), count_pos, count_games);
    init_suspect_portrait(&player, &prsr);
    init_suspect_portrait(&same_rating, &prsr);

    /* Start analysing. */
    time_start = clock();
    do_analize(&prsr, &engn, &player, &same_rating);
    time_curr = clock();
    printf("\nTotal time analysing: %f\n", (time_curr - time_start) / 1000.0);


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

void get_config(FILE* config,
    std::string* path_db,
    std::string* name,
    _event* type_games,
    int* minR,
    int* maxR,
    int* count_pos,
    int* count_games,
    std::wstring* path_engn,
    int* threads,
    int* multipv,
    int* hash,
    int* movetime) {
    char input[MAX_PATH_LENTH] = { '\0' };
    char c = '\0';
    wchar_t* wc;

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%s%c", input, &c);
    *path_db = input;

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%s%c", input, &c);
    *name = input;

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", type_games, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", minR, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", maxR, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", count_pos, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", count_games, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%s%c", input, &c);
    *path_engn = wc = GetWC(input);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", threads, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", multipv, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", hash, &c);

    fseek(config, 41, SEEK_CUR);
    fscanf(config, "%d%c", movetime, &c);

    delete wc;
}
