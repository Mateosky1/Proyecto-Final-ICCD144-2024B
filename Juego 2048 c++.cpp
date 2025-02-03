#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits> 

using namespace std;

const int SIZE = 4; 

struct Player {
    string name;
    int score;
};

vector<Player> leaderboard;

void printBoard(const vector<vector<int>>& board) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    cout << "2048\n";
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == 0) {
                cout << setw(5) << '.';
            } else {
                cout << setw(5) << cell;
            }
        }
        cout << endl;
    }
}

bool moveLeft(vector<vector<int>>& board, int& score) {
    bool moved = false;
    for (auto& row : board) {
        for (int i = 0; i < SIZE - 1; ++i) {
            for (int j = i + 1; j < SIZE; ++j) {
                if (row[j] == 0) continue;
                if (row[i] == 0) {
                    row[i] = row[j];
                    row[j] = 0;
                    moved = true;
                } else if (row[i] == row[j]) {
                    row[i] *= 2;
                    row[j] = 0;
                    score += row[i];
                    moved = true;
                }
                break;
            }
        }
    }
    return moved;
}

bool moveRight(vector<vector<int>>& board, int& score) {
    bool moved = false;
    for (auto& row : board) {
        for (int i = SIZE - 1; i > 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                if (row[j] == 0) continue;
                if (row[i] == 0) {
                    row[i] = row[j];
                    row[j] = 0;
                    moved = true;
                } else if (row[i] == row[j]) {
                    row[i] *= 2;
                    row[j] = 0;
                    score += row[i];
                    moved = true;
                }
                break;
            }
        }
    }
    return moved;
}

bool moveUp(vector<vector<int>>& board, int& score) {
    bool moved = false;
    for (int col = 0; col < SIZE; ++col) {
        for (int i = 0; i < SIZE - 1; ++i) {
            for (int j = i + 1; j < SIZE; ++j) {
                if (board[j][col] == 0) continue;
                if (board[i][col] == 0) {
                    board[i][col] = board[j][col];
                    board[j][col] = 0;
                    moved = true;
                } else if (board[i][col] == board[j][col]) {
                    board[i][col] *= 2;
                    board[j][col] = 0;
                    score += board[i][col];
                    moved = true;
                }
                break;
            }
        }
    }
    return moved;
}

bool moveDown(vector<vector<int>>& board, int& score) {
    bool moved = false;
    for (int col = 0; col < SIZE; ++col) {
        for (int i = SIZE - 1; i > 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                if (board[j][col] == 0) continue;
                if (board[i][col] == 0) {
                    board[i][col] = board[j][col];
                    board[j][col] = 0;
                    moved = true;
                } else if (board[i][col] == board[j][col]) {
                    board[i][col] *= 2;
                    board[j][col] = 0;
                    score += board[i][col];
                    moved = true;
                }
                break;
            }
        }
    }
    return moved;
}

void addRandomTile(vector<vector<int>>& board) {
    vector<pair<int, int>> emptySpaces;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptySpaces.emplace_back(i, j);
            }
        }
    }

    if (!emptySpaces.empty()) {
        auto [x, y] = emptySpaces[rand() % emptySpaces.size()];
        board[x][y] = (rand() % 2 + 1) * 2;
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

void showLeaderboard() {
    cout << "\n--- Puntajes ---\n";
    sort(leaderboard.begin(), leaderboard.end(), [](const Player& a, const Player& b) {
        return a.score > b.score;
    });

    for (size_t i = 0; i < min(leaderboard.size(), size_t(3)); ++i) {
        cout << i + 1 << ". " << leaderboard[i].name << " - " << leaderboard[i].score << endl;
    }
}

void playGame() {
    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));
    addRandomTile(board);
    addRandomTile(board);

    int score = 0;
    string playerName;

    cout << "Ingrese su nombre: ";
    cin >> playerName;

    while (true) {
        printBoard(board);
        cout << "Puntaje: " << score << endl;

        if (!canMove(board)) {
            cout << "Game Over!\n";
            leaderboard.push_back({playerName, score});
            break;
        }

        char move;
        cout << "Move (w/a/s/d): ";
        cin >> move;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        bool moved = false;
        if (move == 'w') moved = moveUp(board, score);
        else if (move == 'a') moved = moveLeft(board, score);
        else if (move == 's') moved = moveDown(board, score);
        else if (move == 'd') moved = moveRight(board, score);
        else {
            cout << "Movimiento invalido, intente nuevamente.\n";
            continue;
        }

        if (moved) {
            addRandomTile(board);
        }
    }
}

void showCredits() {
    cout << "\n--- Créditos ---\n";
    cout << "Desarrolladores del grupo:\n";
    cout << "1. Christopher Pulupa\n";
    cout << "2. JunxxxAnuelBrr\n";
}

int main() {
    srand(time(nullptr)); 

    while (true) {
        cout << "\n--- Menu ---\n";
        cout << "1. Jugar\n";
        cout << "2. Puntajes\n";
        cout << "3. Créditos\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";

        int option;
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (cin.fail() || option < 1 || option > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida, intente nuevamente.\n";
            continue;
        }

        switch (option) {
            case 1:
                playGame();
                break;
            case 2:
                showLeaderboard();
                break;
            case 3:
                showCredits();
                break;
            case 4:
                cout << "Saliendo del juego...\n";
                return 0;
        }
    }
}
