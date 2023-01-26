#include "DEC_module.h"

bool FlStop;

void init_suspect_portrait(suspect_portrait* susp, parser* prsr) {
	//memcpy(&susp->prsr, prsr, sizeof(parser));

	init_attr_cont(&susp->attr_acc);
	zero_attr_cont(&susp->attr_count);
}

int analize_move(UCI_Engine* engn, thc::ChessRules* cr, thc::Move* next_mv) {
	engine_line* line = (engine_line*) malloc(sizeof(engine_line) * engn->multipv);
	int acc = 0;

	// 1. Feed FEN to engine. Get answer of engine.
	engn->set_position(cr->ForsythPublish());
	engn->start_analyse();
	engn->parse_analisys_output(line); // Get lines with moves in LAN notation. 

	// 2. Get accuracy evaluation
	acc = get_accuracy_of_move(next_mv, line, engn->multipv);
	free(line);
	return acc;
}

void analize_game_player(game* gm, UCI_Engine* engn, suspect_portrait* susp, char* name) {
	thc::ChessRules cr;
	thc::Move mv;
	char move_from_game[MAX_MOVE_SIZE] = { '\0' };
	char* ptr_game_notation = gm->moves;
	std::string fen_string;

	attr_set attr_st;
	int acc = 0, count_acc = 0, 
		count_of_mvs_to_next_merge = 0, count_of_mv = 0;

	// 0. Calculate initial merge.
	fen_string = cr.ForsythPublish();  // Get FEN string
	get_attr_set(fen_string.c_str(), &attr_st); // Get attributes of position
	count_of_mvs_to_next_merge = get_count_of_moves_to_next_merge(ptr_game_notation);

	// 1. If player plays white side, then immedietly start analizing, else play 1st move, then analyze
	if (strcmp(gm->name_black, name) == 0) {
		ptr_game_notation = get_next_move_from_notation(ptr_game_notation, move_from_game);
		mv.NaturalIn(&cr, move_from_game);
		cr.PlayMove(mv);
		count_of_mv++;
	}

	// 2. Analyse each move of player, while don't reach the end of notation.
	while (ptr_game_notation != NULL && !FlStop)
	{
		// 1. Get next move.
		memset(move_from_game, '\0', sizeof(char) * MAX_MOVE_SIZE);
		ptr_game_notation = get_next_move_from_notation(ptr_game_notation, move_from_game);
		mv.NaturalIn(&cr, move_from_game);

		// 3. Analyse move.
		acc += analize_move(engn, &cr, &mv);
		count_acc++;

		// 4. Move that move on board.
		cr.PlayMove(mv);
		count_of_mv++;

		// 4.1 Merge positions, if it is time.
		if (count_of_mv >= count_of_mvs_to_next_merge) {
			if (count_acc != 0) {
				fill_acc_in_attr_containers_in_no_socks(&attr_st, susp, acc, count_acc);
			}
			count_of_mvs_to_next_merge = get_count_of_moves_to_next_merge(ptr_game_notation); // Get next count of...
			fen_string = cr.ForsythPublish();  // Get FEN string of new position
			get_attr_set(fen_string.c_str(), &attr_st); // Get attributes of new position

			acc = 0;
			count_acc = 0;
			count_of_mv = 0;
		}
		
		// 5. Skip opponent move 
		if (ptr_game_notation != NULL) {
			ptr_game_notation = get_next_move_from_notation(ptr_game_notation, move_from_game); // gets opponent move
			mv.NaturalIn(&cr, move_from_game);
			cr.PlayMove(mv);
			count_of_mv++;

			// 5.1 Merge positions, if it is time.
			if (count_of_mv >= count_of_mvs_to_next_merge) {
				if (count_acc != 0) {
					fill_acc_in_attr_containers_in_no_socks(&attr_st, susp, acc, count_acc);
				}
				count_of_mvs_to_next_merge = get_count_of_moves_to_next_merge(ptr_game_notation); // Get next count of...
				fen_string = cr.ForsythPublish();  // Get FEN string of new position
				get_attr_set(fen_string.c_str(), &attr_st); // Get attributes of new position

				acc = 0;
				count_acc = 0;
				count_of_mv = 0;
			}
		}
	}
}

