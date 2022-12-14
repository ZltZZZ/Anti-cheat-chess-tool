#pragma once

#define ACC_MULTI 10000

#include "DataBase_parser.h"
#include "Engine_handler.h"
#include "Chessboard_handler.h"
#include <QThread>
#include <QFile>
#include "analysislogwindow.h"

/* ------------This is a module that unite all handlers in one synchronized working machine----------------------
   -----------------------called "DEC" - Database-Engine-Chessboard module.-------------------------------------- */

/* That is a struct that contains information about accuracy of suspected person,
   and other following information about range of research. */
typedef struct _suspect_portrait {
	parser prsr;

    /* Sum of accuracies for all possible sets of attribute (used to calculate the average accuracy after analysis)  */
	attr_container attr_acc;

	/* The count of attributes of each kind (used to calculate the average accuracy after analysis). */
	attr_container attr_count;
} suspect_portrait;

class AnalysisHandler : public QThread
{
public:
    explicit AnalysisHandler(QString threadName, parser* prsr, engine* engn, suspect_portrait* player, suspect_portrait* db, AnalysisLogWindow* logW);
    ~AnalysisHandler();
    void run();
    void stop();
    void on_exit();

private:
    QString name;
    parser prsr;
    engine engn;
    suspect_portrait player;
    suspect_portrait db;
    AnalysisLogWindow* logW;
    FILE* saveFile;
    FILE* logFile;
};

/* Init suspect portrait. */
void init_suspect_portrait(suspect_portrait*, parser*);

/* Return accuracy of move. */
int analize_move(engine*, thc::ChessRules*, thc::Move* next_mv);

/* Analize a game of a player, named NAME. THIS IS A MAIN ALGORINM OF ANALIZING.*/
void analize_game_player(game*, engine*, suspect_portrait*, char* name);

/* Analizes ONLY positions, that contains the same attr_set as was in analysis of player. THIS IS A MAIN ALGORINM OF ANALIZING.*/
void analize_game_player_no_name(game*, engine*, suspect_portrait*, FILE* logFile);

/* Get a move string from notation. Returns NULL, if this is was last move in notation. */
char* get_next_move_from_notation(char* notation, char* move_buff);

/* Ananlizes all games of choosed player. */
void do_analize_glob_player(parser*, engine*, suspect_portrait*, AnalysisLogWindow* logW, FILE* logFile);

/* Ananlizes all games that without name filter (analyze ONLY positions, that player played. */
int do_analize_glob_no_name(parser*, engine*, suspect_portrait* susp, suspect_portrait* player, int max_count_of_moves, AnalysisLogWindow* logW, FILE* logFile);

/* Ananlizes all games that without name filter (with full analize of game). */
void do_analize_glob(parser*, engine*, suspect_portrait*, AnalysisLogWindow* logW, FILE* logFile);

/* Main function, that calls from entry point. */
void do_analize(parser*, engine*, suspect_portrait* susp_player, suspect_portrait* susp_no_name, AnalysisLogWindow* logW, FILE* logFile);

/* Compare next move of ENGINE with next move of Player. Returns a number, that correspondes to number of line. */
int get_accuracy_of_move(thc::Move*, engine_line*, int count_of_lines);

/* Returns count of move to next merge (serial captures or promotion). */
int get_count_of_moves_to_next_merge(char* notation);

/* Fill accuracy of move in all sets of attr of suspect.*/
void fill_acc_in_attr_containers_in_no_socks(attr_set* attr_st, suspect_portrait*, int accuracy, int count_of_moves);

/* Fill accuracy of move in all sets of attr of suspect, that marked as POSITION_ATTR_YES.*/
void fill_acc_in_attr_containers_in_yes_socks(attr_set* attr_st, suspect_portrait*, int accuracy, int count_of_moves);

/* Calculate all accuracies that was as int in susp. */
void calc_acc_suspect(suspect_portrait*);

// Some functions for debugging
void print_susp_std(suspect_portrait* susp);

void print_susp_file(suspect_portrait* susp, FILE* file);

void print_susp_std_count(suspect_portrait* susp);

void print_info_file(FILE* file, parser* prsr, engine* engn);

int get_count_of_moves_total(game* gm);

