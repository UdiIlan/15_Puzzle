#include "15_Puzzle.h"

bool Test_InitBoard_EachValueOnlyOnce();
bool Test_InitBoard_DifferentBoardsEveryCall();
void GetSetBoard(Board& board);
bool Test_IsBoardSolvable_SolvableEvenInversions();
bool Test_IsBoardSolvable_SolvableOddInversions();
bool Test_IsBoardSolvable_UnsolvableEvenInversions();
bool Test_IsBoardSolvable_UnsolvableOddInversions();
bool Test_PlayMove_Up();
bool Test_PlayMove_Down();
bool Test_PlayMove_Left();
bool Test_PlayMove_Right();
bool Test_IsMoveLegal_UpLegal();
bool Test_IsMoveLegal_UpIllegal();
bool Test_IsMoveLegal_DownLegal();
bool Test_IsMoveLegal_DownIllegal();
bool Test_IsMoveLegal_LeftLegal();
bool Test_IsMoveLegal_LeftIllegal();
bool Test_IsMoveLegal_RightLegal();
bool Test_IsMoveLegal_RightIllegal();
bool Test_DidPlayerWin_Yes();
bool Test_DidPlayerWin_No();
bool Test_GetValidCharInput_Valid();
bool Test_GetValidCharInput_InValidExtraChars();
bool Test_GetValidCharInput_InValidWrongChar();

int test_main()
{
	if (!Test_InitBoard_EachValueOnlyOnce()) return -1;
	if (!Test_InitBoard_DifferentBoardsEveryCall()) return -1;
	if (!Test_IsBoardSolvable_SolvableEvenInversions()) return -1;
	if (!Test_IsBoardSolvable_SolvableOddInversions()) return -1;
	if (!Test_IsBoardSolvable_UnsolvableEvenInversions()) return -1;
	if (!Test_IsBoardSolvable_UnsolvableOddInversions()) return -1;
	if (!Test_PlayMove_Up()) return -1;
	if (!Test_PlayMove_Down()) return -1;
	if (!Test_PlayMove_Left()) return -1;
	if (!Test_PlayMove_Right()) return -1;
	if (!Test_IsMoveLegal_UpLegal()) return -1;
	if (!Test_IsMoveLegal_UpIllegal()) return -1;
	if (!Test_IsMoveLegal_DownLegal()) return -1;
	if (!Test_IsMoveLegal_DownIllegal()) return -1;
	if (!Test_IsMoveLegal_LeftLegal()) return -1;
	if (!Test_IsMoveLegal_LeftIllegal()) return -1;
	if (!Test_IsMoveLegal_RightLegal()) return -1;
	if (!Test_IsMoveLegal_RightIllegal()) return -1;
	if (!Test_DidPlayerWin_Yes()) return -1;
	if (!Test_DidPlayerWin_No()) return -1;
	if (!Test_GetValidCharInput_Valid()) return -1;
	if (!Test_GetValidCharInput_InValidExtraChars()) return -1;
	if (!Test_GetValidCharInput_InValidWrongChar()) return -1;

	return 0;
}

bool Test_InitBoard_EachValueOnlyOnce()
{
	Board test_board;
	AllocateBoard(test_board, BOARD_SIZE);
	int empty_row, empty_col;
	InitBoard(test_board, empty_row, empty_col);

	// Checking that each value exists on the board exactly once
	vector<int> values;
	values.resize(BOARD_SIZE * BOARD_SIZE);
	for (unsigned int value_index = 0; value_index < values.size(); ++value_index)
	{
		values[value_index] = 0;
	}
	
	for (unsigned int row_index = 0; row_index < test_board.size(); ++row_index)
	{
		for (unsigned int col_index = 0; col_index < test_board[0].size(); ++col_index)
		{
			values[test_board[row_index][col_index] - 1]++;
		}
	}

	bool success = true;
	for (unsigned int value_index = 0; value_index < values.size() && success; ++value_index)
	{
		if (values[value_index] != 1)
		{
			success = false;
		}
	}
	return success;
}

