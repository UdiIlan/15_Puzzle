#include "15_Puzzle.h"

int main()
{
	const char QUIT_GAME = 'q';
	const char NEW_GAME = 'y';
	const char game_inputs[] = { QUIT_GAME, NEW_GAME, '\0' };
	printf("Welcome to 15 puzzle!\n");
	char start_game_input = '\0';
	bool is_board_allocated = false;
	Board game_board;
	while (start_game_input != QUIT_GAME)
	{
		printf("Insert %c to start a new game or %c to quit: ", NEW_GAME, QUIT_GAME);
		
		start_game_input = GetValidCharInput(game_inputs, cin, cout);
		if (start_game_input == NEW_GAME)
		{
			printf("Starting a new game\n");
			if (!is_board_allocated)
			{
				AllocateBoard(game_board, BOARD_SIZE);
				is_board_allocated = true;
			}

			// Initializing the board until it's sovable and not already solved
			int empty_row = 0;
			int empty_col = 0;
			InitBoard(game_board, empty_row, empty_col);
			while (!IsBoardSolvable(game_board, empty_row) || DidPlayerWin(game_board))
			{
				InitBoard(game_board, empty_row, empty_col);
			}

			// Making moves until the game is solved
			bool first_move = true;
			while (first_move || !DidPlayerWin(game_board))
			{
				first_move = false;
				PrintBoard(game_board);
				printf("Insert direction to move the empty tile: %c for up, %c for down, %c for left or %c for right\n", UP_MOVE, DOWN_MOVE, LEFT_MOVE, RIGHT_MOVE);
				char curr_move = GetValidCharInput(move_inputs, cin, cout);
				while (!IsMoveLegal(game_board.size(), game_board[0].size(), curr_move, empty_row, empty_col))
				{
					printf("Ilegal move. Insert direction to move the empty tile: %c for up, %c for down, %c for left or %c for right\n", UP_MOVE, DOWN_MOVE, LEFT_MOVE, RIGHT_MOVE);
					curr_move = GetValidCharInput(move_inputs, cin, cout);
				}
				PlayMove(game_board, curr_move, empty_row, empty_col);
			}
			PrintBoard(game_board);
			printf("Well done!\n");
		}
	}
	
	printf("Goodbye\n");
	return 0;
}

void AllocateBoard(Board& board, int size)
{
	// Creating a square int matrix of size * size rows and columns
	board.resize(size);
	for (int row_index = 0; row_index < size; ++row_index)
	{
		board[row_index].resize(size);
	}
}

// Initializes a random board
void InitBoard(Board& board, int& empty_row, int& empty_col)
{
	// Creating a linked list of num_of_elements length that contains the
	// numbers 1..num_of_elements
	int num_of_elements = board.size() * board[0].size();
	list<int> elements;
	for (int curr_element = 1; curr_element <= num_of_elements; ++curr_element)
	{
		elements.push_back(curr_element);
	}

	// Creating a random generator with the current timestamp as the seed
	default_random_engine generator;
	chrono::high_resolution_clock::time_point time_seed = chrono::high_resolution_clock::now();
	generator.seed((unsigned int)time_seed.time_since_epoch().count());

	// Getting the elements in a random order
	for (int curr_element = 1; curr_element <= num_of_elements; ++curr_element)
	{
		uniform_int_distribution<int> distribution(0, elements.size() - 1);
		int curr_board_element_index = distribution(generator);
		int selected_element = 0;
		list<int>::iterator elements_it = elements.begin();
		for (int skip_index = 0; skip_index < curr_board_element_index; ++skip_index)
		{
			++elements_it;
		}
		
		// Setting the element in the board
		board[(curr_element - 1) / board.size()][(curr_element - 1) % board[0].size()] = *elements_it;
		if (*elements_it == EMPTY_ELEMENT)
		{
			empty_row = (curr_element - 1) / board.size();
			empty_col = (curr_element - 1) % board[0].size();
		}
		elements.erase(elements_it);
	}
}

