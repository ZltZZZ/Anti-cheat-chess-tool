#include "DataBase_parser.h"

void set_parser_params(parser* prsr, int min_elo, int max_elo, _event evnt, char* name, char* path_to_db) {
	prsr->fiter.elo_min = min_elo;
	prsr->fiter.elo_max = max_elo;
	prsr->fiter.evnt = evnt;
	if (name != NULL) {
		memcpy(prsr->fiter.name, name, sizeof(char) * MAX_NAME_SIZE);
	}
	else {
		memset(prsr->fiter.name, '\0', sizeof(char) * MAX_NAME_SIZE);
	}

	memcpy(prsr->db.path_to_db, path_to_db, sizeof(char) * MAX_PATH_LENTH);
}

void game_clear(game* gm) {
	gm->elo_black = 0;
	gm->elo_white = 0;
	gm->evnt = EVENT_UNDEFINED;
	memset(gm->moves, '\0', sizeof(char) * MAX_BUFF_SIZE);
	memset(gm->name_black, '\0', sizeof(char) * MAX_NAME_SIZE);
	memset(gm->name_white, '\0', sizeof(char) * MAX_NAME_SIZE);
}

int get_next_game(parser* prsr, game* gm) {
	// There are main parsing algorithm
	tag tag_name;
	char* ptr_value = NULL;
	char c;

	// Seacrh until needed game is not found or end of databse isn't reached
	while (!feof(prsr->db.pgn_db))
	{
		game_clear(gm);

		// Get tags and it's values
		while (true)
		{
			memset(prsr->db.buff, '\0', sizeof(char) * MAX_BUFF_SIZE);
			fscanf_s(prsr->db.pgn_db, "%[^\n]%c", prsr->db.buff, MAX_BUFF_SIZE, &c, 1);

			// If reaches empty string in pgn base, that it is the section of moves, so exit loop
			if (prsr->db.buff[0] == '\0') {
				break;
			}
			else {
				// Parse tag
				tag_name = get_tag_name(prsr->db.buff);
				ptr_value = get_tag_value(prsr->db.buff);
				fill_tag_in_game(gm, tag_name, ptr_value);
			}
		}

		fscanf_s(prsr->db.pgn_db, "%c", &c, 1); // Read empty string

		// Check tags of search, and go get next game if doesn't passed filter
		if (check_filter(prsr, gm) == false) {
			memset(prsr->db.buff, '\0', sizeof(char) * MAX_BUFF_SIZE);
			fscanf_s(prsr->db.pgn_db, "%[^\n]%c", prsr->db.buff, MAX_BUFF_SIZE, &c, 1); // Read moves section
			memset(prsr->db.buff, '\0', sizeof(char) * MAX_BUFF_SIZE);
			fscanf_s(prsr->db.pgn_db, "%c", &c, 1); // Read empty string
			// Go to next position
			continue;
		}
		else {
			// Parse moves section. Delete comments, number of moves and so on.
			memset(prsr->db.buff, '\0', sizeof(char) * MAX_BUFF_SIZE);
			fscanf_s(prsr->db.pgn_db, "%[^\n]%c", prsr->db.buff, MAX_BUFF_SIZE, &c, 1);
			move_parser(gm, prsr->db.buff);
			// Read empty string to normalize FILE ptr
			fscanf_s(prsr->db.pgn_db, "%c", &c, 1); // Read empty string
			return DB_SUCCESS;
		}
	}

	return DB_EOF;
}

void open_database(parser* prsr) {
	fopen_s(&prsr->db.pgn_db, prsr->db.path_to_db, "r");
}

void close_database(parser* prsr) {
	fclose(prsr->db.pgn_db);
}

