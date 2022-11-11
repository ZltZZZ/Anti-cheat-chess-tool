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

typedef enum _engine_command_type {
	COMMAND_TYPE_PASSTHROUGH, // Send command without response
	COMMAND_TYPE_GET_ANSW     // Send command and wait for answer
} engine_command_type;

typedef enum _engine_command {
	UCI,
	DEBUG_ON,
	DEBUG_OFF,
	IS_READY,
	SET_OPTION,
	UCI_NEW_GAME,
	DO_NEXT_MOVE,
	START_ANALYZE,
	STOP_ANALYZE,
	QUIT_ENGINE
} engine_command;

typedef enum _engine_answers {
	UCI_OK,
	READY_OK,
	NORMAL_ANSW,
	NO_ANSW
} engine_answers;

typedef struct _engine
{
	LPCWSTR path_to_engine;         // Full path to engine.exe
	HANDLE pipe_in_w;               // Used by app to send msg to engine
	HANDLE pipe_out_r;              // Used by app to recieve msg from engine
	enum _engine_state state;       // Current state of engine (working or not and so on)
} engine;


/* Initialize all fields with NULL and copy path to field path_to_engine[]. */
void init_engine_struct(engine*, LPCWSTR path_to_engine);

/* Call after init_engine_struct. Create new thread and 2 pipes for communication. Run chess_engine.exe. */
engine_error engine_load(engine* ptr_to_engine);

/* Closes engine. */
void engine_close(engine* ptr_to_engine);

/* Send a fixed specified command to engine process. */
void engine_send_command(engine*, engine_command_type, engine_command, char* buff_answ);

/* Set options for engine and send them to engine process. */
void engine_set_options();

/* Look at answer and return one of the engine_answers*/
engine_answers engine_identify_answer(char* answ);


