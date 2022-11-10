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
		engn->state = WORKING;
		return ENGINE_LOAD_OK;
	}
	else {
		return ENGINE_LOAD_FAIL;
	}
}

void engine_close(engine* engn) {
	//òóò äîáàâèòü îòïðàâêó êîìàíäû äâèæêó çàâåðøèòü ðàáîòó (quit)
	close_stream_handle(&engn->pipe_in_w);
	close_stream_handle(&engn->pipe_out_r);
	engn->state = NOT_LOADED;
}
