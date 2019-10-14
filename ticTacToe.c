/**
 * @file assignment-4.c
 *
 * This file implements a game of Tic-Tac-Toe (Naughts and Crosses).
 *
 * @date 09/24/2018
 * @author: Abinashi Singh
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Initialize the board to space characters as empty.
 *
 * @param board the board
 */
void initBoard(char board[3][3]) {

		for( int r=0; r<3; r++){				// for loop with variable r for row and c for column.
		for(int  c=0; c<3; c++){
			board[r][c] = ' ';					// initiated board array to an empty space characters.
		}
	}
}


/**
 * Mark the board position with the marker of a player (X or O).
 *
 * @param board the board
 * @param turn the marker for a player (X or O)
 * @param boardPos the row major position on the board (1-9)
 */
void markTheBoard(char board[3][3], char turn, int boardPos) {
	board[(boardPos-1) / 3][(boardPos-1) % 3]= turn;				// assigning the board array with formula for the row (positionof board-1/3)
																	// and for the column (position of board-1)%3).
																	// assigning it to the turn that will turn the marker for a player (X or O).
}

/**
 * Display the board.
 *
 * @param board the board.
 */
void displayBoard(char board[3][3]) {
	printf("---------------\n");
	for(int r=0; r<3; r++){
		printf("| %c | %c | %c |\n",board[r][0],board[r][1],board[r][2]);		// to print the structure of the game board.
		printf("---------------\n");
	}

}

/**
 * Determines whether given marker has won. Only if
 * marker has three columns in row or three rows in
 * column, or all in one of the two diagonals.
 *
 * @param board the board
 * @param marker the X or O marker
 * @return true if player with marker has won
 */
bool hasWon(const char board[3][3], char marker) {
	for(int r=0; r<3;r++){
		if(((board[r][0]==marker)&&(board[r][1]==marker))&&(board[r][2]==marker)){		//giving the winning case: if all the charachters in the row are same.
			return true;
		}
		if(((board[0][r]==marker)&&(board[1][r]==marker))&&(board[2][r]==marker)){		//giving the winning case: if all the charachters in columns are same.
			return true;
		}
		}
		if(((board[0][0]==marker)&&(board[1][1]==marker))&&(board[2][2]==marker)){		//the winning condition if the player is winning diagonally.
			return true;
		}
		if((board[0][2]==marker)&&(board[1][1]==marker)&&(board[2][0]==marker)){		//the winning condition if the player is winning diagonally.
			return true;
		}
		return false;
	}


/**
 * Determines whether there is a tie: all positions.
 * filled and no winner.
 *
 * @param board the board
 * @return true if the game is a tie, false otherwise
 */
bool isTie(const char board[3][3]) {
	const char *boardp=&board[0][0];
		for(int r=0; r<9; r++){
			if(*(boardp+r)== ' ') {							// giving the condition for a tie case.
				return false;								// if there is empty space then return false or in other words it's tie if all the positions are marked.
			}
		}
		if(!hasWon(board,'X')){								// second condition for a tie game. if the X has not one. then it is a tie.
			return true;
		}
		return false;
}

/**
 * Main program for an interactive game of tic-tac-toe.
 */
int main(void) {
	setbuf(stdout, NULL);
	char board[3][3];
	char turn = 'X';

	// initialize the board
	initBoard(board);

	printf("To play a position use the following map to enter a position.\n");
	printf("-------------\n");
	for (int boardPos = 1; boardPos <= 9; boardPos += 3) {
		printf("| %d | %d | %d |\n", boardPos, boardPos+1, boardPos+2);
		printf("-------------\n");
	}

	// play until there is a draw or a player has won
	while (!isTie(board) && !hasWon(board, 'X') && !hasWon(board, 'O')) {
		int boardPos = -1;
		bool validInput = false;

		// wait for valid input
		while(!validInput) {
			printf("Player %c, enter the position you want to play.\n", turn);
			int success = scanf("%d", &boardPos);
			if (success < 0 || boardPos < 0 || boardPos > 9 ||
				board[(boardPos-1) / 3][(boardPos-1) % 3] != ' ') {
				continue;
			}
			validInput = true;
		}

		// mark the position and display the updated board
		markTheBoard(board, turn, boardPos);

		// display the current board
		displayBoard(board);

		// other player's turn
		switch(turn) {
		case 'X':
			turn = 'O';
			break;
		case 'O':
			turn = 'X';
			break;
		}
	}

	// game over so report results
	if (isTie(board)) {
		printf("The game ends in a tie.\n");
	} else if (hasWon(board, 'X')) {
		printf("Player X has won.");
	} else {
		printf("Player O has won.");
	}
}