int analize_game_player_no_name(game* gm, UCI_Engine* engn, suspect_portrait* susp, int max_count_of_moves) {
	thc::ChessRules cr;
	thc::Move mv;
	char move_from_game[MAX_MOVE_SIZE] = { '\0' };
	char* ptr_game_notation = gm->moves;
	std::string fen_string;
	bool side = WHITE_SIDE;
	int count_mv_anal = 0;

	attr_set attr_st;
	bool attr_st_flag = true; // If this attr_set WAS in a player analisis, than analyse this attr_set
	int acc = 0, acc_white = 0, count_acc_white = 0,
		acc_black = 0, count_acc_black = 0,
		count_of_mvs_to_next_merge = 0, count_of_mv = 0;

	// 0. Calculate initial merge.
	fen_string = cr.ForsythPublish();  // Get FEN string
	get_attr_set(fen_string.c_str(), &attr_st); // Get attributes of position
	attr_st_flag = is_attr_set_in_attr_cont(&attr_st, &susp->attr_acc) && is_attr_set_count_pass_filter(&attr_st, &susp->attr_count, max_count_of_moves); // Get flag of attr_set
	count_of_mvs_to_next_merge = get_count_of_moves_to_next_merge(ptr_game_notation);

	// 1. Analyse each move, while don't reach the end of notation.
	while (ptr_game_notation != NULL && !FlStop)
	{
		// 1. Get next move.
		memset(move_from_game, '\0', sizeof(char) * MAX_MOVE_SIZE);
		ptr_game_notation = get_next_move_from_notation(ptr_game_notation, move_from_game);
		mv.NaturalIn(&cr, move_from_game);

		// 2. Analyse move if attr_set was in player analysis.
		if (attr_st_flag == true) {
			acc = analize_move(engn, &cr, &mv);
			if (side != BLACK_SIDE) {
				acc_white += acc;
				count_acc_white++;
				side = BLACK_SIDE;
			}
			else {
				acc_black += acc;
				count_acc_black++;
				side = WHITE_SIDE;
			}
			count_mv_anal++;
		}

		// 3. Move that move on board.
		cr.PlayMove(mv);
		count_of_mv++;

		// 3.1 Merge positions, if it is time.
		if (count_of_mv >= count_of_mvs_to_next_merge) {
			if (attr_st_flag == true) {
				if (count_acc_white != 0) {
					fill_acc_in_attr_containers_in_yes_socks(&attr_st, susp, acc_white, count_acc_white);
				}
				if (count_acc_black != 0) {
					fill_acc_in_attr_containers_in_yes_socks(&attr_st, susp, acc_black, count_acc_black);
				}

				acc = 0;
				acc_black = 0;
				acc_white = 0;
				count_acc_black = 0;
				count_acc_white = 0;
			}
			count_of_mvs_to_next_merge = get_count_of_moves_to_next_merge(ptr_game_notation); // Get next count of...
			fen_string = cr.ForsythPublish();  // Get FEN string of new position
			get_attr_set(fen_string.c_str(), &attr_st); // Get attributes of new position
			attr_st_flag = is_attr_set_in_attr_cont(&attr_st, &susp->attr_acc) && is_attr_set_count_pass_filter(&attr_st, &susp->attr_count, max_count_of_moves); // Get flag of attr_set

			count_of_mv = 0;
		}
	}

	//fprintf(logFile, "moves analised = %d, ", count_mv_anal);
	return count_mv_anal;
}

void do_analize_glob_player(parser* prsr, UCI_Engine* engn, suspect_portrait* susp) {
	game gm;
	int count_of_games = 0;
	time_t time_start, time_curr;
	FILE* file = NULL;
	fopen_s(&file, "Suspect_analyse.txt", "w");
	print_info_file(file, prsr, engn);

	open_database(prsr);
	init_attr_cont(&susp->attr_acc);
	zero_attr_cont(&susp->attr_count);

	while (count_of_games < prsr->fiter.max_count_of_games && get_next_game(prsr, &gm) != DB_EOF && !FlStop)
	{
		time_start = clock();
		printf("Analyse game %d ", count_of_games + 1);
		analize_game_player(&gm, engn, susp, prsr->fiter.name);
		count_of_games++;
		time_curr = clock();
		printf("time: %fs\n", (time_curr - time_start) / 1000.0);
	}

	calc_acc_suspect(susp);
	print_susp_file(susp, file);
	print_susp_std(susp);
	printf("\n");

	close_database(prsr);
}

