#include "Engine_handler.h"
#include <string.h>

void init_engine_struct(engine* engn, LPCWSTR path_to_engine) {
	engn->path_to_engine = path_to_engine;
	engn->pipe_in_w = NULL;
	engn->pipe_out_r = NULL;
	engn->state = NOT_LOADED;
}

engine_error engine_load(engine* engn) {
	// Creates an engine process (run engine.exe)
	if (create_process(engn->path_to_engine, &engn->pipe_in_w, &engn->pipe_out_r) == PROCESS_CREATE_OK) {
		char answ[MAX_MSG_SIZE] = { '\0' };

		// Wait for initializing of engine (synchronize engine and app) (wait answ)
		wait_for_answ(&engn->pipe_out_r);
		clean_pipe_out(&engn->pipe_out_r);

		// Send command "uci" as specificated in uci protocol docs
		engine_send_command(engn, COMMAND_TYPE_GET_ANSW, UCI, answ);
		if (engine_identify_answer(answ) != UCI_OK) {
			return ENGINE_LOAD_FAIL;
		}

		engn->state = WORKING;
		return ENGINE_LOAD_OK;
	}
	else {
		return ENGINE_LOAD_FAIL;
	}
}

void engine_close(engine* engn) {
	engine_send_command(engn, COMMAND_TYPE_PASSTHROUGH, QUIT_ENGINE, NULL);
	close_stream_handle(&engn->pipe_in_w);
	close_stream_handle(&engn->pipe_out_r);
	engn->state = NOT_LOADED;
}

/* Send command to engine. If command type set as COMMAND_TYPE_PASSTHROUGH, than buff_answ should be set as NULL*/
void engine_send_command(engine* engn, engine_command_type command_type, engine_command command, char* buff_answ) {
	char msg[MAX_MSG_SIZE] = { '\0' };

	switch (command)
	{
	case UCI:
		memcpy(msg, "uci\n", sizeof(char) * 5);
		break;
	case DEBUG_ON:
		break;
	case DEBUG_OFF:
		break;
	case IS_READY:
		memcpy(msg, "isready\n", sizeof(char) * 9);
		break;
	case SET_OPTION:
		break;
	case UCI_NEW_GAME:
		memcpy(msg, "ucinewgame\n", sizeof(char) * 12);
		break;
	case DO_NEXT_MOVE:
		break;
	case START_ANALYZE:
		memcpy(msg, "go\n", sizeof(char) * 4);
		break;
	case STOP_ANALYZE:
		memcpy(msg, "stop\n", sizeof(char) * 6);
		break;
	case QUIT_ENGINE:
		memcpy(msg, "quit\n", sizeof(char) * 6);
		break;
	default:
		break;
	}

	switch (command_type)
	{
	case COMMAND_TYPE_PASSTHROUGH:
		send_message(&engn->pipe_in_w, msg);
		break;
	case COMMAND_TYPE_GET_ANSW:
		send_message(&engn->pipe_in_w, msg);
		wait_for_answ(&engn->pipe_out_r);
		recieve_message(&engn->pipe_out_r, buff_answ);
		break;
	default:
		break;
	}
}

void engine_set_options() {

}

engine_answers engine_identify_answer(char* answ) {
	if (answ[0] == '\0') {
		return NO_ANSW;
	}
	else if (strstr(answ, "uciok") != NULL)
	{
		return UCI_OK;
	}
	else if (strstr(answ, "readyok") != NULL) {
		return READY_OK;
	}
	else {
		return NORMAL_ANSW;
	}
}