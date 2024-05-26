#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h> // _getch()
#include <algorithm> // reverse function

using namespace std;

const int SIZE = 4;

void initializeBoard(vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }
}

void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0)
                cout << setw(4) << ".";
            else
                cout << setw(4) << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void addRandomTile(vector<vector<int>>& board) {
    vector<pair<int, int>> emptyTiles;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyTiles.push_back(make_pair(i, j));
            }
        }
    }

    if (!emptyTiles.empty()) {
        int index = rand() % emptyTiles.size();
        board[emptyTiles[index].first][emptyTiles[index].second] = (rand() % 2 + 1) * 2;
    }
}

bool canMove(const vector<vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) return true;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return true;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return true;
        }
    }
    return false;
}

bool slideAndMergeRow(vector<int>& row) {
    bool moved = false;
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (row[j] == 0 && row[j + 1] != 0) {
                row[j] = row[j + 1];
                row[j + 1] = 0;
                moved = true;
            }
        }
    }
    for (int i = 0; i < SIZE - 1; ++i) {
        if (row[i] == row[i + 1] && row[i] != 0) {
            row[i] *= 2;
            row[i + 1] = 0;
            moved = true;
        }
    }
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - 1; ++j) {
            if (row[j] == 0 && row[j + 1] != 0) {
                row[j] = row[j + 1];
                row[j + 1] = 0;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveLeft(vector<vector<int>>& board) {
    bool moved = false;
    for (int i = 0; i < SIZE; ++i) {
        if (slideAndMergeRow(board[i])) {
            moved = true;
        }
    }
    return moved;
}

bool moveRight(vector<vector<int>>& board) {
    bool moved = false;
    for (int i = 0; i < SIZE; ++i) {
        reverse(board[i].begin(), board[i].end());
        if (slideAndMergeRow(board[i])) {
            moved = true;
        }
        reverse(board[i].begin(), board[i].end());
    }
    return moved;
}

bool moveUp(vector<vector<int>>& board) {
    bool moved = false;
    for (int j = 0; j < SIZE; ++j) {
        vector<int> column(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            column[i] = board[i][j];
        }
        if (slideAndMergeRow(column)) {
            moved = true;
        }
        for (int i = 0; i < SIZE; ++i) {
            board[i][j] = column[i];
        }
    }
    return moved;
}

bool moveDown(vector<vector<int>>& board) {
    bool moved = false;
    for (int j = 0; j < SIZE; ++j) {
        vector<int> column(SIZE);
        for (int i = 0; i < SIZE; ++i) {
            column[i] = board[i][j];
        }
        reverse(column.begin(), column.end());
        if (slideAndMergeRow(column)) {
            moved = true;
        }
        reverse(column.begin(), column.end());
        for (int i = 0; i < SIZE; ++i) {
            board[i][j] = column[i];
        }
    }
    return moved;
}

int main() {
    srand(time(0));
    vector<vector<int>> board(SIZE, vector<int>(SIZE));
    initializeBoard(board);
    addRandomTile(board);
    addRandomTile(board);

    while (true) {
        printBoard(board);
        if (!canMove(board)) {
            cout << "Game Over!" << endl;
            break;
        }

        char move;
        move = _getch(); //get input without pressing enter
        bool moved = false;
        switch (move) {
            case 'w': moved = moveUp(board); break;
            case 's': moved = moveDown(board); break;
            case 'a': moved = moveLeft(board); break;
            case 'd': moved = moveRight(board); break;
            default: cout << "Invalid move! Use w, a, s, d keys to move." << endl;
        }

        if (moved) {
            addRandomTile(board);
        }
    }

    return 0;
}