void do_analize_glob_no_name(parser* prsr, UCI_Engine* engn, suspect_portrait* susp, suspect_portrait* player) {
	game gm;
	char name_cpy[MAX_NAME_SIZE] = { '\0' };
	int count_of_games = 0;
	time_t time_start, time_curr;
	int count_moves = 0;
	FILE* file = NULL;
	fopen_s(&file, "DB_analyse.txt", "w");
	print_info_file(file, prsr, engn);

	// Empty name filter of parser.
	memcpy(name_cpy, prsr->fiter.name, sizeof(char) * MAX_NAME_SIZE);
	memset(prsr->fiter.name, '\0', sizeof(char) * MAX_NAME_SIZE);

	open_database(prsr);
	init_attr_cont_with_other_cont(&susp->attr_acc, &player->attr_acc);
	zero_attr_cont(&susp->attr_count);

	while (get_next_game(prsr, &gm) != DB_EOF && !FlStop)
	{
		count_of_games++;
		time_start = clock();
		printf("Analyse game %d, ", count_of_games);
		count_moves = get_count_of_moves_total(&gm);
		printf("total moves = %d, ", count_moves);
		analize_game_player_no_name(&gm, engn, susp, prsr->fiter.max_count_of_moves);
		time_curr = clock();
		printf("time: %fs\n", (time_curr - time_start) / 1000.0);
		print_susp_std_count(susp);
	}

	calc_acc_suspect(susp);
	print_susp_file(susp, file);
	print_susp_std(susp);

	memcpy(prsr->fiter.name, name_cpy, sizeof(char) * MAX_NAME_SIZE);

	close_database(prsr);
}

void do_analize(parser* prsr, UCI_Engine* engn, suspect_portrait* susp_player, suspect_portrait* susp_no_name) {
	// 1. Load an engine.
	if (engn->load() == ENGINE_OK) {
		//2. Analyse base.
		if (susp_player == NULL) { // If name filter wasn't matched.

		}
		else { // If need to analyse a player.
			printf("Analyse player started.\n");
			do_analize_glob_player(prsr, engn, susp_player); // Firstly, analyze a player.
			printf("Analyse player finished.\n");
			printf("Analyse other dbase started.\n");
			do_analize_glob_no_name(prsr, engn, susp_no_name, susp_player); // Secondly, analyse all attr_sets, that was analyzed in analise before.
			printf("Analyse other dbase finished.\n");
		}

		engn->close();
	}
}

char* get_next_move_from_notation(char* notation, char* move_buff) {
	int len = strlen(notation);
	int i = 0;

	memset(move_buff, '\0', sizeof(char) * MAX_MOVE_SIZE);

	for (i = 0; i < len; i++) {
		if (notation[i] != ' ' && notation[i] != '\0') {
			move_buff[i] = notation[i];
		}
		else {
			break;
		}
	}

	if (notation[i] == ' ') {
		if (notation[i + 1] == '\0'){
			return NULL;
		}
		else {
			return notation + i + 1;
		}
	}
	else {
		return NULL;
	}
}

int get_count_of_moves_to_next_merge(char* notation) {
	int len = 0;
	bool is_capture = false, is_capture_in_move = false;
	int count_of_moves_to_next_merge = 0;

	if (notation == NULL) {
		return 0;
	}
	else {
		len = strlen(notation);
	}

	for (int i = 0; i < len; i++) {
		if (notation[i] == ' ') {
			count_of_moves_to_next_merge++;

			if (is_capture_in_move == false && is_capture == true) {
				count_of_moves_to_next_merge--;
				break;
			}

			is_capture_in_move = false;
		}
		else {
			if ((notation[i] == 'x' || notation[i] == '=')) {
				is_capture_in_move = true;

				if (is_capture == false) {
					is_capture = true;
				}
			}
		}
	}

	return count_of_moves_to_next_merge;
}

/* Line 1. Return 100.
   Line 2. Return 50
   Line 3. Return 25
   Line 4. Return 12
   No Line. Return 0 */
