#include "DataBase_parser.h"
#include <ctime>

void set_parser_params(parser* prsr, int min_elo, int max_elo, _event evnt, char* name, char* path_to_db, int max_count_of_moves, int max_count_of_games) {
	prsr->fiter.elo_min = min_elo;
	prsr->fiter.elo_max = max_elo;
	prsr->fiter.evnt = evnt;
	prsr->fiter.max_count_of_games = max_count_of_games;
	prsr->fiter.max_count_of_moves = max_count_of_moves;
	if (name != NULL) {
		memcpy(prsr->fiter.name, name, sizeof(char) * MAX_NAME_SIZE);
	}
	else {
		memset(prsr->fiter.name, '\0', sizeof(char) * MAX_NAME_SIZE);
	}

	memcpy(prsr->db.path_to_db, path_to_db, sizeof(char) * MAX_PATH_LENTH);

	prsr->db.buff = (char*)malloc(sizeof(char) * MAX_BUFF_SIZE);
	prsr->db.buff_ptr = MAX_BUFF_SIZE;
}

void free_parser_buff(parser* prsr) {
	free(prsr->db.buff);
}

void game_clear(game* gm) {
	gm->elo_black = 0;
	gm->elo_white = 0;
	gm->evnt = EVENT_UNDEFINED;
	memset(gm->moves, '\0', sizeof(char) * MAX_WORD_SIZE);
	memset(gm->name_black, '\0', sizeof(char) * MAX_NAME_SIZE);
	memset(gm->name_white, '\0', sizeof(char) * MAX_NAME_SIZE);
}

int get_next_game(parser* prsr, game* gm) {
	// There are main parsing algorithm
	tag tag_name;
	char* ptr_value = NULL;
	char c;
	int count = 0;
	bool isTag = false, isMove = false, isWord = false;
	char word[MAX_WORD_SIZE] = { '\0' };
	int word_indx = 0;
	time_t before, after;

	//if (prsr->db.buff_ptr == MAX_BUFF_SIZE) {
	//	get_next_page(prsr);
	//	prsr->db.buff_ptr = 0;
	//}
	// Seacrh until needed game is not found or end of databse isn't reached
	before = clock();
	game_clear(gm);
	while (!feof(prsr->db.pgn_db) || prsr->db.buff_ptr != MAX_BUFF_SIZE)
	{
		if (prsr->db.buff_ptr == MAX_BUFF_SIZE) {
			get_next_page(prsr);
			prsr->db.buff_ptr = 0;
		}

		while (prsr->db.buff_ptr < MAX_BUFF_SIZE) {
			c = prsr->db.buff[prsr->db.buff_ptr++];

			if (c == '\n') {
				if (isMove == true && check_filter(prsr, gm) == true) { // Move section reached
					move_parser(gm, word);
					isMove = false;
					return DB_SUCCESS;
				}
				else if (isMove == true) // Didn't pass the filter
				{
					game_clear(gm);
					count++;
					if (count % 10000000 == 0) {
						after = clock();
						printf("still finding: %d, time: %f\n", count, (after - before) / 1000.0);
						before = after;
					}
				}

				if (isTag == true) {
					//parse tag
					tag_name = get_tag_name(word);
					ptr_value = get_tag_value(word);
					fill_tag_in_game(gm, tag_name, ptr_value);
					isTag = false;
				}

				if (isWord == true) {
					isWord = false;
					word_indx = 0;
					memset(word, '\0', sizeof(char) * MAX_WORD_SIZE);
				}
			}
			else {
				if (isWord == false) {
					if (c == '[') {
						isTag = true;
					}
					else {
						isMove = true;
					}

					isWord = true;
				}

				if (word_indx < MAX_WORD_SIZE)
					word[word_indx++] = c;
			}
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
	int size = strlen(buff);
	for (int i = 0; i < size; i++) {
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

	if (prsr->fiter.name[0] == '\0' && prsr->fiter.elo_max != NO_RATING && (avrg_elo == NO_RATING || avrg_elo < prsr->fiter.elo_min || avrg_elo > prsr->fiter.elo_max)) {
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
	char possibleChars_start[] = "abcdefghNBRQKO";
	char possibleChars_move[] = "12345678abcdefghNBRQKx=O- ";
	int gm_index = 0;
	int size = strlen(buff);

	for (int i = 0; i < size; i++) {
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

void get_next_page(parser* prsr) {
	fread(prsr->db.buff, sizeof(char), MAX_BUFF_SIZE, prsr->db.pgn_db);
}