tag get_tag_name(char* buff) {
	char* ptr_substr = NULL;
	if ((ptr_substr = strstr(buff, "[Event ")) != NULL && ptr_substr == buff) {
		return TAG_EVENT;
	}
	if ((ptr_substr = strstr(buff, "[White ")) != NULL && ptr_substr == buff) {
		return TAG_WHITE;
	}
	if ((ptr_substr = strstr(buff, "[Black ")) != NULL && ptr_substr == buff) {
		return TAG_BLACK;
	}
	if ((ptr_substr = strstr(buff, "[WhiteElo ")) != NULL && ptr_substr == buff) {
		return TAG_WHITE_ELO;
	}
	if ((ptr_substr = strstr(buff, "[BlackElo ")) != NULL && ptr_substr == buff) {
		return TAG_BLACK_ELO;
	}
	return TAG_UNDEFINED;
}

char* get_tag_value(char* buff) {
	for (int i = 0; i < MAX_BUFF_SIZE; i++) {
		if (buff[i] == '\"') {
			return buff + i + 1;
		}
	}

	return NULL;
}

void fill_tag_in_game(game* gm, tag tg, char* value_ptr) {
	switch (tg)
	{
	case TAG_EVENT:
		if (strstr(value_ptr, "Bullet") != NULL || strstr(value_ptr, "bullet") != NULL) {
			gm->evnt = EVENT_BULLET;
		}
		else if (strstr(value_ptr, "Classic") != NULL || strstr(value_ptr, "classic") != NULL) {
			gm->evnt = EVENT_CLASSIC;
		}
		else if ((strstr(value_ptr, "Blitz") != NULL || strstr(value_ptr, "blitz") != NULL)) {
			gm->evnt = EVENT_BLITZ;
		}
		else {
			gm->evnt = EVENT_UNDEFINED;
		}
		break;
	case TAG_WHITE:
		for (int i = 0; value_ptr[i] != '\"'; i++) {
			gm->name_white[i] = value_ptr[i];
		}
		break;
	case TAG_BLACK:
		for (int i = 0; value_ptr[i] != '\"'; i++) {
			gm->name_black[i] = value_ptr[i];
		}
		break;
	case TAG_WHITE_ELO:
		gm->elo_white = atoi(value_ptr);
		if (gm->elo_white == 0) gm->elo_white = NO_RATING;
		break;
	case TAG_BLACK_ELO:
		gm->elo_black = atoi(value_ptr);
		if (gm->elo_black == 0) gm->elo_black = NO_RATING;
		break;
	case TAG_UNDEFINED:
		break;
	}
}

bool check_filter(parser* prsr, game* gm) {
	float avrg_elo = NO_RATING;   // Avarage elo of a game
	if (gm->elo_black != NO_RATING && gm->elo_white != NO_RATING) {
		avrg_elo = (float)(gm->elo_black + gm->elo_white) / 2;
	}

	if (prsr->fiter.elo_max != NO_RATING && (avrg_elo == NO_RATING || avrg_elo < prsr->fiter.elo_min || avrg_elo > prsr->fiter.elo_max)){
		return false;
	}
	if (prsr->fiter.evnt != EVENT_UNDEFINED && prsr->fiter.evnt != gm->evnt) {
		return false;
	}
	if (prsr->fiter.name[0] != '\0' && strcmp(prsr->fiter.name, gm->name_black) != 0 && strcmp(prsr->fiter.name, gm->name_white) != 0) {
		return false;
	}

	return true;
}

void move_parser(game* gm, char* buff) {
	bool isComment = false,
		 isMove = false;
	char possibleChars_start[] = "abcdefghNBRQK";
	char possibleChars_move[] = "12345678abcdefghNBRQKx= ";
	int gm_index = 0;

	for (int i = 0; i < MAX_BUFF_SIZE; i++) {
		// Start of a comment
		if (buff[i] == '{') {
			isComment = true;
		}
		// End of comment
		else if (buff[i] == '}')
		{
			isComment = false;
		}

		// Part of the move write in _game structure
		if (isMove) {
			if (strchr(possibleChars_move, buff[i]) != NULL)
				gm->moves[gm_index++] = buff[i];
		}
		// Check if it is a start of move
		else {
			if (!isComment && strchr(possibleChars_start, buff[i]) != NULL) {
				isMove = true;
				gm->moves[gm_index++] = buff[i];
			}
		}

		if (isMove && buff[i] == ' ') {
			isMove = false;
		}
	}
}