int get_accuracy_of_move(thc::Move* mv, engine_line* line, int count_of_lines) {
	std::string str = mv->TerseOut();
	for (int i = 0; i < count_of_lines; i++) {
		if (strcmp(line[i].move, str.c_str()) == 0) {
			return ACC_MULTI / (1 << i);
		}
	}

	return 0;
}

void fill_acc_in_attr_containers_in_no_socks(attr_set* attr_st, suspect_portrait* susp, int accuracy, int count_of_moves) {
	int vectr[5][2];

	vectr[0][0] = attr_st->count_P; vectr[0][1] = EMPTY_P;
	vectr[1][0] = attr_st->count_N; vectr[1][1] = EMPTY_N;
	vectr[2][0] = attr_st->count_B; vectr[2][1] = EMPTY_B;
	vectr[3][0] = attr_st->count_R; vectr[3][1] = EMPTY_R;
	vectr[4][0] = attr_st->count_Q; vectr[4][1] = EMPTY_Q;

	for (int p = 0; p < 2; p++) {
		for (int n = 0; n < 2; n++) {
			for (int b = 0; b < 2; b++) {
				for (int r = 0; r < 2; r++) {
					for (int q = 0; q < 2; q++) {
						// Summ up accuracy
						if (susp->attr_acc.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] == POSITION_ATTR_NO) {
							susp->attr_acc.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] = 0;
						}
						susp->attr_acc.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] += accuracy;

				        // Increment count of eqivalent accuracies
						susp->attr_count.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] += count_of_moves;
					}
				}
			}
		}
	}
}

void fill_acc_in_attr_containers_in_yes_socks(attr_set* attr_st, suspect_portrait* susp, int accuracy, int count_of_moves) {
	int vectr[5][2];

	vectr[0][0] = attr_st->count_P; vectr[0][1] = EMPTY_P;
	vectr[1][0] = attr_st->count_N; vectr[1][1] = EMPTY_N;
	vectr[2][0] = attr_st->count_B; vectr[2][1] = EMPTY_B;
	vectr[3][0] = attr_st->count_R; vectr[3][1] = EMPTY_R;
	vectr[4][0] = attr_st->count_Q; vectr[4][1] = EMPTY_Q;

	for (int p = 0; p < 2; p++) {
		for (int n = 0; n < 2; n++) {
			for (int b = 0; b < 2; b++) {
				for (int r = 0; r < 2; r++) {
					for (int q = 0; q < 2; q++) {
						// Summ up accuracy
						if (susp->attr_acc.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] == POSITION_ATTR_YES) {
							susp->attr_acc.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] = 0;
						}
						susp->attr_acc.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] += accuracy;

						// Increment count of eqivalent accuracies
						susp->attr_count.cont.int_cont[vectr[0][p]][vectr[1][n]][vectr[2][b]][vectr[3][r]][vectr[4][q]] += count_of_moves;
					}
				}
			}
		}
	}
}

void calc_acc_suspect(suspect_portrait* susp) {
	for (int p = 0; p < MAX_P; p++) {
		for (int n = 0; n < MAX_N; n++) {
			for (int b = 0; b < MAX_B; b++) {
				for (int r = 0; r < MAX_R; r++) {
					for (int q = 0; q < MAX_Q; q++) {
						if (susp->attr_acc.cont.int_cont[p][n][b][r][q] != POSITION_ATTR_NO && susp->attr_acc.cont.int_cont[p][n][b][r][q] != POSITION_ATTR_YES) {
							susp->attr_acc.cont.fl_cont[p][n][b][r][q] =
								((float)susp->attr_acc.cont.int_cont[p][n][b][r][q]) / ACC_MULTI / susp->attr_count.cont.int_cont[p][n][b][r][q] * 100;
						}									
					}
				}
			}
		}
	}
}


// Some functions for debugging
void print_susp_std(suspect_portrait* susp) {
	for (int p = 0; p < MAX_P - 1; p++) {
		for (int n = 0; n < MAX_N - 1; n++) {
			for (int b = 0; b < MAX_B - 1; b++) {
				for (int r = 0; r < MAX_R - 1; r++) {
					for (int q = 0; q < MAX_Q - 1; q++) {
						if (susp->attr_acc.cont.int_cont[p][n][b][r][q] != POSITION_ATTR_NO) {
							printf("{%d_p, %d_n, %d_b, %d_r, %d_q}: accuracy = %f, count = %d\n", 
								p, n, b, r, q, susp->attr_acc.cont.fl_cont[p][n][b][r][q],
								susp->attr_count.cont.int_cont[p][n][b][r][q]);
						}
					}
				}
			}
		}
	}
}

