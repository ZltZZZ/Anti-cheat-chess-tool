#include <iostream>
#include "Chessboard_handler.h"

using namespace std;

int main()
{
    char chessboard[MAX_NUMBER_OF_FIGURES_OF_EACH_KIND][MAX_NUMBER_OF_COLORS][MAX_NUMBER_OF_FIGURES_ON_BOARD * MULTIPLIER_VERT_NAME_HORIZ_NUMBER] = { NULL_VALUE };
    char move[MAX_MOVE_LENTH_LAN] = { NULL_VALUE };

    initialize_start_position_on_board(chessboard);
}
