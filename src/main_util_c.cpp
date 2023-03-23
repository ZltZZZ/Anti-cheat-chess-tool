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
    UCI_Engine engn;                            // UCI chess engine, wich will analyse suspect.
    parser prsr;                                // Parser struct with required pointers and information for analysis.
    suspect_portrait* player = NULL;            // Container for future analysys results for suspect. 
    suspect_portrait* same_rating = NULL;       // Container for future analysys results for database.

    /* Configuration. */
    FILE* config = NULL;                        // File with configuration.
    char config_path[MAX_PATH_LENTH] = { '\0' };// Path to config file.

    /* Debugging. */
    time_t time_start, time_curr;               // Timer for debugging.

    /* Parser params. */
    std::string path_db;                        // Path to database (.pgn).
    std::wstring path_engn;                     // Path to engine (.exe).
    std::string name;                           // Name/nickname of suspect.
    int elo_min = 0, elo_max = 0,               // Min and Max Elo (range).
        count_pos = 0, count_games = 0;         // Max count of positions (for db analysys) and games (for suspect).
    _event evnt = EVENT_BLITZ;                  // Type of Event (Blitz, Classic or Bullet).

    /* Engine params. */
    int threads;                                // Count of threads for engine.
    int multipv;                                // Count of lines, shoud be 4.
    int hash;                                   // Size of hash (in mb).
    int movetime;                               // Movetime (in ms).



    player = (suspect_portrait*)malloc(sizeof(suspect_portrait));
    same_rating = (suspect_portrait*)malloc(sizeof(suspect_portrait));
    if (player == NULL || same_rating == NULL) {
        printf("Malloc error: player = (suspect_portrait*)malloc(sizeof(suspect_portrait));\n");
        exit(-1);
    }

    /* Get options from config. */
    printf("Enter path to Config.txt file: ");
    scanf_s("%s", config_path, MAX_PATH_LENTH);
    fopen_s(&config, config_path, "r");
    if (config == NULL) {
        printf("Can't open file %s\n", config_path);
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

    /* Start analysing. */
    time_start = clock();
    do_analize(&prsr, &engn, player, same_rating);
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
