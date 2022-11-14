#include "DEC_module.h"

void analize_move(engine* engn, char* move, suspect_portrait* susp, thc::ChessRules* cr) {
	attr_set attr_st;
	std::string fen_string;
	engine_line line[OPTION_MULTI_PV_DEF];

	// 1. Gets FEN of position
	fen_string = cr->ForsythPublish();

	// 2. Parse that FEN
	get_attr_set(fen_string.c_str(), &attr_st);

	// 3. Feed FEN to engine. Get answer of engine.
	engine_set_position(engn, (char*)"rn1qk1nr/pp3ppp/4p3/2bpPb2/8/2P2N2/PP2BPPP/RNBQK2R b KQkq - 0 1");
	engine_send_command_start_analyze(engn, 1);
	engine_parse_analisys_output(engn, line);

	// 4. Get accuracy evaluation

}