// Checks whether the randomly created board is solvable
bool IsBoardSolvable(Board& board, int empty_row)
{
	// Counting the # of inversions in the board
	int inversions_conter = 0;
	for (unsigned int row_index = 0; row_index < board.size(); ++row_index)
	{
		for (unsigned int col_index = 0; col_index < board[0].size(); ++col_index)
		{
			if (board[row_index][col_index] > 1 && board[row_index][col_index] != EMPTY_ELEMENT)
			{
				for (unsigned int inversion_row_index = row_index; inversion_row_index < board.size(); ++inversion_row_index)
				{
					int inversion_col_start = 0;
					if (inversion_row_index == row_index)
					{
						// Iterating the row only from the next column
						inversion_col_start = col_index + 1;
					}
					for (unsigned int inversion_col_index = inversion_col_start; inversion_col_index < board[0].size(); ++inversion_col_index)
					{
						// If the current element is bigger than elements after it in the board then it's counted as an inversion
						if (board[row_index][col_index] > board[inversion_row_index][inversion_col_index])
						{
							++inversions_conter;
						}
					}
				}
			}
		}
	}

	// For odd boards there's a solution if the # of inversions is even
	if (board.size() % 2 == 1 && inversions_conter % 2 == 0)
	{
		return true;
	}
	// For even boards,	if the sum of number of inversions and the empty tile
	// is row (from the end) is odd then there's a solution
	else if (board.size() % 2 == 0 && ((inversions_conter + board.size() - empty_row) % 2) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlayMove(Board& board, char move_direction, int& empty_row, int& empty_col)
{
	switch (move_direction)
	{
	case UP_MOVE:
		SwapCells(board, empty_row, empty_col, empty_row - 1, empty_col);
		--empty_row;
		break;
	case DOWN_MOVE:
		SwapCells(board, empty_row, empty_col, empty_row + 1, empty_col);
		++empty_row;
		break;
	case LEFT_MOVE:
		SwapCells(board, empty_row, empty_col, empty_row, empty_col - 1);
		--empty_col;
		break;
	case RIGHT_MOVE:
		SwapCells(board, empty_row, empty_col, empty_row, empty_col + 1);
		++empty_col;
		break;
	default:
		break;
	}
}

bool IsMoveLegal(int board_height, int board_width, char move_direction, int empty_row, int empty_col)
{
	bool is_move_legal = true;
	switch (move_direction)
	{
	case UP_MOVE:
		if (empty_row == 0)
		{
			is_move_legal = false;
		}
		break;
	case DOWN_MOVE:
		if (empty_row == board_height - 1)
		{
			is_move_legal = false;
		}
		break;
	case LEFT_MOVE:
		if (empty_col == 0)
		{
			is_move_legal = false;
		}
		break;
	case RIGHT_MOVE:
		if (empty_col == board_width - 1)
		{
			is_move_legal = false;
		}
		break;
	default:
		is_move_legal = false;
		break;
	}
	return is_move_legal;
}

// Checks whether the board is set in a way so that the player achived the goal
bool DidPlayerWin(Board& board)
{
	bool did_player_win = false;

	// Checking that the blank tile is at the correct place
	if (board[board.size() - 1][board[0].size() - 1] == EMPTY_ELEMENT)
	{
		did_player_win = true;
		unsigned int element_order = 1;
		for (unsigned int row_index = 0; row_index < board.size() && did_player_win; ++row_index)
		{
			for (unsigned int col_index = 0; col_index < board[0].size() && did_player_win && element_order < (board.size() * board[0].size()); ++col_index)
			{
				if (board[row_index][col_index] != element_order)
				{
					did_player_win = false;
				}
				element_order++;
			}
		}
	}
	return did_player_win;
}

// Printing the board, each cell gets up to 2 characters and a space
void PrintBoard(Board& board)
{
	for (unsigned int row_index = 0; row_index < board.size(); ++row_index)
	{
		for (unsigned int col_index = 0; col_index < board[0].size(); ++col_index)
		{
			if (board[row_index][col_index] == EMPTY_ELEMENT)
			{
				printf("  X");
			}
			else
			{
				printf("%3d", board[row_index][col_index]);
			}
		}
		printf("\n");
	}
}


// Get a single char input that's a part of a list of valid characters
char GetValidCharInput(const char* valid_charset, istream& in, ostream& out)
{
	string input;
	string valid_chars(valid_charset);
	getline(in, input);
	while (input.length() > 1 || valid_chars.find(input.at(0)) == string::npos)
	{
		out << "Invalid input, please retry\n";
		getline(in, input);
	}

	return input.at(0);
}

void SwapCells(Board& board, int row1, int col1, int row2, int col2)
{
	int temp = board[row1][col1];
	board[row1][col1] = board[row2][col2];
	board[row2][col2] = temp;
}