void print_susp_std_count(suspect_portrait* susp) {
	for (int p = 0; p < MAX_P - 1; p++) {
		for (int n = 0; n < MAX_N - 1; n++) {
			for (int b = 0; b < MAX_B - 1; b++) {
				for (int r = 0; r < MAX_R - 1; r++) {
					for (int q = 0; q < MAX_Q - 1; q++) {
						if (susp->attr_acc.cont.int_cont[p][n][b][r][q] != POSITION_ATTR_NO) {
							printf("{%d_p, %d_n, %d_b, %d_r, %d_q}: count = %d\n",
								p, n, b, r, q,
								susp->attr_count.cont.int_cont[p][n][b][r][q]);
						}
					}
				}
			}
		}
	}
}

void print_susp_file(suspect_portrait* susp, FILE* file) {
	for (int p = 0; p < MAX_P; p++) {
		for (int n = 0; n < MAX_N; n++) {
			for (int b = 0; b < MAX_B; b++) {
				for (int r = 0; r < MAX_R; r++) {
					for (int q = 0; q < MAX_Q; q++) {
						if (susp->attr_acc.cont.int_cont[p][n][b][r][q] != POSITION_ATTR_NO) {
							if (p == EMPTY_P) {
								fprintf(file, "{X_p, ");
							}
							else {
								fprintf(file, "{%d_p, ", p);
							}
							if (n == EMPTY_N) {
								fprintf(file, "X_n, ");
							}
							else {
								fprintf(file, "%d_n, ", n);
							}
							if (b == EMPTY_B) {
								fprintf(file, "X_b, ");
							}
							else {
								fprintf(file, "%d_b, ", b);
							}
							if (r == EMPTY_R) {
								fprintf(file, "X_r, ");
							}
							else {
								fprintf(file, "%d_r, ", r);
							}
							if (q == EMPTY_Q) {
								fprintf(file, "X_q}: ");
							}
							else {
								fprintf(file, "%d_q}: ", q);
							}
							fprintf(file, "accuracy = %f, count = %d\n",
								susp->attr_acc.cont.fl_cont[p][n][b][r][q],
								susp->attr_count.cont.int_cont[p][n][b][r][q]);
						}
					}
				}
			}
		}
	}
}

void print_info_file(FILE* file, parser* prsr, UCI_Engine* engn) {
	fprintf(file, "Path to db: %s\n"
		"Name/nick-name of player (suspect): %s\n"
		"Path to engine: %ls\n"
		"Engine: Count of CPU threads: %d\n"
		"Engine: Count of lines: %d\n"
		"Engine: Hash size: %d MB\n"
		"Engine: Move time: %d sec\n",
		prsr->db.path_to_db,
		prsr->fiter.name,
		engn->path_to_engine.c_str(),
		engn->cpu,
		engn->multipv,
		engn->hash,
		engn->movetime);
	if (prsr->fiter.evnt == EVENT_BLITZ) fprintf(file, "Search (filter): Type of games: Blitz\n");
	else if (prsr->fiter.evnt == EVENT_BULLET) fprintf(file, "Search (filter): Type of games: Bullet\n");
	else if (prsr->fiter.evnt == EVENT_CLASSIC) fprintf(file, "Search (filter): Type of games: Classical\n");
	fprintf(file, "Search (filter): Min rating: %d\n"
		"Search(filter): Max rating: % d\n"
		"Search(filter): Max count of moves: %d\n"
		"Search(filter): Max count of games: %d\n\n",
		prsr->fiter.elo_min,
		prsr->fiter.elo_min,
		prsr->fiter.max_count_of_moves,
		prsr->fiter.max_count_of_games);
}

int get_count_of_moves_total(game* gm) {
	int len = strlen(gm->moves);
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (gm->moves[i] == ' ') {
			count++;
		}
	}

	return count;
}