bool Test_InitBoard_DifferentBoardsEveryCall()
{
	Board test_board1, test_board2;
	AllocateBoard(test_board1, BOARD_SIZE);
	int empty_row, empty_col;
	InitBoard(test_board1, empty_row, empty_col);
	AllocateBoard(test_board2, BOARD_SIZE);
	InitBoard(test_board2, empty_row, empty_col);
	bool identical_boards = true;
	for (unsigned int row_index = 0; row_index < test_board1.size() && identical_boards; ++row_index)
	{
		for (unsigned int col_index = 0; col_index < test_board1[0].size() && identical_boards; ++col_index)
		{
			if (test_board1[row_index][col_index] != test_board2[row_index][col_index])
			{
				identical_boards = false;
			}
		}
	}

	return !identical_boards;
}

void GetSetBoard(Board& board)
{
	AllocateBoard(board, BOARD_SIZE);
	int curr_element = 0;
	for (unsigned int row_index = 0; row_index < board.size(); ++row_index)
	{
		for (unsigned int col_index = 0; col_index < board[0].size(); ++col_index)
		{
			++curr_element;
			board[row_index][col_index] = curr_element;
		}
	}
}

bool Test_IsBoardSolvable_SolvableEvenInversions()
{
	Board test_board;
	GetSetBoard(test_board);
	
	// Setting 1 inversion on the board
	test_board[0][0] = 2;
	test_board[0][1] = 1;

	// Setting the empty cell on an odd row (creates 2 * BOARD_SIZE - 1 inversions)
	test_board[BOARD_SIZE - 3][BOARD_SIZE - 1] = BOARD_SIZE * BOARD_SIZE;
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = (BOARD_SIZE - 2) * BOARD_SIZE;
	
	return IsBoardSolvable(test_board, 3);
}

bool Test_IsBoardSolvable_SolvableOddInversions()
{
	Board test_board;
	GetSetBoard(test_board);

	// Setting the empty cell on an even row (creates (BOARD_SIZE - 1) * BOARD_SIZE - 1 inversions)
	test_board[0][BOARD_SIZE - 1] = BOARD_SIZE * BOARD_SIZE;
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = BOARD_SIZE;

	return IsBoardSolvable(test_board, BOARD_SIZE);
}

bool Test_IsBoardSolvable_UnsolvableEvenInversions()
{
	Board test_board;
	GetSetBoard(test_board);

	// Setting the empty cell on an odd row (creates 2 * BOARD_SIZE - 1 inversions)
	test_board[BOARD_SIZE - 3][BOARD_SIZE - 1] = BOARD_SIZE * BOARD_SIZE;
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = (BOARD_SIZE - 2) * BOARD_SIZE;

	return !IsBoardSolvable(test_board, 3);
}

bool Test_IsBoardSolvable_UnsolvableOddInversions()
{
	Board test_board;
	GetSetBoard(test_board);

	// Setting 1 inversions on the board
	test_board[0][0] = 2;
	test_board[0][1] = 1;

	// Setting the empty cell on an even row (creates (BOARD_SIZE - 1) * BOARD_SIZE - 1 inversions)
	test_board[0][BOARD_SIZE - 1] = BOARD_SIZE * BOARD_SIZE;
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = BOARD_SIZE;

	return !IsBoardSolvable(test_board, BOARD_SIZE);
}

bool Test_PlayMove_Up()
{
	Board test_board;
	GetSetBoard(test_board);
	int empty_row = BOARD_SIZE - 1;
	int empty_col = BOARD_SIZE - 1;
	PlayMove(test_board, UP_MOVE, empty_row, empty_col);
	return empty_row == BOARD_SIZE - 2 && empty_col == BOARD_SIZE - 1 &&
		test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] == (BOARD_SIZE - 1) * BOARD_SIZE &&
		test_board[BOARD_SIZE - 2][BOARD_SIZE - 1] == EMPTY_ELEMENT;
}

bool Test_PlayMove_Down()
{
	Board test_board;
	GetSetBoard(test_board);
	test_board[BOARD_SIZE - 2][BOARD_SIZE - 1] = EMPTY_ELEMENT;
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = (BOARD_SIZE - 1) * BOARD_SIZE;
	int empty_row = BOARD_SIZE - 2;
	int empty_col = BOARD_SIZE - 1;
	PlayMove(test_board, DOWN_MOVE, empty_row, empty_col);
	return empty_row == BOARD_SIZE - 1 && empty_col == BOARD_SIZE - 1 &&
		test_board[BOARD_SIZE - 2][BOARD_SIZE - 1] == (BOARD_SIZE - 1) * BOARD_SIZE &&
		test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] == EMPTY_ELEMENT;
}

