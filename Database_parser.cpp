#include "DataBase_parser.h"

void set_search_params(parser* prsr, int min_elo, int max_elo, _event evnt, char* name, char* path_to_db) {
	prsr->params.elo_min = min_elo;
	prsr->params.elo_max = max_elo;
	prsr->params.evnt = evnt;
	if (name != NULL) {
		memcpy(prsr->params.name, name, sizeof(char) * MAX_NAME_SIZE);
	}
	else {
		memset(prsr->params.name, '\0', sizeof(char) * MAX_NAME_SIZE);
	}

	memcpy(prsr->db.path_to_db, path_to_db, sizeof(char) * MAX_PATH_LENTH);
}

void get_next_game(parser* prsr, game* gm) {
	// There are main parsing algorithm
}

bool is_end_of_db(parser* prsr) {

}

void open_database(parser* prsr) {
	prsr->db.pgn_db.open (prsr->db.path_to_db);
}

void close_database(parser* prsr) {
	prsr->db.pgn_db.close();
}