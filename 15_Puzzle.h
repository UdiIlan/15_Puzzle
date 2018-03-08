#ifndef PUZZLE
#define PUZZLE

#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>
#include <sstream>

using namespace std;

typedef vector<vector<int> > Board;

void AllocateBoard(Board& board, int size);
void InitBoard(Board& board, int& empty_row, int& empty_col);
bool IsBoardSolvable(Board& board, int empty_row);
void PlayMove(Board& board, char move_direction, int& empty_row, int& empty_col);
bool IsMoveLegal(int board_height, int board_width, char move_direction, int empty_row, int empty_col);
bool DidPlayerWin(Board& board);
void PrintBoard(Board& board);
char GetValidCharInput(const char* valid_charset, istream& in, ostream& out);
void SwapCells(Board& board, int row1, int col1, int row2, int col2);

// Global consts
const char UP_MOVE = 'u';
const char DOWN_MOVE = 'd';
const char RIGHT_MOVE = 'r';
const char LEFT_MOVE = 'l';
const int BOARD_SIZE = 4;
const char move_inputs[] = { UP_MOVE, DOWN_MOVE, RIGHT_MOVE, LEFT_MOVE, '\0' };
const int EMPTY_ELEMENT = BOARD_SIZE * BOARD_SIZE;

#endif