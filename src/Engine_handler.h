#include "Process_handler.h"

enum _engine_state {
	NOT_LOADED,
	WORKING,
	THINKING
};

typedef enum _engine_error {
	ENGINE_LOAD_OK,
	ENGINE_LOAD_FAIL
} engine_error;

typedef struct _engine
{
	LPCWSTR path_to_engine;         // Full path to engine.exe
	HANDLE pipe_in_w;               // Used by app to send msg to engine
	HANDLE pipe_out_r;              // Used by app to recieve msg from engine
	enum _engine_state state;       // Current state of engine (working or not and so on)
} engine;


/* Initialize all fields with NULL and copy path to field path_to_engine[] */
void init_engine_struct(engine*, LPCWSTR path_to_engine);

/* Call after init_engine_struct. Create new thread and 2 pipes for communication. Run chess_engine.exe */
engine_error engine_load(engine* ptr_to_engine);

/* Closes engine. */
void engine_close(engine* ptr_to_engine);
