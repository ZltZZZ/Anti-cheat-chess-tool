#include "DEC_module.h"

int analize_move(engine* engn, thc::ChessRules* cr, char* mv_next, std::string* fen_string) {
	engine_line line[OPTION_MULTI_PV_DEF];
	thc::Move next_move;

	// 1. Feed FEN to engine. Get answer of engine.
	engine_set_position(engn, (char*)fen_string->c_str());
	engine_send_command_start_analyze(engn, MOVE_TIME_DEFUALT);
	engine_parse_analisys_output(engn, line); // Get lines with moves in LAN notation. 

	// 2. Get accuracy evaluation
	next_move.NaturalIn(cr, mv_next);
	return get_accuracy_of_move(&next_move, line, OPTION_MULTI_PV_DEF);
}

void analize_game_player(game* gm, engine* engn, suspect_portrait* susp, char* name) {
	thc::ChessRules cr;
	thc::Move mv;
	char move_from_game[MAX_MOVE_SIZE] = { '\0' };
	char* ptr_game_notation = gm->moves;
	std::string fen_string;

	attr_set last_set, that_set;
	int acc = 0, count_acc = 0;

	// 1. If player plays white side, then immedietly start analizing, else play 1st move, then analyze
	if (strcmp(gm->name_black, name) == 0) {
		ptr_game_notation = get_next_move_from_notation(ptr_game_notation, move_from_game);
		mv.NaturalIn(&cr, move_from_game);
		cr.PlayMove(mv);
	}

	// 2. Analyse each move of player, while don't reach the end of notation.
	while (ptr_game_notation != NULL)
	{
		// 1. Get next move.
		memset(move_from_game, '\0', sizeof(char) * MAX_MOVE_SIZE);
		ptr_game_notation = get_next_move_from_notation(ptr_game_notation, move_from_game);
		
		// 2. Get attributes of position
		fen_string = cr.ForsythPublish();  // Get FEN string
		get_attr_set(fen_string.c_str(), &last_set);

		// 3. Analyse move.
		acc = analize_move(engn, &cr, move_from_game, &fen_string);

		// 4. Move that move on board.
		mv.NaturalIn(&cr, move_from_game);
		cr.PlayMove(mv);

		// 5. Merge position on cuptures. (If this is a "cupturing" position, than merge it with last one).
		fen_string = cr.ForsythPublish();  // Get FEN string
		get_attr_set(fen_string.c_str(), &that_set);

		if (compare_attr_sets(&that_set, &last_set) != 0) {
			
		}
		
		// 6. Skip opponent move 
		if (ptr_game_notation != NULL) {
			ptr_game_notation = get_next_move_from_notation(ptr_game_notation, move_from_game); // gets opponent move
			mv.NaturalIn(&cr, move_from_game);
			cr.PlayMove(mv);

			// Also merge position on cuptures. (If this is a "cupturing" position, than merge it with last one).
			copy_attr_set(&last_set, &that_set);
			fen_string = cr.ForsythPublish();  // Get FEN string
			get_attr_set(fen_string.c_str(), &that_set);

			if (compare_attr_sets(&that_set, &last_set) != 0) {
				
			}
		}
	}
}

void do_analize_glob_player(parser* prsr, engine* engn, suspect_portrait* susp) {
	game gm;

	open_database(prsr);

	while (get_next_game(prsr, &gm) != DB_EOF)
	{
		analize_game_player(&gm, engn, susp, prsr->fiter.name);
	}

	close_database(prsr);
}

char* get_next_move_from_notation(char* notation, char* move_buff) {
	int len = strlen(notation);
	int i = 0;

	for (i = 0; i < len; i++) {
		if (notation[i] != ' ' && notation[i] != '\0') {
			move_buff[i] = notation[i];
		}
		else {
			break;
		}
	}

	if (notation[i] == ' ') {
		return notation + i + 1;
	}
	else {
		return NULL;
	}
}

/* Line 1. Return 100.
   Line 2. Return 50
   Line 3. Return 25
   Line 4. Return 12
   No Line. Return 0 */
int get_accuracy_of_move(thc::Move* mv, engine_line* line, int count_of_lines) {
	for (int i = 0; i < count_of_lines; i++) {
		if (strcmp(line[i].move, (mv->TerseOut()).c_str()) == 0) {
			return 100 / (i + 1);
		}
	}

	return 0;
}

void fill_acc_in_attr_containers(attr_set* attr_st, suspect_portrait* susp, int accuracy) {
	int vectr[5][2];

	vectr[0][0] = attr_st->count_P - 1; vectr[0][1] = EMPTY_P - 1;
	vectr[1][0] = attr_st->count_N - 1; vectr[1][1] = EMPTY_N - 1;
	vectr[2][0] = attr_st->count_B - 1; vectr[2][1] = EMPTY_B - 1;
	vectr[3][0] = attr_st->count_R - 1; vectr[3][1] = EMPTY_R - 1;
	vectr[4][0] = attr_st->count_Q - 1; vectr[4][1] = EMPTY_Q - 1;

	for (int p = 0; p < 2; p++) {
		for (int n = 0; n < 2; n++) {
			for (int b = 0; b < 2; b++) {
				for (int r = 0; r < 2; r++) {
					for (int q = 0; q < 2; q++) {
						// Summ up accuracy
						susp->attr_acc.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] += accuracy;
				        // Increment count of eqivalent accuracies
						susp->attr_count.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]]++;
					}
				}
			}
		}
	}
}