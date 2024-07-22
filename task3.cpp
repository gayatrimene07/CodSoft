#include <iostream>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

void displayBoard() {
    cout << "Current board state:" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
            if (j < SIZE - 1) cout << "| ";
        }
        cout << endl;
        if (i < SIZE - 1) cout << "--+---+--" << endl;
    }
}

bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

bool checkDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }
    return true;
}

void updateBoard(char player, int move) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == (char)(move + '0')) {
                board[i][j] = player;
                return;
            }
        }
    }
}

void resetBoard() {
    char num = '1';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = num++;
        }
    }
}

int main() {
    char player = 'X';
    char continueGame;

    do {
        int move;
        resetBoard();
        while (true) {
            displayBoard();
            cout << "Player " << player << ", enter your move (1-9): ";
            cin >> move;

            updateBoard(player, move);

            if (checkWin(player)) {
                displayBoard();
                cout << "Player " << player << " wins!" << endl;
                break;
            }
            if (checkDraw()) {
                displayBoard();
                cout << "The game is a draw!" << endl;
                break;
            }

            // Switch player
            player = (player == 'X') ? 'O' : 'X';
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> continueGame;
    } while (continueGame == 'y' || continueGame == 'Y');

    cout << "Thanks for playing!" << endl;
    return 0;
}