bool Test_PlayMove_Left()
{
	Board test_board;
	GetSetBoard(test_board);
	int empty_row = BOARD_SIZE - 1;
	int empty_col = BOARD_SIZE - 1;
	PlayMove(test_board, LEFT_MOVE, empty_row, empty_col);
	return empty_row == BOARD_SIZE - 1 && empty_col == BOARD_SIZE - 2 &&
		test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] == BOARD_SIZE * BOARD_SIZE - 1 &&
		test_board[BOARD_SIZE - 1][BOARD_SIZE - 2] == EMPTY_ELEMENT;
}

bool Test_PlayMove_Right()
{
	Board test_board;
	GetSetBoard(test_board);
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 2] = EMPTY_ELEMENT;
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = BOARD_SIZE * BOARD_SIZE - 1;
	int empty_row = BOARD_SIZE - 1;
	int empty_col = BOARD_SIZE - 2;
	PlayMove(test_board, RIGHT_MOVE, empty_row, empty_col);
	return empty_row == BOARD_SIZE - 1 && empty_col == BOARD_SIZE - 1 &&
		test_board[BOARD_SIZE - 1][BOARD_SIZE - 2] == BOARD_SIZE * BOARD_SIZE - 1 &&
		test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] == EMPTY_ELEMENT;
}

bool Test_IsMoveLegal_UpLegal()
{
	return IsMoveLegal(BOARD_SIZE, BOARD_SIZE, UP_MOVE, BOARD_SIZE - 1, BOARD_SIZE - 1);
}

bool Test_IsMoveLegal_UpIllegal()
{
	return !IsMoveLegal(BOARD_SIZE, BOARD_SIZE, UP_MOVE, 0, BOARD_SIZE - 1);
}

bool Test_IsMoveLegal_DownLegal()
{
	return IsMoveLegal(BOARD_SIZE, BOARD_SIZE, DOWN_MOVE, 0, BOARD_SIZE - 1);
}

bool Test_IsMoveLegal_DownIllegal()
{
	return !IsMoveLegal(BOARD_SIZE, BOARD_SIZE, DOWN_MOVE, BOARD_SIZE - 1, BOARD_SIZE - 1);
}

bool Test_IsMoveLegal_LeftLegal()
{
	return IsMoveLegal(BOARD_SIZE, BOARD_SIZE, LEFT_MOVE, BOARD_SIZE - 1, BOARD_SIZE - 1);
}

bool Test_IsMoveLegal_LeftIllegal()
{
	return !IsMoveLegal(BOARD_SIZE, BOARD_SIZE, LEFT_MOVE, BOARD_SIZE - 1, 0);
}
bool Test_IsMoveLegal_RightLegal()
{
	return IsMoveLegal(BOARD_SIZE, BOARD_SIZE, RIGHT_MOVE, BOARD_SIZE - 1, 0);
}
bool Test_IsMoveLegal_RightIllegal()
{
	return !IsMoveLegal(BOARD_SIZE, BOARD_SIZE, RIGHT_MOVE, BOARD_SIZE - 1, BOARD_SIZE - 1);
}

bool Test_DidPlayerWin_Yes()
{
	Board test_board;
	GetSetBoard(test_board);
	return DidPlayerWin(test_board);
}

bool Test_DidPlayerWin_No()
{
	Board test_board;
	GetSetBoard(test_board);
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 2] = EMPTY_ELEMENT;
	test_board[BOARD_SIZE - 1][BOARD_SIZE - 1] = BOARD_SIZE * BOARD_SIZE - 1;
	return !DidPlayerWin(test_board);
}

bool Test_GetValidCharInput_Valid()
{
	stringstream input, output;
	input << "y";
	return GetValidCharInput("qy", input, output) == 'y';
}

bool Test_GetValidCharInput_InValidExtraChars()
{
	stringstream input, output;
	input << "yq" << endl << "q";
	return GetValidCharInput("qy", input, output) == 'q';
}

bool Test_GetValidCharInput_InValidWrongChar()
{
	stringstream input, output;
	input << "r" << endl << "q";
	return GetValidCharInput("qy", input, output) == 'q';
}
