#include <iostream>
#include <vector>

const int BOARD_COLS = 7;
const int BOARD_ROWS = 6;

class Board {
public:
    std::vector<std::vector<char>> board;
    int turns;
    std::vector<int> last_move; // [r, c]

    Board() : board(BOARD_ROWS, std::vector<char>(BOARD_COLS, ' ')), turns(0) {
        last_move = {-1, -1};
    }

    void print_board() {
        std::cout << "\n";
        for (int r = 0; r < BOARD_COLS; ++r) {
            std::cout << "  (" << r + 1 << ") ";
        }
        std::cout << "\n";

        for (int r = 0; r < BOARD_ROWS; ++r) {
            std::cout << "|";
            for (int c = 0; c < BOARD_COLS; ++c) {
                std::cout << "  " << board[r][c] << "  |";
            }
            std::cout << "\n";
        }

        std::cout << std::string(42, '-') << "\n";
    }

    char which_turn() {
        std::vector<char> players = {'X', 'O'};
        return players[turns % 2];
    }

    bool in_bounds(int r, int c) {
        return (r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS);
    }

    bool turn(int column) {
        if (column < 0 || column >= BOARD_COLS) {
            return false;
        }

        for (int r = BOARD_ROWS - 1; r >= 0; --r) {
            if (board[r][column] == ' ') {
                board[r][column] = which_turn();
                last_move = {r, column};
                turns++;
                return true;
            }
        }

        return false;
    }

    bool check_winner() {
        int row = last_move[0];
        int col = last_move[1];
        char player = board[row][col];

        // Check horizontal
        int count = 0;
        for (int c = 0; c < BOARD_COLS; ++c) {
            if (board[row][c] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            } else {
                count = 0;
            }
        }

        // Check vertical
        count = 0;
        for (int r = 0; r < BOARD_ROWS; ++r) {
            if (board[r][col] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            } else {
                count = 0;
            }
        }

        // Check diagonal (top-left to bottom-right)
        count = 0;
        int r = row;
        int c = col;
        while (r > 0 && c > 0) {
            r--;
            c--;
        }
        while (r < BOARD_ROWS && c < BOARD_COLS) {
            if (board[r][c] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            } else {
                count = 0;
            }
            r++;
            c++;
        }

        // Check diagonal (top-right to bottom-left)
        count = 0;
        r = row;
        c = col;
        while (r > 0 && c < BOARD_COLS - 1) {
            r--;
            c++;
        }
        while (r < BOARD_ROWS && c >= 0) {
            if (board[r][c] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            } else {
                count = 0;
            }
            r++;
            c--;
        }

        return false;
    }

    bool is_full() {
        for (const auto& row : board) {
            if (std::find(row.begin(), row.end(), ' ') != row.end()) {
                return false;
            }
        }
        return true;
    }
};

void play() {
    Board game;
    bool game_over = false;

    while (!game_over) {
        game.print_board();

        bool valid_move = false;
        while (!valid_move) {
            int user_move;
            std::cout << game.which_turn() << "'s Turn - pick a column (1-" << BOARD_COLS << "): ";
            std::cin >> user_move;
            valid_move = game.turn(user_move - 1);
            if (!valid_move) {
                std::cout << "Invalid move. Please choose an open column.\n";
            }
        }

        if (game.check_winner()) {
            game.print_board();
            std::cout << game.which_turn() << " is the winner!\n";
            game_over = true;
        } else if (game.is_full()) {
            game.print_board();
            std::cout << "The game is a draw.\n";
            game_over = true;
        }
    }
}

int main() {
    play();
    return 0;
}
